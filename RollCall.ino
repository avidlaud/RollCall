#include "./esppl_functions.h"

/*
 * Define Users:
 *  - Name
 *  - LED Pin
 *  - MAC Address
 *  Users should have coresponding indices in each list
 */

String userList[] = {
  "User1",
  "User2",
  "User3",
  "User4"
}

uint8_t ledList[] = {
  D1,
  D2,
  D3,
  D4
}

uint8_t macAddressList[][ESPPL_MAC_LEN] = {
   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
  ,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
  ,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
}

void setup() {
  static const uint8_t D0 = 16;
  static const uint8_t D1 = 5;
  static const uint8_t D2 = 4;
  static const uint8_t D3 = 0;
  static const uint8_t D4 = 2;
  static const uint8_t D5 = 14;
  static const uint8_t D6 = 12;
  static const uint8_t D7 = 13;
  static const uint8_t D8 = 15;
  static const uint8_t D9 = 3;
  static const uint8_t D10 = 1;
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D5, OUTPUT);
  Serial.begin(115200);
  esppl_init(cb);
}

void loop() {
  esppl_sniffing_start();
  while (true) {
    for (int i = ESPPL_CHANNEL_MIN; i <= ESPPL_CHANNEL_MAX; i++ ) {
      esppl_set_channel(i);
      while (esppl_process_frames()) {
        //
      }
    }
  }  
}
