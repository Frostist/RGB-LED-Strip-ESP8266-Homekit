#include <SoftwareSerial.h>
#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <math.h>
#include "wifi_info.h"

#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__);

// varibles for light strip
bool received_sat = false;
bool received_hue = false;
bool is_on = false;

float current_brightness = 50;
float current_sat = 0.0;
float current_hue = 0.0;

float h;
float s;
float v;


#define RED_PIN 5
#define BLUE_PIN 4
#define GREEN_PIN 0

//Runs once
void setup() {
  Serial.begin(115200);
  LOG_D("Set Lights to Off");
  TurnOff();
  LOG_D("Wifi starting up");
  wifi_connect();  // in wifi_info.h
  LOG_D("Homekit Starting");
  my_homekit_setup();
}

//Runs always
void loop() {
  my_homekit_loop();
  delay(10);
}



//==============================
// HomeKit setup and loop
//==============================

// access your HomeKit characteristics defined in my_accessory.c
extern "C" homekit_server_config_t accessory_config;
extern "C" homekit_characteristic_t cha_on;
extern "C" homekit_characteristic_t cha_bright;
extern "C" homekit_characteristic_t cha_sat;
extern "C" homekit_characteristic_t cha_hue;

static uint32_t next_heap_millis = 0;

//THIS IS HOMEKIT SOFTWARE (DO NOT CHANGE)
// Homekit setup
void my_homekit_setup() {

  cha_on.setter = set_on;
  cha_bright.setter = set_bright;
  cha_sat.setter = set_sat;
  cha_hue.setter = set_hue;

  arduino_homekit_setup(&accessory_config);
}


//THIS IS HOMEKIT SOFTWARE (DO NOT CHANGE)
// Homekit Loop
void my_homekit_loop() {
  arduino_homekit_loop();
  const uint32_t t = millis();
  if (t > next_heap_millis) {
    // show heap info every 5 seconds
    next_heap_millis = t + 5 * 1000;
    LOG_D("Free heap: %d, HomeKit clients: %d",
          ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
  }
}


//THIS IS HOMEKIT SOFTWARE (DO NOT CHANGE)
//Sets the lights to be on or off
void set_on(const homekit_value_t v)
{
    bool on = v.bool_value;
    cha_on.value.bool_value = on; // sync the value

    if (on)
    {
        is_on = true;
        Serial.println("Light On");
        TurnOn();
    }
    else
    {
        is_on = false;
        Serial.println("Light Off");
        TurnOff();
    }
}




//THIS IS HOMEKIT SOFTWARE (DO NOT CHANGE)
//sets and receives LED Brightness
void set_bright(const homekit_value_t v)
{
    Serial.println("set_bright:");
    float bright = v.int_value;
    Serial.println(bright);
    cha_bright.value.int_value = bright; // sync the value

    current_brightness = bright/100;
    
    updateColor();
}



//THIS IS HOMEKIT SOFTWARE (DO NOT CHANGE)
//sets and receives LED Sat
void set_sat(const homekit_value_t v)
{
    Serial.println("set_sat:");
    float sat = v.float_value;
    Serial.println(sat);
    cha_sat.value.float_value = sat; // sync the value

    current_sat = sat/100;
    received_sat = true;
    
    updateColor();
}



//THIS IS HOMEKIT SOFTWARE (DO NOT CHANGE)
//sets and receives LED Hue
void set_hue(const homekit_value_t v)
{
    Serial.println("set_hue:");
    float hue = v.float_value;
    Serial.println(hue);
    cha_hue.value.float_value = hue; // sync the value

    current_hue = hue;
    received_hue = true;
    
    updateColor();
}



//MY CODE STARTS HERE//

//Turn on
void TurnOn()
{
setLEDHSV(current_hue, current_sat, current_brightness);   
}

//Turn off
void TurnOff()
{
setLEDHSV(0,0,0);
}


//updates homekit and lights etc
void updateColor() {
  if (is_on) {
    if (received_hue && received_sat) {
      Serial.println("Updating Colour");
      TurnOn();
      received_hue = false;
      received_sat = false;
    }
  } else if (!is_on)  //lamp - switch to off
  {
    Serial.println("is_on == false");
    TurnOff();
  }
}


//tells voltage to circut
void setLEDRGB(byte r, byte g, byte b) {
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}


//creates that voltage
void setLEDHSV(float h, float s, float v) {
  int i;
  float f, p, q, t;
  float r, g, b;


  if (s == 0) {
    // achromatic (grey)
    r = g = b = v * 255;
    setLEDRGB(r, g, b);
    return;

  } else {
    
    h = h / 60;  // sector 0 to 5
    i = (int)trunc(h);
    f = h - i;  // factorial part of h
    p = v * (1.0 - s);
    q = v * (1.0 - s * f);
    t = v * (1.0 - s * (1.0 - f));

    switch (i) {
      case 0:
        r = v;
        g = t;
        b = p;
        break;
      case 1:
        r = q;
        g = v;
        b = p;
        break;
      case 2:
        r = p;
        g = v;
        b = t;
        break;
      case 3:
        r = p;
        g = q;
        b = v;
        break;
      case 4:
        r = t;
        g = p;
        b = v;
        break;
      default:  // case 5:
        r = v;
        g = p;
        b = q;
        break;
    }
    setLEDRGB(r * 255, g * 255, b * 255);
    return;
  }
}