#pragma once

typedef enum _EventType
{
    DOOR_OPENED,
    DOOR_CLOSED,
    DOOR_OBSTRUCTION,
    FLOOR_SENSOR,
    DOOR_OPEN_REQUEST,
    DOOR_CLOSE_REQUEST,
    CABIN_MOTOR_STOPPED,
    FLOOR_REQUEST,
    MAINTENANCE_REQUEST,
    MAINTENANCE_COMPLETE
} EventType;
