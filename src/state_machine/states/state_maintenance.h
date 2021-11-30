#pragma once

#include "state_types.h"
#include "request_mgr.h"
#include "event_types.h"

class MaintenanceState : public StateBase
{
    bool isMaintenanceComplete = false;

public:
    MaintenanceState(StateInfo *pCtx, RequestMgr *pReqMgr) : StateBase(pCtx, pReqMgr) {}
    virtual ~MaintenanceState() = default;

    virtual void Init()
    {
        isMaintenanceComplete = false;
    }

    virtual void HandleEvent(EventType event)
    {
        if (event == MAINTENANCE_COMPLETE)
        {
            isMaintenanceComplete = true;
        }
    }

    /**
     * @brief Execute - Runs the state machine action for the current state
     * 
     * @return StateEnum denoting the next state to be transitioned to.
     *         Current state value is returned to stay in the state.
     */
    virtual StateEnum Execute()
    {
        // default return is the same state
        StateEnum retState = MAINTENANCE;
        if (isMaintenanceComplete == true)
        {
            // do any state machine context reset if required

            retState = CABIN_IDLE;
        }

        return retState;
    }
};
