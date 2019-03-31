//  EEPROM 512 BYTES
//  ------------------------------
//  32  SSID          { NAMES }
//  32  PASSWORD
//  32  Profile 1
//  32  Profile 2
//  32  Profile 3
//  32  Profile 4
//  + ------ > 192 bytes for names
//  128 bytes for 4 Byte params[]
//  + ------ > 320 bytes
//  4 bytes actual profile

// WiFi Settings
char ssid[32];
char password[32];

// Profile Names
char profile1[32];
char profile2[32];
char profile3[32];
char profile4[32];

// 4 Profiles * ( 4 Temps ; 4 Time )
int profile_param[32];

// Current Selected Profile
int current_profile;

// Load all EEPROM data
void loadEEPROMdata() {
  EEPROM.begin(512);
  // NAMES
  EEPROM.get(0, ssid);
  EEPROM.get(32, password);
  EEPROM.get(64, profile1);
  EEPROM.get(96, profile2);
  EEPROM.get(128, profile3);
  EEPROM.get(160, profile4); 
  // Profile Params
  for (int i = 0; i < 32; i = i + 1) {
   EEPROM.get(192+(i*4), profile_param[i]); 
  }
  EEPROM.get(400, current_profile);
  EEPROM.end();
}

// Save Wi-Fi Credentials
void savewifi() {
  EEPROM.begin(512);
  EEPROM.put(0, ssid);
  EEPROM.put(32, password);
  EEPROM.commit();
  EEPROM.end();
}

// Save Profile Settings
void saveprofile(int num){
  EEPROM.begin(512);
  switch (num) {
    case 1:
      EEPROM.put(64, profile1);
      break;
    case 2:
      EEPROM.put(96, profile2);
      break;
    case 3:
      EEPROM.put(128, profile3);
      break;
    case 4:
      EEPROM.put(160, profile4);
      break;
  }
  // Profile Params
  for (int i = (0 + 8*(num-1) ) ; i < 8*num ; i = i + 1) {
   EEPROM.put(192+(i*4), profile_param[i]); 
  }
  EEPROM.commit();
  EEPROM.end();
}

// Save Current Selected Profile
void savecurrentprofile(int num){
  EEPROM.begin(512);
  EEPROM.put(400, num);
  EEPROM.commit();
  EEPROM.end();
}
