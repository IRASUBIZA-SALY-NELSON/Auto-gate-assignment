#include <Servo.h>

// Pin configurations
const int triggerPin = 2;        // Pin for Ultrasonic sensor trigger
const int echoPin = 3;           // Pin for Ultrasonic sensor echo
const int redLedAnodePin = 4;    // Pin for Red LED anode (connected to Vcc)
const int redLedCathodePin = 8;  // Pin for Red LED cathode (acting as ground)
const int blueLedCathodePin = 7; // Pin for Blue LED cathode (acting as ground)
const int blueLedPin = 5;        // Pin for Blue LED anode
const int servoPin = 6;          // Pin for Servo motor control
const int buzzerPin = 12;        // Pin for Buzzer

// Constants
const float thresholdDistance = 10.0;  // Threshold for object detection (in cm)
const int closedAngle = 0;             // Servo angle for closed barrier
const int openAngle = 90;              // Servo angle for open barrier
const unsigned long closeDelay = 5000; // Delay (in milliseconds) before closing after no detection

// Creating an instance of Servo object
Servo myServo;
bool isOpen = false;                    // Barrier state: false = closed, true = open
unsigned long lastDetectionTime = 0;    // Timestamp for the last detection

void setup() {
  // Initialize pin modes
  pinMode(triggerPin, OUTPUT);  // Trigger pin for ultrasonic sensor
  pinMode(echoPin, INPUT);      // Echo pin for ultrasonic sensor
  pinMode(redLedAnodePin, OUTPUT);    // Red LED anode pin
  pinMode(redLedCathodePin, OUTPUT);  // Red LED cathode pin
  pinMode(blueLedCathodePin, OUTPUT); // Blue LED cathode pin
  digitalWrite(blueLedCathodePin, LOW); // Set Blue LED cathode LOW
  digitalWrite(redLedCathodePin, LOW);  // Set Red LED cathode LOW

  pinMode(blueLedPin, OUTPUT);   // Blue LED anode pin
  pinMode(buzzerPin, OUTPUT);    // Buzzer pin

  // Initialize servo and set its position to closed
  myServo.attach(servoPin);
  myServo.write(closedAngle);  // Initial barrier position (closed)

  // Initialize LEDs and buzzer state
  digitalWrite(redLedAnodePin, HIGH); // Turn ON Red LED (anode high)
  digitalWrite(blueLedPin, LOW);      // Keep Blue LED OFF initially
  digitalWrite(buzzerPin, LOW);       // Ensure Buzzer is OFF
}

// Function to calculate distance using the ultrasonic sensor
float getDistance() {
  digitalWrite(triggerPin, LOW);          // Ensure trigger pin is LOW
  delayMicroseconds(2);                   // Small delay for stability
  digitalWrite(triggerPin, HIGH);         // Send pulse to trigger
  delayMicroseconds(10);                  // Duration of trigger pulse
  digitalWrite(triggerPin, LOW);          // End pulse
  long duration = pulseIn(echoPin, HIGH); // Measure echo duration
  return duration / 58.0;                 // Convert pulse duration to cm
}

unsigned long lastBeepTime = 0;
bool buzzerState = false;

void loop() {
  // Get the distance from the ultrasonic sensor
  float distance = getDistance();
  bool objectDetected = (distance < thresholdDistance); // Check if object is within threshold

  // If object is detected, open the barrier
  if (objectDetected) {
    if (!isOpen) {
      myServo.write(openAngle);    // Open the barrier
      isOpen = true;                // Set barrier state to open
      digitalWrite(blueLedPin, HIGH);  // Turn ON Blue LED
      digitalWrite(redLedAnodePin, LOW); // Turn OFF Red LED
    }
    lastDetectionTime = millis(); // Update last detection time
  } else {
    // If no object detected and barrier is open, close the barrier after delay
    if (isOpen && (millis() - lastDetectionTime > closeDelay)) {
      myServo.write(closedAngle);   // Close the barrier
      isOpen = false;               // Set barrier state to closed
      digitalWrite(redLedAnodePin, HIGH); // Turn ON Red LED
      digitalWrite(blueLedPin, LOW); // Turn OFF Blue LED
      digitalWrite(buzzerPin, LOW); // Ensure Buzzer is OFF
      buzzerState = false;          // Reset buzzer state
    }
  }

  // If the barrier is open, trigger buzzer at intervals
  if (isOpen) {
    unsigned long currentTime = millis();
    if (currentTime - lastBeepTime >= 500) { // Adjust beep rate with time (500ms interval)
      buzzerState = !buzzerState;           // Toggle buzzer state
      digitalWrite(buzzerPin, buzzerState); // Update buzzer
      lastBeepTime = currentTime;           // Update last beep time
    }
  }

  delay(50);  // Small delay for stability and smoother operation
}
