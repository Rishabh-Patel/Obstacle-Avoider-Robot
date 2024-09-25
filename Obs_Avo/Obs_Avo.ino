#include <NewPing.h>  // Ultrasonic sensor function library. Install this library
#include <Servo.h>    // Servo motor library. Standard library

#define trigPin 9
#define echoPin 8
#define in1 10
#define in2 3
#define in3 11
#define in4 5
#define servoPin 6

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trigPin, echoPin, maximum_distance); // Initialize the ultrasonic sensor
Servo servo_motor;  // Servo motor instance

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  servo_motor.attach(servoPin); // Attach the servo motor
  
  servo_motor.write(100);  // Set servo to the neutral position
  delay(2000);  // Initial delay
  
  distance = measureDistance(); // Measure initial distance
  delay(100);  // Add a short delay
}

long measureDistance() {
  long duration, distance;
  
  // Send trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read echo pulse
  duration = pulseIn(echoPin, HIGH, 30000); // Timeout of 30ms
  
  // Check for timeout condition
  // if (duration == 0) {
  //   Serial.println("Out of range or no echo received");
  //   return -1;  // Indicates a problem (e.g., out of range)
  // }

  // Calculate the distance in cm
  distance = (duration / 2) / 29.1;
  
  Serial.print("Distance: ");
  Serial.println(distance);
  
  return distance;
}

void loop() {
  // delay(50);

  if (distance <= 20) {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    int distanceRight = lookRight();
    delay(300);
    int distanceLeft = lookLeft();
    delay(300);

    if (distanceRight >= distanceLeft) {
      turnRight();
    } else {
      turnLeft();
    }
    moveForward();
  } else {
    moveForward(); 
  }
  
  distance = measureDistance();
}

int lookRight() {  
  servo_motor.write(0);  // Look to the right
  delay(500);
  int distance = measureDistance(); // Measure distance
  delay(100);
  servo_motor.write(110);  // Return to neutral position
  return distance;
}

int lookLeft() {
  servo_motor.write(180);  // Look to the left
  delay(500);
  int distance = measureDistance(); // Measure distance
  delay(100);
  servo_motor.write(110);  // Return to neutral position
  return distance;
}

void moveStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void moveForward() {
  // if (!goesForward) {
  //   goesForward = true;
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  // }
}

void moveBackward() {
  // goesForward = false;
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(500);
  // moveStop();  // Stop after turning
  moveForward();
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(500);
  moveForward();
  // moveStop();  // Stop after turning
}