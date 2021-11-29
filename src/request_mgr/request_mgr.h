#pragma once

#include "state_types.h"

#define NUM_FLOORS (2)

typedef struct _MoveRequest
{
    /**
     * @brief Requested floor
     * 
     */
    unsigned int floor;
    /**
    * @brief Current request elevator movement
    * 
    */
    ElevatorMovement reqMove;
} MoveRequest;

class RequestMgr
{
    unsigned int requestedFloor = 0;
    unsigned int requestFLags[NUM_FLOORS] = {0};

    void UpdateNextRequestedFloor(void)
    {
        unsigned int nextRequestedFloor = requestedFloor;
        // Clear the flag of the current floor
        // update the requested floof if pending request
        for (int i = 0; i < NUM_FLOORS; ++i)
        {
            if (i == requestedFloor)
            {
                requestFLags[i] = 0;
            }
            else if (requestFLags[i] != 0)
            {
                nextRequestedFloor = i;
            }
        }
        requestedFloor = nextRequestedFloor;
    }

public:
    RequestMgr() {}

    /**
     * @brief Get the Next Request object
     * 
     * @param currentFloor 
     * @param currentMovement 
     * @param nextRequest 
     */
    void GetNextRequest(unsigned int currentFloor,
                        ElevatorMovement currentMovement,
                        MoveRequest &nextRequest)
    {
        if (requestedFloor == currentFloor)
        {
            nextRequest.reqMove = IDLE;
            UpdateNextRequestedFloor();
        }

        if (requestedFloor != currentFloor)
        {
            nextRequest.floor = currentFloor == 0 ? 1 : 0;
            nextRequest.reqMove = (ElevatorMovement)(nextRequest.floor - currentFloor);
        }
    }

    /**
     * @brief Add new floor request to the queue
     * TODO : Add logic for UP/DOWN request
     * Only relevant for more than 2 floors
     * 
     * @param floor Requested floor
     */
    void QueueNewRequest(unsigned int floor /* UP/DOWN */)
    {
        if (floor < NUM_FLOORS)
        {
            requestFLags[floor] = 1;
        }
    }
};
