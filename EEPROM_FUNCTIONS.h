//  MAX EEPROM 512 BYTES
//  NAMES
//  32  SSID
//  32  PASSWORD
//  32  Profile 1
//  32  Profile 2
//  32  Profile 3
//  32  Profile 4
//   ------- > 192 bytes for names
//  64 bytes for params
//  -------- > 256 bytes
//  2 bytes actual profile

// WiFi Settings//
char ssid[32];
char password[32];

// NAMES
char profile1[32];
char profile2[32];
char profile3[32];
char profile4[32];
// Parametros 8 por perfil (4 temp 4 time)
int profile_param[32];

int current_profile;

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
   EEPROM.get(192+(i*2), profile_param[i]); 
  }
  EEPROM.get(256, current_profile);
  EEPROM.end();
}

void savedata() {
  EEPROM.begin(512);
  EEPROM.put(0, ssid);
  EEPROM.put(0+sizeof(ssid), password);
  char ok[2+1] = "OK";
  EEPROM.put(0+sizeof(ssid)+sizeof(password), ok);
  EEPROM.commit();
  EEPROM.end();
}


void savewifi() {
  EEPROM.begin(512);
  EEPROM.put(0, ssid);
  EEPROM.put(32, password);
  EEPROM.commit();
  EEPROM.end();
}

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
   EEPROM.put(192+(i*2), profile_param[i]); 
  }

  EEPROM.commit();
  EEPROM.end();
}



