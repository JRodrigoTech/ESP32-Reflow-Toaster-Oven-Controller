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


int ramp(int profile,int pos){

  int profileramp = 0;
  
  switch (pos) {
    case 1:
      profileramp = ((profile_param[(0+8*(profile-1))]-25)*100)/profile_param[(4+8*(profile-1))];
      break;
    case 2:
      profileramp = ((profile_param[(1+8*(profile-1))]-profile_param[(0+8*(profile-1))])*100)/(profile_param[(5+8*(profile-1))]-profile_param[(4+8*(profile-1))]);
      break;
    case 3:
      profileramp = ((profile_param[(2+8*(profile-1))]-profile_param[(1+8*(profile-1))])*100)/(profile_param[(6+8*(profile-1))]-profile_param[(5+8*(profile-1))]);
      break;
    case 4:
      profileramp = ((profile_param[(3+8*(profile-1))]-profile_param[(2+8*(profile-1))])*100)/(profile_param[(7+8*(profile-1))]-profile_param[(6+8*(profile-1))]);
      break;
  }

    return profileramp;
    
}

int maxtempoint(int profile,int pos){

  int returnvalue = 0;
  
  switch (pos) {
    case 1:
      returnvalue = profile_param[(0+8*(profile-1))];
      break;
    case 2:
      returnvalue = profile_param[(1+8*(profile-1))];
      break;
    case 3:
      returnvalue = profile_param[(2+8*(profile-1))];
      break;
    case 4:
      returnvalue = profile_param[(3+8*(profile-1))];
      break;
  }

    return returnvalue;
    
}


int maxtime(int profile,int pos){

  int returnvalue = 0;
  
  switch (pos) {
    case 1:
      returnvalue = profile_param[(4+8*(profile-1))]*1000;
      break;
    case 2:
      returnvalue = (profile_param[(5+8*(profile-1))]-profile_param[(4+8*(profile-1))])*1000;
      break;
    case 3:
      returnvalue = (profile_param[(6+8*(profile-1))]-profile_param[(5+8*(profile-1))])*1000;
      break;
    case 4:
      returnvalue = (profile_param[(7+8*(profile-1))]-profile_param[(6+8*(profile-1))])*1000;
      break;
  }

    return returnvalue;
    
}
