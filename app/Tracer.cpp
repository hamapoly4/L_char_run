#include "Tracer.h" // <1>
#include <stdio.h>

Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_2), sonarSensor(PORT_3) { // <2>
  }

void Tracer::terminate() {
  leftWheel.stop();  // <1>
  rightWheel.stop();
}

void Tracer::run() {
  static unsigned char str_flag = false;  // 走行スタートのフラグ
  int16_t dist; // 超音波センサの距離

  const float Kp = 0.50;  // Pゲイン
  const float Ki = 0.03;  // Iゲイン
  const float Kd = 2;     // Dゲイン
  const int target = 38;  // 目標値
  static int old_diff = 0;
  static int i = 0;
  static int sum = 0;
  int diff = 0;
  int D_value = 0;
  int I_value = 0;
  int P_value = 0;
  int turn = 0;

  /* 左右のモータの角位置に関する変数 */
  int32_t leftwheel_count;
  int32_t rightwheel_count;

  if (str_flag == false)
  {
    dist = sonarSensor.getDistance();
    if (-1 < dist && dist < 5)
    {
      str_flag = true;
      return;
    }
  }

  leftwheel_count = leftWheel.getCount() / ;     // 左モータの角位置を取得
  rightwheel_count = rightwheel.getCount();   // 右モータの角位置を取得
  if (leftwheel_count >= 360 && rightwheel_count >= 360)
  {
    leftwheel.setCount(leftwheel_count);
    rightwheel.setCount(rightwheel_count);

    wup_tsk(MAIN_TASK);
  }

  // P control
  diff = colorSensor.getBrightness() - target;
  P_value = Kp * diff;
  
  // I control
  sum += diff;
  I_value = sum * Ki;
  
  // D control
  D_value = (diff - old_diff) * Kd;
  
  // control sum
  turn = P_value + I_value + D_value;
  
  // RasPike run!!
  leftWheel.setPWM(pwm + turn);
  rightWheel.setPWM(pwm - turn);
  
  i++;
  if (i >= 10)
  {
    sum = 0;
    i = 0;
  }
  old_diff = diff;
}
