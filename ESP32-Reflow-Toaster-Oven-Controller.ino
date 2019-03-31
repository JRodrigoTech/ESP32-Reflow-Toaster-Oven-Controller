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

// Dual Core Control loop on CORE 0
TaskHandle_t  Tloop0;
boolean       REFLOW_STATUS = false;      // Reflow process status (on/off)

// Time Out for AP MODE
const int     conn_time_out = 10000 ;     // in ms
int           time_out = 0 ;

// No delay variables
unsigned long flagMillis;
unsigned long currentMillis;
const unsigned long period = 1000;  // in ms (delete)
const unsigned long rflw_period = 500;  // in ms


// Server Settings //
const byte    DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress     apIP(192, 168, 4, 1);    // Private network for server in AP MODE
DNSServer     dnsServer;              // Create the DNS object
WebServer     webServer(80);          // HTTP server
boolean       AP_MODE = false;

// MAX6675 Pins
const int   thermoDO = 19;
const int   thermoCS = 5;
const int   thermoCLK = 18;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO); // Initialize library

// Thermocouple Reading function
String thermocouple_temp() {
  return String(thermocouple.readCelsius());
}

void setup() {
  
  Serial.begin(115200);   // SERIAL DEBUG

  Serial.print("setup() running on core ");
  Serial.println(xPortGetCoreID());
  
                // turn the LED on (HIGH is the voltage level)
                pinMode(17, OUTPUT);
                digitalWrite(17, LOW);
                
                // turn the LED on (HIGH is the voltage level)
                pinMode(LED_BUILTIN, OUTPUT);
                digitalWrite(LED_BUILTIN, LOW);

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


          digitalWrite(LED_BUILTIN, LOW);

  // WEB SERVER SOCKET REQUESTS //
/*
  webServer.on("/", []() {
    webServer.send(200, "text/plain", "Hello World");
  });
*/
  // Thermocouple Plain Read
  webServer.on("/temp1", []() {
    webServer.send(200, "text/plain", thermocouple_temp() );
  });
  
  // Reflow Temperatures Array Data
  webServer.on("/reflowdata.js", []() {
    webServer.send(200, "text/plain", profiledata(current_profile) );
  });

  // Settings - Wi-Fi
  webServer.on("/settings/wifi", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+wifisettings1+String(ssid)+wifisettings2+String(password)+wifisettings3+bottom+webend);
  });

  // Settings - Profile 1
  webServer.on("/settings/profile/1", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+profileset(1,profile1,profile_param[0],profile_param[1],profile_param[2],profile_param[3],profile_param[4],profile_param[5],profile_param[6],profile_param[7])+bottom+webend );
  });

  // Settings - Profile 2
  webServer.on("/settings/profile/2", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+profileset(2,profile2,profile_param[8],profile_param[9],profile_param[10],profile_param[11],profile_param[12],profile_param[13],profile_param[14],profile_param[15])+bottom+webend );
  });

  // Settings - Profile 3
  webServer.on("/settings/profile/3", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+profileset(3,profile3,profile_param[16],profile_param[17],profile_param[18],profile_param[19],profile_param[20],profile_param[21],profile_param[22],profile_param[23])+bottom+webend );
  });

  // Settings - Profile 4
  webServer.on("/settings/profile/4", []() {
    webServer.send(200, "text/html", header+title+settingsmenu+setprojava+profileset(4,profile4,profile_param[24],profile_param[25],profile_param[26],profile_param[27],profile_param[28],profile_param[29],profile_param[30],profile_param[31])+bottom+webend );
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
    webServer.send(200, "text/plain", "Restarting... please wait...<a style=\"color: teal;\" href=\"/\">Home Page</a>"+jsreboot );
    ESP.restart();
  });
 
  // Replay to all not defined requests with same home HTML file
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", header+title+menu(current_profile,profile1,profile2,profile3,profile4)+mainhome(current_profile,profile1,profile2,profile3,profile4)+bottom+mainscripts+webend );
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


      // Oven Controller
      currentMillis = millis();  
      if (currentMillis - flagMillis >= period)  
      {
        digitalWrite(17, !digitalRead(17)); 
        flagMillis = currentMillis; 
      }


       vTaskDelay(10);   // Watchdog trigger fix
 } // END while(1)
} // END loop0()
