#include "./esppl_functions.h"

//How long after not seeing someone to update their status - 900000=15 minutes
#define SEEN_INTERVAL 900000
/*
 * Define Users:
 *  - Name
 *  - LED Pin
 *  - MAC Address
 *  Users should have coresponding indices in each list
 */

#define NUM_USERS 4

String userList[NUM_USERS] = {
  "User1",
  "User2",
  "User3",
  "User4"
};

uint8_t pinList[NUM_USERS] = {
  D1,
  D2,
  D3,
  D4
};

uint8_t macAddressList[NUM_USERS][ESPPL_MAC_LEN] = {
   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
  ,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
  ,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

bool isHere[NUM_USERS] = {
  false,
  false,
  false,
  false
};

unsigned long lastSeen[NUM_USERS] = {
  0,
  0,
  0,
  0
};

void updateLeds() {
  unsigned long curr_time = millis();
  for(int user = 0; user < NUM_USERS; user++) {
    if(isHere[user] && (lastSeen[user] + SEEN_INTERVAL) < curr_time) {
      //User is no longer here
      isHere[user] = false;
      digitalWrite(pinList[user], LOW);
    }
  }
}

void checkIn(int user) {
  unsigned long curr_time = millis();
  Serial.printf("%d", user);
  Serial.printf("%l", curr_time);
  if (!isHere[user]) {
    digitalWrite(pinList[user], HIGH);
    isHere[user] = true;
  }
  lastSeen[user] = curr_time;
}

void checkMatches(esppl_frame_info *info) {
  updateLeds();
  uint8_t *rAddr = info->receiveraddr;
  uint8_t *sAddr = info->sourceaddr;
  bool rMatch = true;
  bool sMatch = true;
  for(int user = 0; user < NUM_USERS; user++) {
    for(int i = 0; i < ESPPL_MAC_LEN; i++) {
      if(rMatch && rAddr[i] != macAddressList[user][i]) {
        rMatch = false;
      }
      if(sMatch && sAddr[i] != macAddressList[user][i]) {
        sMatch = false;
      }
    }
    if(rMatch && sMatch) {
      //User is here
      checkIn(user);
    }
  }
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
  esppl_init(checkMatches);
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
