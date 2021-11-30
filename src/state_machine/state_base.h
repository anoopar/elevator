#pragma once

#include "state_base.h"
#include "request_mgr.h"
#include "event_types.h"

class StateBase
{
protected:
    StateInfo *pCtx = nullptr;
    RequestMgr *pReqMgr = nullptr;

    void GetNextRequestWrapper()
    {
        MoveRequest request;
        pReqMgr->GetNextRequest(pCtx->floor, pCtx->requestedMovement, request);
        pCtx->requestedFloor = request.floor;
        pCtx->requestedMovement = request.reqMove;
    }

public:
    StateBase(StateInfo *pContext,
              RequestMgr *reqMgr /*HALModuleBase* hal*/) : pCtx(pContext), pReqMgr(reqMgr) {}
    virtual void Init() = 0;
    virtual void HandleEvent(EventType event) = 0;

    /**
     * @brief Execute - Runs the state machine action for the current state
     * 
     * @return StateEnum denoting the next state to be transitioned to.
     *         Current state value is returned to stay in the state.
     */
    virtual StateEnum Execute() = 0;

    virtual ~StateBase() {}
};
