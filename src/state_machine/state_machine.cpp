#include "state_machine.h"
#include "state_factory.h"

/**
 * @brief Constructs StateMachine object
 * 
 */
StateMachine::StateMachine(/*HALModuleBase* hal, */ RequestMgr *requestMgr) : reqMgr(requestMgr)
{
    // Prime the state objects
    for (int i = STATE_START; i < MAX_STATES; ++i)
    {
        states[i] = StateBuilder::BuildState((StateEnum)i, &context, requestMgr);
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
    context.floor = 0;
    context.state = CABIN_IDLE;
    context.requestedFloor = 0;
    context.requestedMovement = IDLE;

    // Load Idle state
    TransitionTo(CABIN_IDLE);
}

/**
 * @brief Periodic execution called from the main worker thread
 * 
 */
void StateMachine::RunStateMachine(void)
{
    StateEnum newState = states[context.state]->Execute();
    if (newState != context.state)
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
    states[context.state]->HandleEvent(event);
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
    context.state = state;
}
