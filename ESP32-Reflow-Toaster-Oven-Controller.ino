#include <WiFi.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <EEPROM.h>
#include <esp_task_wdt.h>
#include "max6675.h"
#include "Variables.h"
#include "EEPROM.h"
#include "html.h"

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO); // Initialize library

// Thermocouple Reading function
String thermocouple_temp() {
  return String(thermocouple.readCelsius());
}

void setup() {
  
  //Serial.begin(115200);   // SERIAL DEBUG
  
  // SSR POWER OUTPUT
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);

  // Pre-load EEPROM DATA
  loadEEPROMdata();

  if(current_profile > 4 || current_profile < 1 ){ current_profile=1; }   // Profile Range Delimiter

  // WIFI CLIENT MODE //
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED && AP_MODE == false) {
      delay(500);
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      time_out = time_out + 500 ;
      if(time_out >= conn_time_out){
        AP_MODE = true;
      }
  }

  // WIFI AP MODE if not CLIENT //
  if(AP_MODE == false){   // as CLIENT
    
    MDNS.begin("reflow");   // Bonjour Service > http://reflow.local/
    
  }else if(AP_MODE == true){

    // AP WIFI MODE //
    WiFi.mode(WIFI_OFF); // Close the WiFi client connection
    delay(1000);
    
    // Configure the Access Point
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("Reflow Controller"); // Without password
    //WiFi.softAP("Reflow Controller", "1234");   //  With password
    
    // if DNSServer is started with "*" for domain name, it will reply with
    // provided IP to all DNS request
    dnsServer.start(DNS_PORT, "*", apIP);
     
  }

  // WEB SERVER SOCKET REQUESTS //

  // Reflow Temperatures Array Data
  webServer.on("/reflowdata", []() {    
    webServer.send(200, "text/plain", profileplotprint() );
  });

  // Thermocouple Plain Read
  webServer.on("/temp", []() {
    webServer.send(200, "text/plain", thermocouple_temp() );
  });
  
  // Settings - Wi-Fi
  webServer.on("/settings/wifi", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+wifisettings1+String(ssid)+wifisettings2+String(password)+wifisettings3+bottom+webend);
  });

  // Settings - Profile 1
  webServer.on("/settings/profile/1", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+profileset(1)+bottom+webend );
  });

  // Settings - Profile 2
  webServer.on("/settings/profile/2", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+profileset(2)+bottom+webend );
  });

  // Settings - Profile 3
  webServer.on("/settings/profile/3", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+profileset(3)+bottom+webend );
  });

  // Settings - Profile 4
  webServer.on("/settings/profile/4", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+profileset(4)+bottom+webend );
  });

  // Wi-Fi save config. with path arguments from URL
  webServer.on("/wifi/{}/{}", []() {
    String Argument = webServer.pathArg(0);
    Argument.toCharArray(ssid, 32);
    Argument = webServer.pathArg(1);
    Argument.toCharArray(password, 32);
    savewifi();
    webServer.sendHeader("Location", "/settings/wifi");
    webServer.send(302);  // Code 302 - Found - Resource requested has been temporarily moved to the URL given by the Location
  });

  // Set profile and return to home
  webServer.on("/set/{}", []() {
    String Argument = webServer.pathArg(0);
    current_profile = Argument.toInt();
    savecurrentprofile(current_profile);
    webServer.sendHeader("Location", "/");
    webServer.send(302);  // Code 302 - Found - Resource requested has been temporarily moved to the URL given by the Location
  });

  // Save Profile Data
  webServer.on("/profile/{}/{}/{}/{}/{}/{}/{}/{}/{}/{}", []() {

    String Argument = webServer.pathArg(0);
    int pts = Argument.toInt();     // Profile Number

    Argument = webServer.pathArg(1);  // Profile Name

    Argument.replace("%20", " ");   // Replace URL Space char
    
    switch (pts) {
      case 1:
        Argument.toCharArray(profile1, 32);
        break;
      case 2:
        Argument.toCharArray(profile2, 32);
        break;
      case 3:
        Argument.toCharArray(profile3, 32);
        break;
      case 4:
        Argument.toCharArray(profile4, 32);
        break;
    }

    // Temperature Arguments
    Argument = webServer.pathArg(2);
    profile_param[0+(8*(pts-1))]= Argument.toInt();
    Argument = webServer.pathArg(3);
    profile_param[1+(8*(pts-1))]= Argument.toInt(); 
    Argument = webServer.pathArg(4);
    profile_param[2+(8*(pts-1))]= Argument.toInt();
    Argument = webServer.pathArg(5);
    profile_param[3+(8*(pts-1))]= Argument.toInt();
    // Time Arguments
    Argument = webServer.pathArg(6);
    profile_param[4+(8*(pts-1))]= Argument.toInt();
    Argument = webServer.pathArg(7);
    profile_param[5+(8*(pts-1))]= Argument.toInt(); 
    Argument = webServer.pathArg(8);
    profile_param[6+(8*(pts-1))]= Argument.toInt();
    Argument = webServer.pathArg(9);
    profile_param[7+(8*(pts-1))]= Argument.toInt(); 
    
    saveprofile(pts);   // Save params to the EEPROM

    switch (pts) {      // Web page redirect
      case 1:
        webServer.sendHeader("Location", "/settings/profile/1");
        break;
      case 2:
        webServer.sendHeader("Location", "/settings/profile/2");
        break;
      case 3:
        webServer.sendHeader("Location", "/settings/profile/3");
        break;
      case 4:
        webServer.sendHeader("Location", "/settings/profile/4");
        break;
    }
    webServer.send(302);  // Code 302 - Found - Resource requested has been temporarily moved to the URL given by the Location
  });

  // Reboot the board
  webServer.on("/reboot", []() {
    webServer.send(200, "text/html", "Restarting... please wait... <a style=\"color: teal;\" href=\"/\">Home Page</a>"+jsreboot );
    ESP.restart();
  });

  // Start Reflow
  webServer.on("/start", []() {
    webServer.sendHeader("Location", "/");
    webServer.send(302);  // Code 302 - Found - Resource requested has been temporarily moved to the URL given by the Location
    REFLOW_STATUS = true;
  });

  // Stop Reflow
  webServer.on("/stop", []() {
    webServer.sendHeader("Location", "/");
    webServer.send(302);  // Code 302 - Found - Resource requested has been temporarily moved to the URL given by the Location
    REFLOW_STATUS = false;
  });

  // Replay to all not defined requests with same home HTML file
  webServer.onNotFound([]() {
    if(AP_MODE == true){
    webServer.send(200, "text/html", header+title+menu(apIP[0],apIP[1],apIP[2],apIP[3])+mainhome()+bottom+profiledata(current_profile)+mainscripts+webend );  
    } else {
    webServer.send(200, "text/html", header+title+menu(WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3])+mainhome()+bottom+profiledata(current_profile)+mainscripts+webend );
    }
  });
  
  webServer.begin();      // Starts the previous defined Web Server Sockets

  flagMillis = millis();  // Initial start time

  // Starts the loop0() on CORE 0 (By default the main loop() is running on CORE 1)
  xTaskCreatePinnedToCore(loop0,"loop0",10000,NULL,1,&Tloop0,0);    /* pin task to core 0 */                    
  
}

