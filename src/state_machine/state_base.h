#pragma once

#include "state_base.h"
#include "request_mgr.h"
#include "event_types.h"

class StateBase
{
protected:
    void GetNextRequestWrapper(StateInfo &context,
                               RequestMgr *reqMgr)
    {
        MoveRequest request;
        reqMgr->GetNextRequest(context.floor, context.requestedMovement, request);
        context.requestedFloor = request.floor;
        context.requestedMovement = request.reqMove;
    }

public:
    StateBase() {}
    virtual void Init() = 0;
    virtual void HandleEvent(EventType event) = 0;

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
                              /*HALModuleBase* hal*/) = 0;

    virtual ~StateBase() {}
};
