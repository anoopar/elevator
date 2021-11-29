#pragma once

#include "state_types.h"
#include "request_mgr.h"
#include "event_types.h"

class MaintenanceState : public StateBase
{
public:
    MaintenanceState() {}
    virtual void Init() {}
    virtual void HandleEvent(EventType event) {}

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
                              /*HALModuleBase* hal*/)
    {
        return context.state;
    }
};
