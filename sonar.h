#include <Arduino.h>
 
class SR04 {
  public:
    int trigPin;
    int echoPin;
 
    void setup() {
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }
    
    void trigger() {
      // the sr04 is triggered by a HIGH pulse of 10 or more microseconds.
      // Short low pulse, clean high, then low.
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(11);
      digitalWrite(trigPin, LOW);
    }
 
    long microsecondsToCentimeters(long microseconds)
    {
      // The speed of sound is 340 m/s or 29 microseconds per centimeter.
      // The ping travels out and back, so to find the distance of the
      // object we take half of the distance travelled.
      return microseconds / 58; // (use 148 for inches) 
    }
    
    long readDist() {
      trigger();
      // The echo pin is used to read the signal from the hc-sr04. A HIGH
      // pulse whose duration is the time (in microseconds) from the sending
      // of the ping to the reception of its echo off of an object.
      long duration = pulseIn(echoPin, HIGH);
      // convert the time into a distance
      int cm = microsecondsToCentimeters(duration);
      return cm;
    }
};
