#include <DHT.h>
#include <DHT_U.h>

#define BLYNK_TEMPLATE_ID "TMPLEuF8W7U7"
#define BLYNK_DEVICE_NAME "Smart Sense"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial

#define APP_DEBUG

#include "BlynkEdgent.h"
#include <TimeLib.h>

BlynkTimer timer;

#define pumpPin D0
#define DHTPIN D1
//#define lightPin D5
#define lightSensorPin D6

#define DHTTYPE    DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

int notificationFlag = 0;

long Pump_timer_start_set[4] = {0xFFFF, 0xFFFF};
long Pump_timer_stop_set[4] = {0xFFFF, 0xFFFF};
unsigned char Pump_weekday_set[4];

//long Light_timer_start_set[4] = {0xFFFF, 0xFFFF};
//long Light_timer_stop_set[4] = {0xFFFF, 0xFFFF};
//unsigned char Light_weekday_set[4];

long rtc_sec;
unsigned char day_of_week;

bool Pump_set[1];
bool Pump_status[1];
bool Pump_blynk_status[1];
bool Pump_timer_on_set[1];

//bool Light_set[1];
//bool Light_status[1];
//bool Light_blynk_status[1];
//bool Light_timer_on_set[1];

BLYNK_WRITE(V0)
{
  int val = param.asInt();
  if ( Pump_timer_on_set[0] == 0 )
    Pump_set[0] = val;
  else
    Pump_blynk_status[0] = 1;
}

//BLYNK_WRITE(V1)
//{
//  int val = param.asInt();
//  if ( Light_timer_on_set[0] == 0 )
//    Light_set[0] = val;
//  else
//    Light_blynk_status[0] = 1;
//}

BLYNK_WRITE(V10) 
{
  unsigned char week_day;
 
  TimeInputParam t(param);

  if (t.hasStartTime() && t.hasStopTime() ) 
  {
    Pump_timer_start_set[0] = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
    Pump_timer_stop_set[0] = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
                   
    for (int i = 1; i <= 7; i++) 
    {
      if (t.isWeekdaySelected(i)) 
      {
        week_day |= (0x01 << (i-1));
      }
      else
      {
        week_day &= (~(0x01 << (i-1)));
      }
    } 

    Pump_weekday_set[0] = week_day;
  }
  else
  {
    Pump_timer_start_set[0] = 0xFFFF;
    Pump_timer_stop_set[0] = 0xFFFF;
  }
}

BLYNK_WRITE(V11) 
{
unsigned char week_day;
 
  TimeInputParam t(param);

  if (t.hasStartTime() && t.hasStopTime() ) 
  {
    Pump_timer_start_set[1] = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
    Pump_timer_stop_set[1] = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
                   
    for (int i = 1; i <= 7; i++) 
    {
      if (t.isWeekdaySelected(i)) 
      {
        week_day |= (0x01 << (i-1));
      }
      else
      {
        week_day &= (~(0x01 << (i-1)));
      }
    } 

    Pump_weekday_set[1] = week_day;
  }
  else
  {
    Pump_timer_start_set[1] = 0xFFFF;
    Pump_timer_stop_set[1] = 0xFFFF;
  }
}

BLYNK_WRITE(V12) 
{
unsigned char week_day;
 
  TimeInputParam t(param);

  if (t.hasStartTime() && t.hasStopTime() ) 
  {
    Pump_timer_start_set[2] = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
    Pump_timer_stop_set[2] = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
                   
    for (int i = 1; i <= 7; i++) 
    {
      if (t.isWeekdaySelected(i)) 
      {
        week_day |= (0x01 << (i-1));
      }
      else
      {
        week_day &= (~(0x01 << (i-1)));
      }
    } 

    Pump_weekday_set[2] = week_day;
  }
  else
  {
    Pump_timer_start_set[2] = 0xFFFF;
    Pump_timer_stop_set[2] = 0xFFFF;
  }
}

BLYNK_WRITE(V13) 
{
unsigned char week_day;
 
  TimeInputParam t(param);

  if (t.hasStartTime() && t.hasStopTime() ) 
  {
    Pump_timer_start_set[3] = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
    Pump_timer_stop_set[3] = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
                   
    for (int i = 1; i <= 7; i++) 
    {
      if (t.isWeekdaySelected(i)) 
      {
        week_day |= (0x01 << (i-1));
      }
      else
      {
        week_day &= (~(0x01 << (i-1)));
      }
    } 

    Pump_weekday_set[3] = week_day;
  }
  else
  {
    Pump_timer_start_set[3] = 0xFFFF;
    Pump_timer_stop_set[3] = 0xFFFF;
  }
}

