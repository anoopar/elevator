#include <iostream>

using namespace std;

typedef enum _TransitType_t
{
    DESCENT = -1,
    IDLE,
    ASCENT,
} TransitType_t;

typedef struct _ServiceRequest_t
{
    TransitType_t reqDirn;
    unsigned int fromFloor;
} ServiceRequest_t;

typedef struct _StateMachineContext_t
{
    TransitType_t currentTransit;
    ServiceRequest_t nextReq;
    unsigned int currentFloor;
} StateMachineContext_t;

typedef enum _ElevatorState_t
{
    CABIN_STOPPED,
    CABIN_MOVING,
    DOOR_OPEN,
    DOOR_CLOSING,
    DOOR_CLOSED
} ElevatorState_t;

class ElevateStateBase
{
private:
public:
    virtual void Init() = 0;
    virtual void Execute() = 0;
    virtual void HandleEvent() = 0;
};

class StateMachine
{
private:
    StateMachineContext_t context;

public:
    void TransitionTo(ElevatorState_t nextState);
};

int main()
{
    cout << "Hello World \n"
         << endl;
    return 0;
}
