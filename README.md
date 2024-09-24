# Glider - Robo Race Robot

**Glider** is a high-performance robo race robot designed for speed and agility on the track. It is controlled using an Arduino microcontroller, BTS7960 motor drivers, and a Flysky CT6B RC controller, providing precise control over motor functions and movement.

## Features
- **Motor Control**: Powered by BTS7960 motor drivers to handle high-current motors.
- **Flysky CT6B**: RC control using the Flysky CT6B transmitter and receiver.
- **Arduino Integration**: Uses an Arduino to interface with the motor driver and controller, translating inputs into motor commands.
- **Precision Movements**: Custom PWM values to fine-tune forward, backward, left, and right movements for optimal performance.

## Components
- **Arduino (Uno/compatible)**: Main microcontroller used for signal processing.
- **BTS7960 Motor Driver**: High-current motor driver to control the robot's motors.
- **Flysky CT6B**: 6-channel RC transmitter and receiver for remote control.
- **Motors**: High-speed DC motors for propulsion.
- **Power Supply**: Appropriate battery pack to provide the required power for motors and the electronics.

## Hardware Setup

### Wiring Diagram
- **BTS7960 Motor Driver**:
  - Connect motor driver inputs to the Arduino PWM pins.
  - Motor output terminals connect directly to the motors.
  - Ensure power and ground are properly connected.
  
- **Flysky CT6B**:
  - Connect receiver channels to the Arduino analog pins.
  - Map channels to desired robot functions (forward, backward, left, right).

### Pin Configuration

| Arduino Pin | Function                      |
|-------------|-------------------------------|
| 3           | Flysky Channel 1 (Left/Right)  |
| 5           | Flysky Channel 2 (Forward/Backward) |
| 2, 4        | Motor Enable Right             |
| 6, 9        | Motor PWM Right                |
| 7, 8        | Motor Enable Left              |
| 10, 11      | Motor PWM Left                 |

## Code

The provided Arduino code reads the Flysky controller inputs and sends the appropriate PWM signals to the BTS7960 motor driver for controlling the robot's motors.

### Code Explanation

The Arduino code reads PWM signals from the Flysky CT6B receiver, processes them, and controls the motors via the BTS7960 motor driver to achieve forward, backward, and turning motions.

#### Receiver and Motor Driver Pin Setup
The code defines the pins for the receiver and motor driver:

- **Receiver signal pins**: 
  - `ch1_pin (Pin 3)` controls left and right movement.
  - `ch2_pin (Pin 5)` controls forward and backward movement.
  
- **Motor driver pins**: Control the motors:
  - Right motor: `R_EN_right`, `L_EN_right`, `R_PWM_right`, `L_PWM_right`.
  - Left motor: `R_EN_left`, `L_EN_left`, `R_PWM_left`, `L_PWM_left`.

#### Thresholds
The code defines thresholds for motor control:

- Forward and backward thresholds determine when the robot starts moving forward or backward, and the speed of that motion.
- Turning thresholds define left and right turn control.

#### Setup Function
The `setup()` function initializes the pins for the receiver and motor driver and begins serial communication for debugging.

#### Loop Function
The main `loop()` function continuously reads the PWM signals and controls the motors:

- It uses the `pulseIn()` function to read signals from the receiver channels.
- The `map()` function maps the received PWM values to motor speed (0-255).
- Based on the values of ch1 (turning) and ch2 (forward/backward), the motors are driven to make the robot move forward, backward, or turn left/right.

#### Motor Control Logic
- **Neutral state**: Stops all motors when both ch1 and ch2 are neutral.
- **Forward and Backward Motion**: Moves the robot based on ch2 input.
- **Turning**: The robot turns left or right based on ch1 input.

### Additional Notes
- The serial monitor prints the values of ch1 and ch2, making it easy to troubleshoot or adjust the thresholds.
- This code is designed to ensure smooth transitions between movement states, offering precise control during a robo race.

### Video
[![Watch the video](https://example.com/your-thumbnail.jpg)](https://www.instagram.com/reel/DAObigBgAjd/)

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
