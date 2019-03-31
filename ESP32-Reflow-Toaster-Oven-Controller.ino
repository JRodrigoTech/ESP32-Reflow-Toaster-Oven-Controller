#include <WiFi.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <EEPROM.h>
#include <esp_task_wdt.h>
#include "max6675.h"
#include "EEPROM_FUNCTIONS.h"
#include "html.h"

//int LED_BUILTIN = 14;

TaskHandle_t Tloop0;


// Time Out for AP MODE
const int     conn_time_out = 10000 ;     // in ms
int           time_out = 0 ;

// Temperature controller
unsigned long flagMillis;
unsigned long currentMillis;
const unsigned long period = 1000;  //the value is a number of milliseconds


// Server Settings //
const byte    DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress     apIP(192, 168, 4, 1);    // Private network for server in AP MODE
DNSServer     dnsServer;              // Create the DNS object
WebServer     webServer(80);          // HTTP server
boolean       AP_MODE = false;

// MAX6675
const int   thermoDO = 19;
const int   thermoCS = 5;
const int   thermoCLK = 18;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);


String thermocouple_temp() {
  
  return String(thermocouple.readCelsius());

}


void setup() {
  
  Serial.begin(115200);

  Serial.print("setup() running on core ");
  Serial.println(xPortGetCoreID());
  
  // turn the LED on (HIGH is the voltage level)
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  
  // turn the LED on (HIGH is the voltage level)
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Read EEPROM DATA
  loadEEPROMdata();

  if(current_profile > 4 || current_profile < 1 ){ current_profile=1; }

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

  if(AP_MODE == false){
    
    MDNS.begin("reflow");
    
  }else if(AP_MODE == true){

    // AP WIFI MODE //
    WiFi.mode(WIFI_OFF); // Close the WiFi client connection
    delay(1000);
    
    // configure access point
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("Reflow Controller"); // Sin password
    //WiFi.softAP("Reflow Controller", "1234");   //  Con password
    
    // if DNSServer is started with "*" for domain name, it will reply with
    // provided IP to all DNS request
    dnsServer.start(DNS_PORT, "*", apIP);
     
  }


  digitalWrite(LED_BUILTIN, LOW);

/*
  webServer.on("/", []() {
    webServer.send(200, "text/plain", "this works as well");
  });
*/
  webServer.on("/test", []() {
    webServer.send(200, "text/plain", "this works as well");
  });

  webServer.on("/temp1", []() {
    webServer.send(200, "text/plain", thermocouple_temp() );
  });

  webServer.on("/reflowdata.js", []() {
    webServer.send(200, "text/plain", profiledata(current_profile) );
  });



  
/*
  webServer.on("/style.css", []() {
    webServer.send(200, "text/css", css );
  });
*/
/*
   webServer.on("/ok", []() {
    webServer.send(204);
  });*/


  // Path Arguments from URL
  webServer.on("/wifi/{}/{}", []() {
    String Argument = webServer.pathArg(0);
    Argument.toCharArray(ssid, 32);
    Argument = webServer.pathArg(1);
    Argument.toCharArray(password, 32);
    savewifi();
    
    //webServer.send(200, "text/plain", "SSID: '" + String(ssid) + "' and PWD: '" + String(password) + "'");
    webServer.sendHeader("Location", "/settings/wifi");
    webServer.send(302);
  });

  // Set profile
  webServer.on("/set/{}", []() {
    String Argument = webServer.pathArg(0);
    current_profile = Argument.toInt();
    savecurrentprofile(current_profile);
    webServer.sendHeader("Location", "/");
    webServer.send(302);
  });

  webServer.on("/settings/wifi", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+wifisettings1+String(ssid)+wifisettings2+String(password)+wifisettings3+bottom+webend );
  });


  // Perfil 1
  webServer.on("/settings/profile/1", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+
                                          profileset(1,profile1,profile_param[0],profile_param[1],profile_param[2],profile_param[3],profile_param[4],profile_param[5],profile_param[6],profile_param[7])
                                                +bottom+webend );
  });

  // Perfil 2
  webServer.on("/settings/profile/2", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+
                                          profileset(2,profile2,profile_param[8],profile_param[9],profile_param[10],profile_param[11],profile_param[12],profile_param[13],profile_param[14],profile_param[15])
                                                +bottom+webend );
  });

  // Perfil 3
  webServer.on("/settings/profile/3", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+
                                          profileset(3,profile3,profile_param[16],profile_param[17],profile_param[18],profile_param[19],profile_param[20],profile_param[21],profile_param[22],profile_param[23])
                                                +bottom+webend );
  });

  // Perfil 4
  webServer.on("/settings/profile/4", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+
                                          profileset(4,profile4,profile_param[24],profile_param[25],profile_param[26],profile_param[27],profile_param[28],profile_param[29],profile_param[30],profile_param[31])
                                                +bottom+webend );
  });