//BLYNK_WRITE(V15) 
//{
//unsigned char week_day;
// 
//  TimeInputParam t(param);
//
//  if (t.hasStartTime() && t.hasStopTime() ) 
//  {
//    Light_timer_start_set[0] = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
//    Light_timer_stop_set[0] = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
//                   
//    for (int i = 1; i <= 7; i++) 
//    {
//      if (t.isWeekdaySelected(i)) 
//      {
//        week_day |= (0x01 << (i-1));
//      }
//      else
//      {
//        week_day &= (~(0x01 << (i-1)));
//      }
//    } 
//
//    Light_weekday_set[0] = week_day;
//  }
//  else
//  {
//    Light_timer_start_set[0] = 0xFFFF;
//    Light_timer_stop_set[0] = 0xFFFF;
//  }
//}
//BLYNK_WRITE(V16) 
//{
//unsigned char week_day;
// 
//  TimeInputParam t(param);
//
//  if (t.hasStartTime() && t.hasStopTime() ) 
//  {
//    Light_timer_start_set[1] = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
//    Light_timer_stop_set[1] = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
//                   
//    for (int i = 1; i <= 7; i++) 
//    {
//      if (t.isWeekdaySelected(i)) 
//      {
//        week_day |= (0x01 << (i-1));
//      }
//      else
//      {
//        week_day &= (~(0x01 << (i-1)));
//      }
//    } 
//
//    Light_weekday_set[1] = week_day;
//  }
//  else
//  {
//    Light_timer_start_set[1] = 0xFFFF;
//    Light_timer_stop_set[1] = 0xFFFF;
//  }
//}
//
//BLYNK_WRITE(V17) 
//{
//unsigned char week_day;
// 
//  TimeInputParam t(param);
//
//  if (t.hasStartTime() && t.hasStopTime() ) 
//  {
//    Light_timer_start_set[2] = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
//    Light_timer_stop_set[2] = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
//                   
//    for (int i = 1; i <= 7; i++) 
//    {
//      if (t.isWeekdaySelected(i)) 
//      {
//        week_day |= (0x01 << (i-1));
//      }
//      else
//      {
//        week_day &= (~(0x01 << (i-1)));
//      }
//    } 
//
//    Light_weekday_set[2] = week_day;
//  }
//  else
//  {
//    Light_timer_start_set[2] = 0xFFFF;
//    Light_timer_stop_set[2] = 0xFFFF;
//  }
//}
//
//BLYNK_WRITE(V18) 
//{
//unsigned char week_day;
// 
//  TimeInputParam t(param);
//
//  if (t.hasStartTime() && t.hasStopTime() ) 
//  {
//    Light_timer_start_set[3] = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
//    Light_timer_stop_set[3] = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
//                   
//    for (int i = 1; i <= 7; i++) 
//    {
//      if (t.isWeekdaySelected(i)) 
//      {
//        week_day |= (0x01 << (i-1));
//      }
//      else
//      {
//        week_day &= (~(0x01 << (i-1)));
//      }
//    } 
//
//    Light_weekday_set[3] = week_day;
//  }
//  else
//  {
//    Light_timer_start_set[3] = 0xFFFF;
//    Light_timer_stop_set[3] = 0xFFFF;
//  }
//}

// #########################################################################################################
BLYNK_WRITE(InternalPinRTC) 
{
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013
  unsigned long blynkTime = param.asLong(); 
  
  if (blynkTime >= DEFAULT_TIME) 
  {
    setTime(blynkTime);

    day_of_week = weekday();
  
    if ( day_of_week == 1 )
      day_of_week = 7;
    else
      day_of_week -= 1; 
    
    rtc_sec = (hour()*60*60) + (minute()*60) + second();
   
    Serial.println(blynkTime);
    Serial.println(String("RTC Server: ") + hour() + ":" + minute() + ":" + second());
    Serial.println(String("Day of Week: ") + weekday()); 
  }
}

// #########################################################################################################
BLYNK_CONNECTED() 
{
  Blynk.sendInternal("rtc", "sync"); 
}

// #########################################################################################################
void checkTime() 
{
  Blynk.sendInternal("rtc", "sync"); 
}

