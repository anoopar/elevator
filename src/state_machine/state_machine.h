#pragma once

#include "state_types.h"
#include "request_mgr.h"
#include "event_types.h"
#include "state_base.h"

class StateMachine
{
private:
    StateInfo context;
    RequestMgr *reqMgr;
    StateBase *states[MAX_STATES];

    void InitContext(void);
    void TransitionTo(StateEnum state);

public:
    /**
     * @brief StateMachine constructor
     * 
     */
    StateMachine(/*HALModuleBase* hal, */ RequestMgr *requestMgr);

    /**
     * @brief Reset the state context
     * 
     */
    void Reset(void);

    /**
     * @brief State Machine execution
     * Called at regular cadence.
     * 
     */
    void RunStateMachine(void);

    /**
     * @brief Handle the Events from Event Manager
     * 
     * @param event Event to handle
     */
    void HandleEvent(EventType event);

    /**
     * @brief Get the Current State object
     * 
     * @return StateEnum 
     */
    StateEnum GetCurrentState(void)
    {
        return context.state;
    }

    /**
     * @brief Get the State Info object
     * 
     * @param infoOut 
     */
    void GetStateInfo(StateInfo &infoOut)
    {
        // copy the context into infoOut
        infoOut = context;
    }
    /**
     * @brief Destroy the State Machine object
     * 
     */
    ~StateMachine();
};
