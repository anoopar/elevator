#pragma once

#include "state_types.h"
#include "request_mgr.h"
#include "state_base.h"
#include "state_builder.h"

class StateMachine
{
private:
    StateInfo info;
    RequestMgr *reqMgr;
    StateBase *states[MAX_STATES];

public:
    StateMachine(/*HALModuleBase* hal, */ RequestMgr *requestMgr) : reqMgr(requestMgr)
    {
        for (int i = STATE_START; i < MAX_STATES; ++i)
        {
            states[i] = StateBuilder::BuildState((StateEnum)i);
        }
    }
};
