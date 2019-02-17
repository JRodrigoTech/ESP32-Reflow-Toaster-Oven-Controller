#include <WiFi.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include <WebServer.h>
#include "max6675.h"
#include "html.h"

//int LED_BUILTIN = 14;

// WiFi Settings//
const char*   ssid     = "JRodrigo";
const char*   password = "YourWifiPassword";
// Time Out for AP MODE
const int     conn_time_out = 10000 ;     // in ms
int           time_out = 0 ;

// Server Settings //
const byte    DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress     apIP(10, 10, 10, 10);    // Private network for server in AP MODE
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
  // turn the LED on (HIGH is the voltage level)
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

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
    WiFi.softAP("Free WiFi"); // WiFi name
    
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
/*
  webServer.on("/style.css", []() {
    webServer.send(200, "text/css", css );
  });
*/
/*
   webServer.on("/ok", []() {
    webServer.send(204);
  });*/

  // replay to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", header+title+menu+main+right+bottom);
  });
  
  webServer.begin();
}

void loop() {
  if(AP_MODE == true){dnsServer.processNextRequest();}
  webServer.handleClient();


}
