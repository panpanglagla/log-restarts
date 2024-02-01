#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Arduino.h>

typedef enum {
  StateType_Idle,
  StateType_StartNetwork,
  StateType_StartHotspot,
  StateType_Hotspot,
  StateType_TimeSync,
  StateType_Error,
  StateType_Ready,
  StateType_Wait,
  StateType_Sleep
} StateType;

#endif
