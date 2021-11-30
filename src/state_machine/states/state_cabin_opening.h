#pragma once

#include "state_types.h"
#include "request_mgr.h"
#include "event_types.h"

class CabinOpeningState : public StateBase
{
    bool maintenanceRequested = false;
    bool doorOpened = false;

public:
    CabinOpeningState(StateInfo *pCtx, RequestMgr *pReqMgr) : StateBase(pCtx, pReqMgr) {}
    virtual ~CabinOpeningState() = default;

    virtual void Init()
    {
        maintenanceRequested = false;
        // Cabin is not moving when entering this state
        doorOpened = false;
        // Initiate Door Open
        // HAL_OpenDoor()
    }

    virtual void HandleEvent(EventType event)
    {
        switch (event)
        {
        case DOOR_OPENED:
            doorOpened = true;
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
        StateEnum retState = CABIN_OPENING;

        // Giving maintenance request higher priority
        if (maintenanceRequested == true)
        {
            retState = MAINTENANCE;
        }
        else if (doorOpened == true)
        {
            // transition to Idle
            retState = CABIN_IDLE;
        }

        return retState;
    }
};
