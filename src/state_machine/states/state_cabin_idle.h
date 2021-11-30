#pragma once

#include "state_types.h"
#include "request_mgr.h"
#include "event_types.h"

class CabinIdleState : public StateBase
{
    bool maintenanceRequested = false;
    bool doorCloseRequired = false;

public:
    CabinIdleState(StateInfo *pCtx, RequestMgr *pReqMgr) : StateBase(pCtx, pReqMgr) {}
    virtual ~CabinIdleState() = default;

    virtual void Init()
    {
        maintenanceRequested = false;
        doorCloseRequired = false;
    }

    virtual void HandleEvent(EventType event)
    {
        switch (event)
        {
        case DOOR_CLOSE_REQUEST:
        case FLOOR_REQUEST:
            doorCloseRequired = true;
            break;
        case MAINTENANCE_REQUEST:
            maintenanceRequested = true;
            break;
        default:
            break;
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
        StateEnum retState = CABIN_IDLE;

        // Giving maintenance request higher priority
        if (maintenanceRequested == true)
        {
            retState = MAINTENANCE;
        }
        else if (doorCloseRequired == true)
        {
            // Try and get the next floor request
            GetNextRequestWrapper();

            if (pCtx->requestedFloor != pCtx->floor)
            {
                // need to tranition to CABIN_CLOSING
                retState = CABIN_CLOSING;
            }
        }
        return retState;
    }
};
