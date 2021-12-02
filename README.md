# Elevator

## System Overview

- Mechanical elevator moves vertically between floors.
- Switches inside the elevator : Door close, door open, Floor number selection
- Each floor will have switch to request elevator service. Up/ down buttons
- Door sensor - Detects obstruction while closing
- Floor sensors - to detect the new floor. This can be done inside the firmware by keeping track of the floors and elevator motor encoders or speed and time calculation.

![Alt text](docs/ElevatorSystemOverview.png?raw=true "System Overview")

## Requirements

- User requests the elevator by pushing the request button at a floor. The elevator reaches the floor and opens door.
- User selects floor number inside the elevator. The elevator closes the door and moves to the requested floor. Opens the door once reached at destination.
- If obstruction detected while closing the door, door is opened and retry to close after a timeout.
- A door that is open will be closed after a timeout for following reasons
    1. Floor number pressed. 
    2. Elevator request from another floor 
    3. Door close button pressed
- A door that is closed will be open only if the elevator is at rest. Open can happen if 
    1. Requested floor reached 
    2. Open button pressed 
    3. Obstruction while closing

## System Architecture

![Alt text](docs/ElevatorSystemArchitecture.png?raw=true "System Architecture")

### Modules
#### Main Worker Thread
    Foreground loop that periodically calls State machine and display module.

#### State Machine
    State machine managing the elevator system states and its transitions.
    Handles input events in each state.

#### Event Manager
    Records asynchronous user input events.
    If a polling scheme needs to be used this module will do the polling with the main worker thread calling the event polling method of this module.
    Any Floor request events will be handed off to the Request manager module.
    Other user inputs are translated to system events and passed on to the state machine.

#### Request Manager
    Module to handle and arbitrate all the requests of the elevator.
    Records the new requests. 
    State machine calls into this module with the current state info to get the next request.
    This module abstract any algorithms to prioritize the request. 
    If the system needs to be scaled into a multi floor elevator system or a multi floor multi elevator system, this object can be extended. The changes will be localised to this module. 

#### IO Module
    HAL for GPIO ISRs and other IO input.

#### Display Module
    Display for user at each floors and inside cabin.

## State Diagram

Cabin Door remains Open during Idle state.

Closing door while at rest is avoided for power efficiency.

Code : src/state_machine

#### CABIN_IDLE 

    - Default Init state. Door is open.
    - Transitions to CABIN_CLOSING if a request pending detected.
    - Transitions to CABIN_CLOSING if a Door Close button is pressed.
    - Transitions to MAINTENANCE if Error detected or Maintenace request.

#### CABIN_CLOSING 

    - Requests Door close. 
    - Transitions to CABIN_OPENING if any door obstructions found.
    - Transitions to CABIN_OPENING if Door Open button is pressed or request is pending from same floor.
    - Transitions to CABIN_OPENING if no pending requests and times out.
    - Transitions to CABIN_MOVING if request pending.
    - Transitions to MAINTENANCE if Error detected or Maintenace request.

#### CABIN_MOVING

    - Polls the pending request and moves the cabin UP or DOWN according to the requested floor and current cabin position.
    - Stops cabin and transitions to CABIN_OPENING if destination floor reached.
    - Transitions to MAINTENANCE if Error detected

#### CABIN_OPENING

    - Opens door.
    - Transitions to CABIN_IDLE once the door is opened.

#### MAINTENANCE

    - Transitions to IDLE on reset

![Alt text](docs/ElevatorStateDiagram.png?raw=true "State Diagram")

### State Machine - Sequence Diagram

![Alt text](docs/Elevator_SM_SequenceDiagram.png?raw=true "Sequence Diagram")

## Assumptions

- [ ] Power Up / Power Loss Sequence - On power up, before the state machine is initilized the cabin is moved to home and default door open position.
- [ ] No emergency stop inputs.
- [ ] HAL module drives the motor and door. 
- [ ] inputs from hardware (GPIO/sensors/encoders etc) are managed by the event manager and translated into "Events".
- [ ] Only state machine design is in scope.

## Design Issues

- The events send to state machine that are not handled in current state are not queued or passed to next state if in transition. Some events are ignored for a state as per design, but there can be a window during transition, where events can be lost.
- Timeout counters are based on the cadence of the state machine execution. Needs a config parameter to correctly determine the timeout values probably at compile time rather than hardcoding them.
- Constant frequency of execution loop for state machine is expected. This timing dependency should be eliminated.

## Build and test

```
cmake --build build && cd build && ctest && cd ..
```
