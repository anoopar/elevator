#pragma once

#include "state_types.h"
#include "state_base.h"
#include "state_cabin_idle.h"
#include "state_cabin_closing.h"
#include "state_cabin_moving.h"
#include "state_cabin_opening.h"
#include "state_maintenance.h"

class StateBuilder
{
public:
    static StateBase *BuildState(StateEnum state, StateInfo *pCtx, RequestMgr *pReqMgr)
    {
        StateBase *retObject = nullptr;
        switch (state)
        {
        case CABIN_IDLE:
            retObject = static_cast<StateBase *>(new CabinIdleState(pCtx, pReqMgr));
            break;
        case CABIN_CLOSING:
            retObject = static_cast<StateBase *>(new CabinClosingState(pCtx, pReqMgr));
            break;
        case CABIN_MOVING:
            retObject = static_cast<StateBase *>(new CabinMovingState(pCtx, pReqMgr));
            break;
        case CABIN_OPENING:
            retObject = static_cast<StateBase *>(new CabinOpeningState(pCtx, pReqMgr));
            break;
        case MAINTENANCE:
            retObject = static_cast<StateBase *>(new MaintenanceState(pCtx, pReqMgr));
            break;
        default:
            break;
        }
        return retObject;
    }
};
