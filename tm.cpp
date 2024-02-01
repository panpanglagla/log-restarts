#include "tm.h"

TimeChangeRule CEST = { "CEST", Last, Sun, Mar, 2, 120 };  // Central European Summer Time
TimeChangeRule CET = { "CET ", Last, Sun, Oct, 3, 60 };    // Central European Standard Time
Timezone CE(CEST, CET);

TimeManager::TimeManager() {
}

boolean TimeManager::sync() {
  WiFiUDP _ntpUDP;
  NTPClient _timeClient(_ntpUDP, "fr.pool.ntp.org", 0, 60 * 60 * 1000);
  _timeClient.begin();
  if (_timeClient.update()) {
    unsigned long epoch = _timeClient.getEpochTime();
    setTime(epoch);
    return true;
  } else {
    return false;
  }
}

byte TimeManager::getWeekday() {
  TimeChangeRule *tcr;
  time_t t = CE.toLocal(now(), &tcr);
  return weekday(t);
}

time_t TimeManager::getNow() {
  TimeChangeRule *tcr;
  return CE.toLocal(now(), &tcr);
}

time_t TimeManager::getNowUTC() {
  return now();
}

byte TimeManager::getYear() {
  TimeChangeRule *tcr;
  time_t t = CE.toLocal(now(), &tcr);
  return year(t);
}

byte TimeManager::getMonth() {
  TimeChangeRule *tcr;
  time_t t = CE.toLocal(now(), &tcr);
  return month(t);
}

byte TimeManager::getDay() {
  TimeChangeRule *tcr;
  time_t t = CE.toLocal(now(), &tcr);
  return day(t);
}

byte TimeManager::getHour() {
  TimeChangeRule *tcr;
  time_t t = CE.toLocal(now(), &tcr);
  return hour(t);
}

byte TimeManager::getMinute() {
  TimeChangeRule *tcr;
  time_t t = CE.toLocal(now(), &tcr);
  return minute(t);
}

byte TimeManager::getSecond() {
  TimeChangeRule *tcr;
  time_t t = CE.toLocal(now(), &tcr);
  return second(t);
}
