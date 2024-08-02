#include "app.h" // <1>
#include "Tracer.h" // <2>
#include <stdio.h>

using namespace ev3api;

Tracer tracer;  // <4>

void tracer_task(intptr_t exinf) { // <1>
  tracer.run();
  ext_tsk();
}

void main_task(intptr_t unused) { // <1>
  sta_cyc(TRACER_CYC); // <4>
  
  slp_tsk();  // メインタスクの起床待ち

  stp_cyc(TRACER_CYC); // <3>
  printf("stop cyclickhandler!!\n")
  tracer.terminate(); // <4>
  ext_tsk(); // <5>
}