// WEB SERVER // CORE 1 //
void loop() {
  // DNS Server for Wi-Fi in AP MODE
  if(AP_MODE == true){dnsServer.processNextRequest();}
  // Web Server Client Handler
  webServer.handleClient();
}

// CONTROL // LCD // CORE 0 //
void loop0( void * pvParameters ){
        Serial.print("loop0 running on core ");
        Serial.println(xPortGetCoreID());
 while(1){

  currentMillis = millis();  

  if(REFLOW_STATUS == true){

    if(prev_REFLOW_STATUS == false){   // Reflow initialized
      temps_pos = 0;
      temp_acqui = thermocouple.readCelsius();
      prev_temp_acqui = temp_acqui;
      Degsec = 0 ;
      digitalWrite(17, HIGH);
      reflow_pos = 1;
      
      reflow_wait = currentMillis;
      plot_flag = currentMillis;
      acquisition_flag = currentMillis;
      control_flag = currentMillis;
      PWM_flag = currentMillis;
      prev_REFLOW_STATUS = true;
    }


    // Oven Temperature acquisition ( every 300 ms ) ( 10 x 2 sec )
    if (currentMillis - acquisition_flag >= 300)  
    {
      if( temps_pos >= 10 ){
        Degsec = ((temp_acqui - prev_temp_acqui)*100) / 3 ;
        prev_temp_acqui = temp_acqui;
        temps_pos = 0 ;
      }
      int tempstemp = thermocouple.readCelsius();
      if( ( (temp_acqui-tempstemp) > -25) && ( (temp_acqui-tempstemp) < 25) ){
           temp_acqui = (temp_acqui + tempstemp) / 2 ;
      }
      ++temps_pos;
      acquisition_flag = currentMillis; 
    }


    // Oven PWM Power Controller  ( variable )
    if(currentMillis - PWM_flag >= 1000){
      
      if(PWM_period > 20){
        digitalWrite(17, HIGH);
      }     

      PWM_flag = currentMillis; 
      
    }else if(currentMillis - PWM_flag >= PWM_period){
      
      if(PWM_period < 980){
        digitalWrite(17, LOW);
      }
    
    }


    // Oven Power Controller  ( every 1000 ms )
    if (currentMillis - control_flag >= 1000)  
    {
          
      PWM_period = PWM_period + ((ramp(current_profile,reflow_pos)-Degsec));

        if ( PWM_period > 1000 ){PWM_period=1000;}
        if ( PWM_period < 0 ){PWM_period=0;}

      if( ramp(current_profile,reflow_pos) == 0 ){
        
          if (currentMillis - reflow_wait >= maxtime(current_profile,reflow_pos) ){
              ++reflow_pos;
              reflow_wait = currentMillis;
          }
          
      }else{
        
        if( maxtempoint(current_profile,reflow_pos) <= (temp_acqui+15) ){
          ++reflow_pos;
          reflow_wait = currentMillis;
        }
      }
      if(reflow_pos >= 5){REFLOW_STATUS=false;}
      control_flag = currentMillis; 
      
    }


    // Oven Live Plot ( every 5000 ms )
    if ((currentMillis - plot_flag >= 5000) && (plotleg < 138))  
    { 
      plotdata[2*plotleg] = temp_acqui;
      plotdata[2*plotleg+1] = plotleg*5;
      plotleg=plotleg+1;
      plot_flag = currentMillis; 
    }

  }else{  // REFLOW_STATUS != true
      digitalWrite(17, LOW);      // Disable Power
      prev_REFLOW_STATUS = false;
  }  // ENF IF REFLOW_STATUS
  
       vTaskDelay(10);   // Watchdog trigger fix
 } // END while(1)
} // END loop0()
