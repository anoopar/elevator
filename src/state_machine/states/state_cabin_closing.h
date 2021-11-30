#pragma once

#include "state_types.h"
#include "request_mgr.h"
#include "event_types.h"

#define DOOR_CLOSE_WAIT_TIMEOUT_COUNT (16)
#define WAIT_FOR_REQUEST_TIMEOUT_COUNT (16)

class CabinClosingState : public StateBase
{
    bool maintenanceRequested = false;
    bool doorOpenRequired = false;
    unsigned int timeoutCounter = 0;

    enum CabinClosingSubState
    {
        SUBSTATE_DOOR_CLOSE_START,
        SUBSTATE_DOOR_CLOSE_WAIT_FOR_DONE,
        SUBSTATE_WAITING_FOR_REQUEST
    };

    CabinClosingSubState substate;

public:
    CabinClosingState(StateInfo *pCtx, RequestMgr *pReqMgr) : StateBase(pCtx, pReqMgr) {}
    virtual ~CabinClosingState() = default;

    virtual void Init()
    {
        maintenanceRequested = false;
        doorOpenRequired = false;
        timeoutCounter = 0;
        substate = SUBSTATE_DOOR_CLOSE_START;
    }

    virtual void HandleEvent(EventType event)
    {
        switch (event)
        {
        case DOOR_CLOSED:
            if (substate == SUBSTATE_DOOR_CLOSE_WAIT_FOR_DONE)
            {
                // Reset counter
                timeoutCounter = 0;
                // transit to next substate
                substate = SUBSTATE_WAITING_FOR_REQUEST;
            }
            break;
        case DOOR_OPEN_REQUEST: // Fall through intentional
        case DOOR_OBSTRUCTION:
            doorOpenRequired = true;
            break;
        case FLOOR_REQUEST:
            // Do nothing.. polled in execute
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
        StateEnum retState = CABIN_CLOSING;

        // Giving maintenance request higher priority
        if (maintenanceRequested == true)
        {
            retState = MAINTENANCE;
        }
        else if (doorOpenRequired == true)
        {
            retState = CABIN_OPENING;
        }
        else
        {
            switch (substate)
            {
            case SUBSTATE_DOOR_CLOSE_START:
                // Close the door
                // HAL_CloseDoor();
                substate = SUBSTATE_DOOR_CLOSE_WAIT_FOR_DONE;
                break;
            case SUBSTATE_DOOR_CLOSE_WAIT_FOR_DONE:
                timeoutCounter++;
                if (timeoutCounter >= DOOR_CLOSE_WAIT_TIMEOUT_COUNT)
                {
                    // Unable to close the door
                    // ERROR occured
                    retState = MAINTENANCE;
                }
                break;
            case SUBSTATE_WAITING_FOR_REQUEST:
                // Try and get the next floor request
                GetNextRequestWrapper();
                if (pCtx->floor != pCtx->requestedFloor)
                {
                    // Door closed, ready to move
                    retState = CABIN_MOVING;
                }
                else
                {
                    // timeoutCounter is set to 0 at transition
                    timeoutCounter++;
                    if (timeoutCounter >= WAIT_FOR_REQUEST_TIMEOUT_COUNT)
                    {
                        // No pending requests found
                        retState = CABIN_OPENING;
                    }
                }
                break;
            default:
                break;
            }
        }

        return retState;
    }
};
