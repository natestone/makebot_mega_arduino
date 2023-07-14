//Get a square by moving Mega


#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "src/MeSingleLineFollower.h"
#include "src/MeCollisionSensor.h"
#include "src/MeBarrierSensor.h"
#include "src/MeNewRGBLed.h"
#include <MeMegaPi.h>

MeBarrierSensor barrier_61(61);
MeMegaPiDCMotor motor_1(1);
MeMegaPiDCMotor motor_9(9);
MeMegaPiDCMotor motor_2(2);
MeMegaPiDCMotor motor_10(10);
MeMegaPiDCMotor motor_3(3);
MeMegaPiDCMotor motor_11(11);
MeMegaPiDCMotor motor_4(4);
MeMegaPiDCMotor motor_12(12);
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;

float Time = 0;

void motor_foward_left_run(int16_t speed)
{
   motor_10.run(-speed);
}

void motor_foward_right_run(int16_t speed)
{
  motor_1.run(speed);
}

void motor_back_left_run(int16_t speed)
{
  motor_2.run(-speed);
}

void motor_back_right_run(int16_t speed)
{
  motor_9.run(speed);
}

void motor_stop()
{
      motor_1.run(0);
      motor_9.run(0);
      motor_2.run(0);
      motor_10.run(0);
      //motor_3.run(0);
      //motor_11.run(0);
      //motor_4.run(0);
      //motor_12.run(0);
}

void move_control(int16_t vx, int16_t vy, int16_t vw)
{
  int16_t foward_left_speed;
  int16_t foward_right_speed;
  int16_t back_left_speed;
  int16_t back_right_speed;

  foward_left_speed = vy + vx + vw;
  foward_right_speed = vy - vx - vw;
  back_left_speed = vy - vx + vw;
  back_right_speed = vy + vx - vw;

  motor_foward_left_run(foward_left_speed);
  motor_foward_right_run(foward_right_speed);
  motor_back_left_run(back_left_speed);
  motor_back_right_run(back_right_speed);
}

void _delay(float seconds) {
  if(seconds < 0.0){
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

void setup() {
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
  Time = 0.5;

}

void _loop() {
}

int go = 0;

void loop() {
  if(barrier_61.isBarried()) 
  {
   
    while (go < 1)
     {

      // forward and right
      move_control(10 / 100.0 * 255,20 / 100.0 * 255,0 / 100.0 * 255);
      _delay(2.0);

      // back and right
      move_control(10 / 100.0 * 255,-20 / 100.0 * 255,0 / 100.0 * 255);
      _delay(2.0);
    
      // left
      move_control(-20 / 100.0 * 255,0 / 100.0 * 255,0 / 100.0 * 255);
      _delay(2.0);

      motor_stop();
      go++;

     }
  }
}

/*

original code

     // right
      move_control(50 / 100.0 * 255,0 / 100.0 * 255,0 / 100.0 * 255);
      _delay(0.7);

      motor_stop();
      _delay(float(Time));

     // forward
      move_control(0 / 100.0 * 255,50 / 100.0 * 255,0 / 100.0 * 255);
      _delay(0.7);

      motor_stop();
      _delay(float(Time));

      // left
      move_control(-50 / 100.0 * 255,0 / 100.0 * 255,0 / 100.0 * 255);
      _delay(0.7);

      motor_stop();
      _delay(float(Time));

      // back
      move_control(0 / 100.0 * 255,-50 / 100.0 * 255,0 / 100.0 * 255);
      _delay(0.7);

      motor_stop();
      _delay(float(Time));



right triangle

      // forward
      move_control(0 / 100.0 * 255,20 / 100.0 * 255,0 / 100.0 * 255);
      _delay(2.0);

      motor_stop();
      _delay(float(Time));

      // right and back
      move_control(20 / 100.0 * 255,-20 / 100.0 * 255,0 / 100.0 * 255);
      _delay(2.0);
    
      motor_stop();
      _delay(float(Time));

      // left
      move_control(-20 / 100.0 * 255,0 / 100.0 * 255,0 / 100.0 * 255);
      _delay(2.0);

      motor_stop();
      _delay(float(Time));


equilateral traingle

     // forward and right
      move_control(10 / 100.0 * 255,20 / 100.0 * 255,0 / 100.0 * 255);
      _delay(2.0);

      // back and right
      move_control(10 / 100.0 * 255,-20 / 100.0 * 255,0 / 100.0 * 255);
      _delay(2.0);
    
      // left
      move_control(-20 / 100.0 * 255,0 / 100.0 * 255,0 / 100.0 * 255);
      _delay(2.0);

      motor_stop();
*/