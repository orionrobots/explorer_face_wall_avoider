#include <Arduino.h>
 
class Motor {
  public:
    int enable;
    int in1;
    int in2;
 
    void setup() {
      //Set all the pins as outputs
      pinMode(enable, OUTPUT);
      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
    }
    
    void forward(int speed) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enable, speed);
    }
    
    void backward(int speed) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enable, speed);
    }
    
    void stop() {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(enable, 0);
    }
};
 
class TurtleMotors {
  public:
    Motor left_motor;
    Motor right_motor;
    int speed;
    int step_size_in_ms;
  
  private:
    //Because we will wait for a number of steps and stop regularly - 
    //turn this into a function we can use a few times.
    void _waitAndStop(int steps) {
     if (steps > 0) {
      delay(step_size_in_ms * steps);
      left_motor.stop();
      right_motor.stop();
     }
    }
    
  public:
    void setup() {
      left_motor.setup();
      right_motor.setup();
    }
    
    void forward(int steps=1) {
      left_motor.forward(speed);
      right_motor.forward(speed);
       _waitAndStop(steps);
    }
    
    void backward(int steps=1) {
      left_motor.backward(speed);
      right_motor.backward(speed);
      _waitAndStop(steps);
    }
 
    void turnLeft(int steps=1) {
      left_motor.backward(speed);
      right_motor.forward(speed);
      _waitAndStop(steps);
    }
 
    void turnRight(int steps=1) {
      left_motor.forward(speed);
      right_motor.backward(speed);
      _waitAndStop(steps);
    }
    
    void stop() {
      left_motor.stop();
      right_motor.stop();
    }
};
