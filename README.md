# Auto-gate-assignment

# **Ultrasonic Sensor Barrier System with Servo and LED Indicators**

## 📜 **Project Description**
This project is designed to use an ultrasonic sensor to detect objects at a specific distance. Based on the detection, the system controls a servo motor to open or close a barrier (gate) and provides visual and auditory indicators. The system is equipped with LEDs and a buzzer for status indication.

- **Servo Motor**: Controls the movement of the barrier (gate).
- **Ultrasonic Sensor**: Measures distance to detect objects.
- **LED Indicators**: Red LED shows barrier is closed, Blue LED shows barrier is open.
- **Buzzer**: Provides an alert when the barrier is open.

The barrier opens when an object is detected within a predefined threshold distance and closes after a set period of no detection.

## 🚀 **Features**
- **Ultrasonic Distance Measurement**: Detects objects within a specified range.
- **Servo Control**: Opens and closes the barrier based on detection.
- **LED Indicators**: Shows the current status of the barrier (open/closed).
- **Buzzer Alerts**: Provides sound feedback when the barrier is open.
- **Automatic Barrier Control**: The barrier will close after 5 seconds of no detection.

## 🛠️ **Components Used**
- **Ultrasonic Sensor (HC-SR04)**:
  - Trigger Pin: Pin 2
  - Echo Pin: Pin 3
- **Servo Motor (SG90 or similar)**: Pin 6
- **Red LED**: Pin 4 (Anode), Pin 8 (Cathode)
- **Blue LED**: Pin 5 (Anode), Pin 7 (Cathode)
- **Buzzer**: Pin 12

## 🔧 **Required Libraries**
- **Servo Library**: Used to control the servo motor.

```cpp
#include <Servo.h>
