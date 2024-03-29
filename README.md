# Homekit ESP8266 - RGB Ledstrip 
A simple project that allows for the control of a RGB (4-pin) LED Strip to be controlled natively by Apples Homekit

Go back to [Will's Homekit stuff](https://github.com/Frostist/Wills-Homekit-Stuff) to see all the rest of my Homekit projects!

# Notes:
- You'll need to download/have the [ardunio IDE](https://www.arduino.cc/en/software) 
- You'll need some sort of [esp8266](https://botshop.co.za/products/nodemcu-esp8266-development-board) or [esp32](https://botshop.co.za/products/nodemcu-esp32-development-board) board (with at least 3 outputs)
> ESP32 boards have seemed to be depreciated with Homekit... But you can still use them, you must just have the correct ESP Library.

This code is still a work in progress, as many other lighting solutions exsit for homekit and use much smarter lights like the neopixels ect (which have a single control wire)


# A couple of prerequisites:
- You'll need the ardunio homekit library [here](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266/)
- You'll need esp serial library [here](https://github.com/plerup/espsoftwareserial/)
- You'll need esp homekit library [here](https://github.com/maximkulkin/esp-homekit)
- You'll need the esp8266 board manager [here](https://arduino-esp8266.readthedocs.io/en/latest/installing.html/)
> or
- You'll need the esp32 board manager [here](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html)
> For this one just follow the instructions on the website, if you get lost just watch my video.

# Some thoughts
- There are a couple of caveats like how the Hue, Sat or Brightness variables aren't stored in memory, but if you really wanted to implment that, it shouldn't be too hard.
- I also added the following below, to TurnOff(); the lights when the power comes back on, as in some countries with loadshedding, having your lights power up at 2am isn't very fun. 

```
void setup() {
  Serial.begin(115200);
  LOG_D("Set Lights to Off");
  TurnOff();
  LOG_D("Wifi starting up");
  wifi_connect();  // in wifi_info.h
  LOG_D("Homekit Starting");
  my_homekit_setup();
}
```
Some more thoughts... My newest update to 3.0.0 includes this code here. To get the unit to reconnect to the wifi based off whether it has a homekit connection and if 10 units of time have passed. This was a serious pain for me, because with some garbage wifi routers they need to be rebooted every now and again, and when this happens the esp8266 unit disconnects and then poof! Never reconnects again. Thus tis update fixes that. 

```
  //calling the counter and hosts logic 
  if (arduino_homekit_connected_clients_count() == 0 && timepassed > 10) {
    delay(10000);
    LOG_D("Wifi or Homekit not connected.");
    LOG_D("Trying to reconnect to wifi.");
    wifi_connect();

    //Resetting the counter to give it some time for the wifi to start up
    timepassed = 0;
  }
```

I have also cracked a way to store varibles in the esp8266 memory!! Which is great for storing a state, for when the power goes off and on again... I might emplement this in the future...

# Read through the steps below and watch the video as well to help!
## 1. The first step is to set your pins. 
Look at the following image of a ESP-12E board.

![This is an image](https://github.com/Frostist/RGB-LED-Strip-ESP8266-Homekit/blob/main/images/esp-12e.jpg)

I used pins D1, D2 and D3.
These equate to PIN 5, 4 and 0.

```
#define RED_PIN 5
#define BLUE_PIN 4
#define GREEN_PIN 0
```



## 2. The next step is to enter Wifi and Password. 
> Note: the network can be a hidden SSID but it has to be a 2.4Ghz wifi network.

You can find this in the wifi_info.h file. 
This can be easily edited in the ardunio IDE.

```
const char *ssid = "YOUR SSID";
const char *password = "YOUR PASSWORD";
```



## 3. Wire in your LED to the board.

You'll need to either create a bread board or do what i did, and "hack" one, thus not needing to buy mosfet's etc
![This is an image](https://github.com/Frostist/RGB-LED-Strip-ESP8266-Homekit/blob/main/images/Esp_board.jpg)

I bought this LED light strip [here](https://www.takealot.com/multipurpose-5m-smd-5050-60led-rgb-strip-light/PLID70902466/), you can find them anywhere on the internet, they are very cheap and work well for fun hacking with Homekit.

However be aware the one i bought came with a very werid power supply, so maybe buy another one...

>Make sure your pin outputs match the mosfets that will power that stream of LED's otherwise your colours will come out very werid.

![This is an image](https://github.com/Frostist/RGB-LED-Strip-ESP8266-Homekit/blob/main/images/led_strips_ledstripfet.gif)

The following image isn't correct because it shows an ardunio, but the wiring remains the same for an esp board. Just make sure ground is GND on the board.


## 4. Run the code!
That should be it. You should just be able to run the code now, the accessory version is 3.0, so if you see any updates here, then you'll know to update your own software.

>NB I am still working on the finer things with this project, took ages to get brightness and colour working together, now its just updating the lights whether it be colour or brightness that changes.




## Resources used to get this working!
- https://www.programmingalgorithms.com/algorithm/hsv-to-rgb/c/
- https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
- https://github.com/alejandro-n-rivera/arduino_led_rgb_hsv
