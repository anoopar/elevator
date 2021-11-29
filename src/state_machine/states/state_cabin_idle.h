#pragma once

#include "state_types.h"
#include "request_mgr.h"
#include "event_types.h"

class CabinIdleState : public StateBase
{
    bool maintenaceRequested = false;
    bool doorCloseRequired = false;

public:
    CabinIdleState() {}
    virtual ~CabinIdleState() = default;

    virtual void Init()
    {
        maintenaceRequested = false;
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
            maintenaceRequested = true;
            break;
        default:
            break;
        }
    }

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
        // default return is the same state
        StateEnum retState = CABIN_IDLE;

        // Giving maintenance request higher priority
        if (maintenaceRequested == true)
        {
            retState = MAINTENANCE;
        }
        else if (doorCloseRequired == true)
        {
            // Try and get the next floor request
            GetNextRequestWrapper(context, reqMgr);

            if (context.reqFloor != context.floor)
            {
                // need to tranition to CABIN_CLOSING
                retState = CABIN_CLOSING;
            }
        }
        return retState;
    }
};
