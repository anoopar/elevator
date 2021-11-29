#pragma once

#include "state_base.h"

class StateBase
{
public:
    virtual void Init();
    virtual void HandleEvent();

    /**
     * @brief Execute - Runs the state machine action for the current state
     * 
     * @return StateEnum denoting the next state to be transitioned to.
     *         Current state value is returned to stay in the state.
     */
    virtual StateEnum Execute(void);
};
