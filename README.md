# Homekit ESP8266 - RGB Ledstrip 
A simple project that allows for the control of a RGB (4-pin) LED Strip to be controlled natively by Apples Homekit

# Notes:
- You'll need to download/have the ardunio IDE
- You'll need some sort of esp8266 or esp32 board (with at least 3 outputs)

This code is still a work in progress, as many other lighting solutions exsit for homekit and use much smarter lights like the neopixels ect (which have a single control wire)


# A couple of prerequisites:
- You'll need the ardunio homekit library [here](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266/)
- You'll need esp serial library [here](https://github.com/plerup/espsoftwareserial/)
- You'll need esp homekit library [here](https://github.com/maximkulkin/esp-homekit))
- You'll need the esp board manager [here](https://arduino-esp8266.readthedocs.io/en/latest/installing.html/)
> For this one just follow the instructions on the website, if you get lost just watch my video.




# Read through the steps below and watch the video as well to help!
## 1. The first step is to set your pins. Look at the following image of a ESP-12E board.

![This is an image](https://github.com/Frostist/RGB-LED-Strip-ESP8266-Homekit/blob/main/images/esp-12e.jpg)

I used pins D1, D2 and D3.
These equate to PIN 5, 4 and 0.

## 2. The next step is to enter Wifi and Password. 
> Note: the network can be a hidden SSID but it has to be a 2.4Ghz wifi network.
You can find this in the wifi_info.h file. 
This can be easily edited in the ardunio IDE.

## 3. Wire in your LED to the board.

You'll need to either create a bread board or do what i did, and "hack" one, thus not needing to buy mosfet's etc
![This is an image](https://github.com/Frostist/RGB-LED-Strip-ESP8266-Homekit/blob/main/images/Esp_board.jpg)

I bought this LED light strip [here](https://www.takealot.com/multipurpose-5m-smd-5050-60led-rgb-strip-light/PLID70902466/), you can find them anywhere on the internet, they are very cheap and work well for fun hacking with Homekit.

However be aware the one i bought came with a very werid power supply, so maybe buy another one...


## 4. Run the code!
That should be it. You should just be able to run the code now, the accessory version is 3.0, so if you see any updates here, then you'll know to update your own software.

>NB I am still working on the finer things with this project, took ages to get brightness and colour working together, now its just updating the lights whether it be colour or brightness that changes.




Resources used to get this working!
https://www.programmingalgorithms.com/algorithm/hsv-to-rgb/c/
https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
https://github.com/alejandro-n-rivera/arduino_led_rgb_hsv
