#ifndef MOTOR_H
#define MOTOR_H

#include <Encoder.h>
#include <Servo.h>
#include <PID_v1.h>

class Motor {
public:
  static void initialize();
  
  Motor(int encoderPin1, int encoderPin2);
  void attach(int motorPin);
  void updateEncoder();
  void update();
  void setSpeed(double speed);
  void setRotations(double rotations);
  bool isAtTarget();

private:
  int motorIndex;
  bool isSpeedMode = true;
  
  double input, output, setpoint;
  signed char ticksSampled;
  Encoder encoder;
  PID pid;
  Servo motor;

  int targetTicks;
};

#endif

