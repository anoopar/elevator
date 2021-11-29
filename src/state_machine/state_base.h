#pragma once

#include "state_base.h"
#include "request_mgr.h"
#include "event_types.h"

class StateBase
{
public:
    virtual void Init() = 0;
    virtual void HandleEvent(EventType event) = 0;

    /**
     * @brief 
     * 
     * @return StateEnum denoting the next state to be transitioned to.
     *         Current state value is returned to stay in the state.
     */

    /**
     * @brief Execute - Runs the state machine action for the current state
     * 
     * @param context 
     * @param reqMgr 
     * @param hal 
     * @return StateEnum denoting the next state to be transitioned to.
     *         Current state value is returned to stay in the state.
     */
    virtual StateEnum Execute(StateInfo &context,
                              RequestMgr *reqMgr
                              /*HALModuleBase* hal*/) = 0;

    virtual ~StateBase() {}
};
