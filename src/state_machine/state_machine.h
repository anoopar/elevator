#pragma once

#include "state_types.h"
#include "request_mgr.h"
#include "event_types.h"
#include "state_base.h"
#include "state_builder.h"

class StateMachine
{
private:
    StateInfo info;
    RequestMgr *reqMgr;
    StateBase *states[MAX_STATES];

    void TransitionTo(StateEnum state)
    {
        states[state]->Init();
        info.state = state;
    }

public:
    StateMachine(/*HALModuleBase* hal, */ RequestMgr *requestMgr) : reqMgr(requestMgr)
    {
        // Prime the state objects
        for (int i = STATE_START; i < MAX_STATES; ++i)
        {
            states[i] = StateBuilder::BuildState((StateEnum)i);
        }

        // reset the state context
        Reset();
    }

    /**
     * @brief Reset the state context
     * 
     */
    void Reset(void)
    {
        info.floor = 0;
        info.state = CABIN_IDLE;
        info.reqFloor = 0;
        info.reqMovement = IDLE;

        // Load Idle state
        TransitionTo(CABIN_IDLE);
    }

    void RunStateMachine(void)
    {
        StateEnum newState = states[info.state]->Execute(info, reqMgr);
        if (newState != info.state)
        {
            TransitionTo(newState);
        }
    }

    void HandleEvent(EventType event)
    {
        states[info.state]->HandleEvent(event);
    }

    /**
     * @brief Destroy the State Machine object
     * 
     */
    ~StateMachine()
    {
        for (int i = STATE_START; i < MAX_STATES; ++i)
        {
            delete states[i];
        }
    }
};