/*
  webServer.on("/settings/profile/{}", []() {
    String Argument = webServer.pathArg(0);
    int pts = Argument.toInt();
    char selpro[32];
    
    switch (pts) {
      case 1:
        strcat(selpro,profile1);
        break;
      case 2:
        strcat(selpro,profile2);
        break;
      case 3:
        strcat(selpro,profile3);
        break;
      case 4:
        strcat(selpro,profile4);
        break;
    }

    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+
                                          profileset(pts,selpro,profile_param[0+(8*(pts-1))],profile_param[1+(8*(pts-1))],profile_param[2+(8*(pts-1))],profile_param[3+(8*(pts-1))],profile_param[4+(8*(pts-1))],profile_param[5+(8*(pts-1))],profile_param[6+(8*(pts-1))],profile_param[7+(8*(pts-1))])
                                                +bottom+webend );
  });*/



  // Save Profile
  
  webServer.on("/profile/{}/{}/{}/{}/{}/{}/{}/{}/{}/{}", []() {

    String Argument = webServer.pathArg(0);
    int pts = Argument.toInt();

    Argument = webServer.pathArg(1);

    Argument.replace("%20", " "); // Space
    
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


    // Temperatures
    Argument = webServer.pathArg(2);
    profile_param[0+(8*(pts-1))]= Argument.toInt();
    Argument = webServer.pathArg(3);
    profile_param[1+(8*(pts-1))]= Argument.toInt(); 
    Argument = webServer.pathArg(4);
    profile_param[2+(8*(pts-1))]= Argument.toInt();
    Argument = webServer.pathArg(5);
    profile_param[3+(8*(pts-1))]= Argument.toInt();
    // Times
    Argument = webServer.pathArg(6);
    profile_param[4+(8*(pts-1))]= Argument.toInt();
    Argument = webServer.pathArg(7);
    profile_param[5+(8*(pts-1))]= Argument.toInt(); 
    Argument = webServer.pathArg(8);
    profile_param[6+(8*(pts-1))]= Argument.toInt();
    Argument = webServer.pathArg(9);
    profile_param[7+(8*(pts-1))]= Argument.toInt(); 
    
    saveprofile(pts);

    switch (pts) {
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

    webServer.send(302);
  });

  webServer.on("/reboot", []() {
    webServer.send(200, "text/plain", "Restarting... please wait...");
    ESP.restart();
  });
 
  // replay to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", header+title+menu(current_profile,profile1,profile2,profile3,profile4)+mainhome(current_profile,profile1,profile2,profile3,profile4)+bottom+mainscripts+webend );
  });
  
  webServer.begin();

  flagMillis = millis();  //initial start time

  xTaskCreatePinnedToCore(loop0,"loop0",10000,NULL,1,&Tloop0,0);    /* pin task to core 0 */                    
  
}



void loop() {     // CORE 1

  // Web Server
  if(AP_MODE == true){dnsServer.processNextRequest();}
  webServer.handleClient();

}



void loop0( void * pvParameters ){        // CORE 0
  Serial.print("loop0 running on core ");
  Serial.println(xPortGetCoreID());
  
 while(1) {
      // Oven Controller
      currentMillis = millis();  
      if (currentMillis - flagMillis >= period)  
      {
        digitalWrite(17, !digitalRead(17)); 
        flagMillis = currentMillis; 
      }


       vTaskDelay(10);    // Wacht
    }




}


