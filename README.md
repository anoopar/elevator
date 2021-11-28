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

## State Diagram

Cabin Door remains Open during Idle state.

Closing door while at rest is avoided for power efficiency.

CABIN_IDLE 
- Default Init state. Door is open.
- Transitions to CABIN_CLOSING if a request pending detected.
- Transitions to CABIN_CLOSING if a Door Close button is pressed.
- Transitions to MAINTENANCE if Error detected or Maintenace request.

CABIN_CLOSING 
- Requests Door close. 
- Transitions to CABIN_OPENING if any door obstructions found.
- Transitions to CABIN_OPENING if Door Open button is pressed or request is pending from same floor.
- Transitions to CABIN_OPENING if no pending requests and times out.
- Transitions to CABIN_MOVING if request pending.
- Transitions to MAINTENANCE if Error detected or Maintenace request.

CABIN_MOVING
- Polls the pending request and moves the cabin UP or DOWN according to the requested floor and current cabin position.
- Stops cabin and transitions to CABIN_OPENING if destination floor reached.
- Transitions to MAINTENANCE if Error detected

CABIN_OPENING
- Opens door.
- Transitions to CABIN_IDLE once the door is opened.

MAINTENANCE
- Transitions to IDLE on reset

![Alt text](docs/ElevatorStateDiagram.png?raw=true "State Diagram")

