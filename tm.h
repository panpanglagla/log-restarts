#ifndef TM_H
#define TM_H

#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Timezone.h>
#include "constants.h"

class TimeManager {
public:
  TimeManager();
  boolean sync();
  byte getWeekday();
  byte getYear();
  byte getDay();
  byte getMonth();
  byte getHour();
  byte getMinute();
  byte getSecond();
  time_t getNow();
  time_t getNowUTC();
};

#endif