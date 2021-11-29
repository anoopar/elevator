#pragma once

#include "state_types.h"
#include "state_base.h"
#include "state_cabin_idle.h"
// TODO
class StateBuilder
{
public:
    static StateBase *BuildState(StateEnum state)
    {
        StateBase *retObject = nullptr;
        switch (state)
        {
        case CABIN_IDLE:
            retObject = static_cast<StateBase *>(new CabinIdleState());
            break;
        case CABIN_CLOSING:
            break;
        case CABIN_MOVING:
            break;
        case CABIN_OPENING:
            break;
        case MAINTENANCE:
            break;
        default:
            break;
        }
        return retObject;
    }
};
