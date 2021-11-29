#pragma once

typedef enum _StateEnum
{
    STATE_START,

    CABIN_IDLE = STATE_START,
    CABIN_CLOSING,
    CABIN_MOVING,
    CABIN_OPENING,
    MAINTENANCE,

    MAX_STATES
} StateEnum;

typedef enum _ElevatorMovement
{
    DESCENT = -1,
    IDLE = 0,
    ASCENT = 1
} ElevatorMovement;

typedef struct _StateInfo
{
    /**
     * @brief Current state
     * 
     */
    StateEnum state;
    /**
     * @brief Current Floor
     * 
     */
    unsigned int floor;
    /**
     * @brief Requested floor
     * 
     */
    unsigned int reqFloor;
    /**
     * @brief Current request elevator movement
     * 
     */
    ElevatorMovement reqMovement;
} StateInfo;
