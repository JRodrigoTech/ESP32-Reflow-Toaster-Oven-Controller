// LCD Variables
int LCD_screen = 0;
int temp_LCD,prev_temp_LCD,prev_LCD_profile;
boolean LCDtempread = false;
boolean prev_RFLW = false;
unsigned long LCD_temp_flag;

// TFT Print Profiles
void LCDPrintProfiles(boolean initz) {
  if(initz == false){
    tft.fillScreen(ILI9341_BLACK);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_BLACK);
    tft.fillRect(0, 0, 320, 18, ILI9341_BLUE); 
    tft.setCursor(2, 2);
    tft.println("Reflow Profil List");
  }else{
    tft.fillRect(0, 19, 320, 80, ILI9341_BLACK); 
    tft.fillRect(0, 19, 320, 80, ILI9341_BLACK);     
  }
  String txt = String(profile1);
  ///Print current_profile  in LIGHT_YELLOW
  for (int i = 1; i <= 4; i++) {

    if(current_profile == i){
      tft.fillRect(0,20*i,320,18, LIGHT_YELLOW);
      tft.setTextColor(ILI9341_BLACK);
    }else{
      tft.setTextColor(ILI9341_BLUE);
    }
    
    tft.setCursor(2,(20*i)+2);
    switch (i) {
        case 1:
          //txt = String(profile1);
          txt.remove(26, 5);
          tft.println(txt);
          break;
        case 2:
          txt = String(profile2);
          txt.remove(26, 5);
          tft.println(txt);
          break;
        case 3:
          txt = String(profile3);
          txt.remove(26, 5);
          tft.println(txt);
          break;
        case 4:
          txt = String(profile4);
          txt.remove(26, 5);
          tft.println(txt);
          break;
    }
  } // END FOR
}

// TFT Profiles Change
void LCDChangeProfiles(int current, int prev){
  String txt = String(profile1);
  int set = prev;
  for(int i = 0; i <= 1; i++){
  
    if(i==0){
        tft.fillRect(0, (20*prev)-1, 320, 21, ILI9341_BLACK); 
        tft.fillRect(0, (20*prev)-1, 320, 21, ILI9341_BLACK);  
        tft.setTextColor(ILI9341_BLUE);
        tft.setCursor(2,(20*prev)+2);
        
    }else if(i==1){
        tft.fillRect(0,20*current,320,18, LIGHT_YELLOW);
        tft.setTextColor(ILI9341_BLACK);
        tft.setCursor(2,(20*current)+2);
        set = current;
    }
	switch (set) {
	  case 1:
		//txt = String(profile1);
		txt.remove(26, 5);
		tft.println(txt);
		break;
	  case 2:
		txt = String(profile2);
		txt.remove(26, 5);
		tft.println(txt);
		break;
	  case 3:
		txt = String(profile3);
		txt.remove(26, 5);
		tft.println(txt);
		break;
	  case 4:
		txt = String(profile4);
		txt.remove(26, 5);
		tft.println(txt);
		break;
	}
  }// END FOR
}

// LCD Print Bottom Temperatura
void LCDPrintTemp(boolean initz, int tempread){
  if(initz == false){
    tft.fillRect(0, 221, 320, 19, LIGHT_GRAY); 
    tft.setTextSize(2);
    tft.setCursor(2, 223);
    tft.setTextColor(DARK_RED);
    tft.print("Temperature:");
  }else if(tempread < 0){
    tft.fillRect(145, 221, 320, 19, LIGHT_GRAY);
    tft.fillRect(145, 221, 320, 19, LIGHT_GRAY);
    tft.setTextSize(2);
    tft.setCursor(146, 223);
    tft.setTextColor(DARK_RED);
    tft.print("Not Connected");
  }else if(initz == true){
    tft.fillRect(145, 221, 320, 19, LIGHT_GRAY);
    tft.fillRect(145, 221, 320, 19, LIGHT_GRAY);
    tft.setTextSize(2);
    tft.setCursor(146, 223);
    tft.setTextColor(DARK_RED);
    tft.print(tempread);
    tft.print((char)247);  
    tft.print("C");
  }
}

// LCD Print Reflow Status On/Off
void LCDReflowStatus(boolean initz){
  if(initz == true){
    tft.fillRect(294, 0, 320, 18, ILI9341_BLUE);
    tft.fillRect(294, 0, 320, 18, ILI9341_BLUE);
    tft.setTextSize(2);
    tft.setCursor(295, 2);
    tft.setTextColor(ILI9341_GREEN);
    tft.print("ON");
  }else if(initz == false){
    tft.fillRect(294, 0, 320, 18, ILI9341_BLUE);
    tft.fillRect(294, 0, 320, 18, ILI9341_BLUE);
  }
}