# RollCall
A network packet approach to attendance built with an ESP8266 microcontroller.

Utilizes the Wi-Fi capabilities of the ESP8266 microcontroller to detect presence of devices via packets. The ESP8266 is run in promiscuous mode and picks up any network packets. When a saved user's MAC address is found, the corresponding LED with light up, indicating that the user is present.

## Prerequisites
This program can be flashed to the ESP8266 using the Arduino IDE. The ESP8266 board manager must be used. More information can be found in the [ESP8226 repository](https://github.com/esp8266/Arduino). `esppl_functions.h` and `esppl_struct.h` included in this repository are parts of [ESP8266 Promiscuous Library](https://github.com/RicardoOliveira/ESPProLib).

## Usage
Target users should be defined in `RollCall.ino`. Each user should be labeled with their MAC address for identification and a pin number for output. Additionally, users can be assigned names for help with debugging via serial output.

