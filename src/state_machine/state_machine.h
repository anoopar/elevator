#pragma once

#include "state_types.h"
#include "request_mgr.h"
#include "event_types.h"
#include "state_base.h"

class StateMachine
{
private:
    StateInfo info;
    RequestMgr *reqMgr;
    StateBase *states[MAX_STATES];

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

    void RunStateMachine(void);

    void HandleEvent(EventType event);

    /**
     * @brief Destroy the State Machine object
     * 
     */
    ~StateMachine();
};
