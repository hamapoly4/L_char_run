#include "Motor.h"       // <1>
#include "ColorSensor.h" // <2>
#include "SonarSensor.h"

using namespace ev3api;  // <4>

class Tracer {  // <1>
public:
  Tracer();
  void run();       // <2>
  void terminate();

private:
  Motor leftWheel;
  Motor rightWheel;
  ColorSensor colorSensor; // <3>
  SonarSensor sonarSensor;
#ifndef MAKE_RASPIKE
  const int8_t pwm = (Motor::PWM_MAX) / 6;
#else
  const int8_t pwm = 45;
#endif

};
