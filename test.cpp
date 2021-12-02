#include <iostream>
#include "request_mgr.h"
#include "state_machine.h"

using namespace std;

// int main(int, char**) {
//     std::cout << "Hello, world!\n";
// }

#include <gtest/gtest.h>

class ElevatorTestFixture : public ::testing::Test
{
public:
    RequestMgr reqMgr;
    StateMachine *sm;

    ElevatorTestFixture()
    {
        // initialization code here
    }

    void SetUp()
    {
        // code here will execute just before the test ensues
        sm = new StateMachine(&reqMgr);
    }

    void TearDown()
    {
        delete sm;
    }

    ~ElevatorTestFixture()
    {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put in any custom data members that you need
};

TEST_F(ElevatorTestFixture, IdleStateOnInit)
{
    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;

    sm->RunStateMachine();

    // Run should not change state
    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;
}

TEST_F(ElevatorTestFixture, IgnoredEvents_IdleState)
{
    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;
    sm->RunStateMachine();

    // Ignore DOOR_OPENED
    sm->HandleEvent(DOOR_OPENED);
    sm->RunStateMachine();

    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;

    // Ignore DOOR_CLOSED
    sm->HandleEvent(DOOR_CLOSED);
    sm->RunStateMachine();

    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;

    // Ignore DOOR_OBSTRUCTION
    sm->HandleEvent(DOOR_OBSTRUCTION);
    sm->RunStateMachine();

    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;

    // Ignore FLOOR_SENSOR
    sm->HandleEvent(FLOOR_SENSOR);
    sm->RunStateMachine();

    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;

    // Ignore DOOR_OPEN_REQUEST
    sm->HandleEvent(DOOR_OPEN_REQUEST);
    sm->RunStateMachine();

    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;

    // Ignore CABIN_MOTOR_STOPPED
    sm->HandleEvent(CABIN_MOTOR_STOPPED);
    sm->RunStateMachine();

    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;

    // Ignore MAINTENANCE_COMPLETE
    sm->HandleEvent(MAINTENANCE_COMPLETE);
    sm->RunStateMachine();

    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;
}

TEST_F(ElevatorTestFixture, DoorCloseRequest_NoFloorRequest_IdleState)
{
    reqMgr.Reset();

    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;
    sm->RunStateMachine();

    // DOOR_CLOSE_REQUEST - will be ignored since no pending floor request
    sm->HandleEvent(DOOR_CLOSE_REQUEST);
    sm->RunStateMachine();
    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;
}

TEST_F(ElevatorTestFixture, DoorCloseRequest_SameFloorRequest_IdleState)
{
    reqMgr.Reset();

    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;
    sm->RunStateMachine();

    reqMgr.QueueNewRequest(0);
    // DOOR_CLOSE_REQUEST - will be ignored since no pending floor request that is different than current floor
    sm->HandleEvent(DOOR_CLOSE_REQUEST);
    sm->RunStateMachine();
    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;
}

TEST_F(ElevatorTestFixture, DoorCloseRequest_NewFloorRequest_IdleState)
{
    reqMgr.Reset();

    EXPECT_EQ(sm->GetCurrentState(), CABIN_IDLE)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_IDLE;
    sm->RunStateMachine();

    reqMgr.QueueNewRequest(1);
    // DOOR_CLOSE_REQUEST - transition to CABIN_CLOSING
    sm->HandleEvent(DOOR_CLOSE_REQUEST);
    sm->RunStateMachine();
    EXPECT_EQ(sm->GetCurrentState(), CABIN_CLOSING)
        << "Curent state " << sm->GetCurrentState() << ", but expected " << CABIN_CLOSING;
}

// DOOR_OPENED,
// DOOR_CLOSED,
// DOOR_OBSTRUCTION,
// FLOOR_SENSOR,
// DOOR_OPEN_REQUEST,
// DOOR_CLOSE_REQUEST,
// CABIN_MOTOR_STOPPED,
// FLOOR_REQUEST,
// MAINTENANCE_REQUEST,
// MAINTENANCE_COMPLETE