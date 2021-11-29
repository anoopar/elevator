#include "state_machine.h"
#include "state_builder.h"

/**
 * @brief Constructs StateMachine object
 * 
 */
StateMachine::StateMachine(/*HALModuleBase* hal, */ RequestMgr *requestMgr) : reqMgr(requestMgr)
{
    // Prime the state objects
    for (int i = STATE_START; i < MAX_STATES; ++i)
    {
        states[i] = StateBuilder::BuildState((StateEnum)i);
    }

    // reset the state context
    Reset();
}

/**
 * @brief Reset the state context
 * 
 */
void StateMachine::Reset(void)
{
    info.floor = 0;
    info.state = CABIN_IDLE;
    info.reqFloor = 0;
    info.reqMovement = IDLE;

    // Load Idle state
    TransitionTo(CABIN_IDLE);
}

/**
 * @brief Periodic execution called from the main worker thread
 * 
 */
void StateMachine::RunStateMachine(void)
{
    StateEnum newState = states[info.state]->Execute(info, reqMgr);
    if (newState != info.state)
    {
        TransitionTo(newState);
    }
}

/**
 * @brief Event Handler. Passes the event to the state object to handle
 * 
 * @param event Raised event 
 */
void StateMachine::HandleEvent(EventType event)
{
    states[info.state]->HandleEvent(event);
}

/**
 * @brief Destroy the State Machine object
 * 
 */
StateMachine::~StateMachine()
{
    for (int i = STATE_START; i < MAX_STATES; ++i)
    {
        delete states[i];
        states[i] = nullptr;
    }
}

/**
 * @brief Transitions from current state to new state.
 * 
 * @param state New state to transition to.
 */
void StateMachine::TransitionTo(StateEnum state)
{
    states[state]->Init();
    info.state = state;
}
