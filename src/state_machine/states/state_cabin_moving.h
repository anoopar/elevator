#pragma once

#include "state_types.h"
#include "request_mgr.h"
#include "event_types.h"

#define ONE_FLOOR_JOURNEY_TIMEOUT_COUNT (120)
class CabinMovingState : public StateBase
{
    unsigned int timeoutCounter = 0;
    bool cabinStopped = false;

    void UpdateCurrentFloor(void)
    {
        if (pCtx->requestedMovement == ASCENT)
        {
            pCtx->floor++;
        }
        else
        {
            pCtx->floor--;
        }
    }

public:
    CabinMovingState(StateInfo *pCtx, RequestMgr *pReqMgr) : StateBase(pCtx, pReqMgr) {}
    virtual ~CabinMovingState() = default;

    virtual void Init()
    {
        timeoutCounter = 0;
        // Try and get the next floor request
        GetNextRequestWrapper();
        if (pCtx->floor != pCtx->requestedFloor)
        {
            cabinStopped = false;
            // Call Move Cabin - to move one more floor in the same dirrection
            // HAL_MoveCabin(1, pCtx->requestedMovement);
        }
    }

    virtual void HandleEvent(EventType event)
    {
        switch (event)
        {
        case FLOOR_SENSOR:
            UpdateCurrentFloor();
            if (pCtx->floor != pCtx->requestedFloor)
            {
                cabinStopped = false;
                // Call Move Cabin - to move one more floor in the same dirrection
                // HAL_MoveCabin(1, pCtx->requestedMovement);

                // reset timeout since one floor journey is completed
                timeoutCounter = 0;
            }
            break;
        case CABIN_MOTOR_STOPPED:
            cabinStopped = true;
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
        StateEnum retState = CABIN_MOVING;

        if (pCtx->floor != pCtx->requestedFloor)
        {
            // increment the timeout counter
            ++timeoutCounter;

            // check for timeout
            if (timeoutCounter > ONE_FLOOR_JOURNEY_TIMEOUT_COUNT)
            {
                // ERROR
                retState = MAINTENANCE;
            }
        }
        else
        {
            if (cabinStopped == true)
            {
                // reached destination - transition to CABIN_OPENING
                retState = CABIN_OPENING;
            }
        }

        return retState;
    }
};