void Pump_mng()
{
  bool time_set_overflow;
  bool Pump_status_buf[1];
  int timer = 0;
  int i = 0;
  
  while( i != 4 && timer != 1)
  {
    Pump_status_buf[0] = Pump_status[0];
    time_set_overflow = 0;
    
    if ( Pump_timer_start_set[i] != 0xFFFF && Pump_timer_stop_set[i] != 0xFFFF)
    {
      if ( Pump_timer_stop_set[i] < Pump_timer_start_set[i] ) time_set_overflow = 1;

      if ((((time_set_overflow == 0 && (rtc_sec >= Pump_timer_start_set[i]) && (rtc_sec < Pump_timer_stop_set[i])) ||
        (time_set_overflow  && ((rtc_sec >= Pump_timer_start_set[i]) || (rtc_sec < Pump_timer_stop_set[i])))) && 
        (Pump_weekday_set[i] == 0x00 || (Pump_weekday_set[i] & (0x01 << (day_of_week - 1) )))) )
        {
          Pump_timer_on_set[0] = 1;
          timer = 1;
        }
        else
          Pump_timer_on_set[0] = 0;
    }
    else
      Pump_timer_on_set[0] = 0;

    if ( Pump_timer_on_set[0] )
    {
      Pump_status[0] = 1;
      Pump_set[0] = 0;
    }
    else
    {
      Pump_status[0] = Pump_set[0];
    }

    if ( Pump_status_buf[0] != Pump_status[0] )
      Pump_blynk_status[0] = 1; 
    i++; 
  }
  digitalWrite(pumpPin, Pump_status[0]);  
}

//void Light_mng()
//{
//  bool Light_set_overflow;
//  bool Light_status_buf[1];
//  int ltimer = 0;
//  int i = 0;
//  
//  while( i != 4 && ltimer != 1)
//  {
//    Light_status_buf[0] = Light_status[0];
//    Light_set_overflow = 0;
//    
//    if ( Light_timer_start_set[i] != 0xFFFF && Light_timer_stop_set[i] != 0xFFFF)
//    {
//      if ( Light_timer_stop_set[i] < Light_timer_start_set[i] ) Light_set_overflow = 1;
//
//      if ((((Light_set_overflow == 0 && (rtc_sec >= Light_timer_start_set[i]) && (rtc_sec < Light_timer_stop_set[i])) ||
//        (Light_set_overflow  && ((rtc_sec >= Light_timer_start_set[i]) || (rtc_sec < Light_timer_stop_set[i])))) && 
//        (Light_weekday_set[i] == 0x00 || (Light_weekday_set[i] & (0x01 << (day_of_week - 1) )))) )
//        {
//          Light_timer_on_set[0] = 1;
//          ltimer = 1;
//        }
//        else
//          Light_timer_on_set[0] = 0;
//    }
//    else
//      Light_timer_on_set[0] = 0;
//
//    if ( Light_timer_on_set[0] )
//    {
//      Light_status[0] = 1;
//      Light_set[0] = 0;
//    }
//    else
//    {
//      Light_status[0] = Light_set[0];
//    }
//
//    if ( Light_status_buf[0] != Light_status[0] )
//      Light_blynk_status[0] = 1; 
//    i++; 
//  }
//  digitalWrite(lightPin, Light_status[0]);  
//}

void blynk_update()
{
  if ( Pump_blynk_status[0] )
  {
      Pump_blynk_status[0] = 0;
      Blynk.virtualWrite(V0, Pump_status[0]);
  }  
//  if ( Light_blynk_status[0] )
//  {
//      Light_blynk_status[0] = 0;
//      Blynk.virtualWrite(V1, Light_status[0]);
//  } 
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(lightSensorPin, INPUT);
  pinMode(pumpPin, OUTPUT);
//  pinMode(lightPin, OUTPUT);
  

  BlynkEdgent.begin();
  timer.setInterval(10000L, checkTime);
}

void loop() 
{
  BlynkEdgent.run();
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
  }
  else {
    if(event.temperature > 0){
    Blynk.virtualWrite(V2, event.temperature);
    }
  }
  
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
  }
  else {
    if(event.relative_humidity < 100){
    Blynk.virtualWrite(V3, event.relative_humidity);
    }
   }
  
  unsigned int Moisture;
  Moisture = analogRead(A0);
  Blynk.virtualWrite(V4, Moisture);
  
  unsigned int LightIntensity;
  LightIntensity = digitalRead(lightSensorPin);
  Blynk.virtualWrite(V5, LightIntensity);
  
  if(LightIntensity > 900 && notificationFlag ==0){
    Blynk.logEvent("light");
    notificationFlag = 1;
  }
  timer.run();
  Pump_mng();
//  Light_mng();
  blynk_update();
}
