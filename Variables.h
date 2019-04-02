// PIN DEFINITIONS //
// MAX6675 Pins
const int   thermoDO = 19;
const int   thermoCS = 5;
const int   thermoCLK = 18;





// Time Out for AP MODE
const int     conn_time_out = 10000 ;     // in ms
int           time_out = 0 ;

// Server Settings //
const byte    DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress     apIP(192, 168, 4, 1);    // Private network for server in AP MODE
DNSServer     dnsServer;              // Create the DNS object
WebServer     webServer(80);          // HTTP server
boolean       AP_MODE = false;



// Dual Core Control loop on CORE 0
TaskHandle_t  Tloop0;
boolean       REFLOW_STATUS = false;      // Reflow process status (on/off)
boolean       prev_REFLOW_STATUS = false;




// No delay variables
unsigned long currentMillis;
unsigned long control_flag;
unsigned long acquisition_flag;
unsigned long plot_flag;
unsigned long PWM_flag;
unsigned long reflow_wait;
long PWM_period = 1000;




unsigned long flagMillis;



const unsigned long period = 1000;  // in ms (delete)
const unsigned long rflw_period = 500;  // in ms



// Reflow Control variables
int temps_pos, temp_acqui, prev_temp_acqui, Degsec, reflow_pos;




// Plot Data Arrays
int plotdata[276];
int plotleg=0;
