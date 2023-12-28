#include <Arduino.h>
#include <WiFi.h>
// #include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <EEPROM.h>

#define LED 2
#define RXD2 16
#define TXD2 17
#define box_count 6
#define Wifi_Switch 23
#define Manual_Switch 22

#define box_ip "192.178.678.555"
#define polling_time 2000

#ifndef STASSID
#define STASSID "Vendigo-3"
#define STAPSK  "versicles123"
#endif


#define get_link "https://locker-api.versicles.com/locker/645e48406dd4d02438dea2c6.json"  //Update this link for different lockers
#define parse_check "{\"id\": \"645e48406dd4d02438dea2c6\""                               //update this json response for every locker
#define put_link "https://locker-iot-api.versicles.com/locker-box"                        //Update this link for different lockers
//////////////////////////////////////////////////////////////////////////////
//Variables
int i = 0;
int statusCode;
const char* ssid = STASSID;
const char* passphrase = STAPSK;
//Server1 Variables
String st;
String content;
String esid;
String epass = "";
//Server2 variables
String header;        // Variable to store the HTTP request
//////////////////////////////////////////////////////////////////////////////
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;    //(example: 2000ms = 2s)

//////////////////////////////////////////////////////////////////////////////
const char* put_host = "https://locker-iot-api.versicles.com";
const uint16_t port = 443;
//////////////////////////////////////////////////////////////////////////////
const char* rootCACertificate = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
"-----END CERTIFICATE-----\n";
//////////////////////////////////////////////////////////////////////////////
bool Wifi_Connected = false;
bool Send_trigger = false;
bool state = HIGH;
int send_response = 0;

String web_sequence = "";   //"0:0:0:0:0:0:0:0:0:0:0:0:&"
bool Unlock_doors_keep_food[] = {false,false,false,false,false,false};
bool Unlock_doors_Collect_food[] = {false,false,false,false,false,false};

bool response_is_locked[] =  {true, true, true, true, true, true};
bool response_is_Occupied[] = {false,false,false,false,false,false};
bool response_temp_threshold[] = {false,false,false,false,false,false};
bool update_boxes[] = {false,false,false,false,false,false};
bool response_sent[] = {false,false,false,false,false,false};

bool push_web_status = true;
bool Internet_down = false;
bool Internet_status_down = false;
bool load_wifi_config_page = true;
bool Manual_Control_Server_Configured = false;

String locker_box_ids[] ={"645e48416dd4d02438dea2c7","645e48416dd4d02438dea2c8","645e48416dd4d02438dea2c9","645e48416dd4d02438dea2ca","645e48416dd4d02438dea2cb","645e48416dd4d02438dea2cc"};

// HardwareSerial Serial2(2) // use UART2
//////////////////////////////////////////////////////////////////////////////
//Function Decalration
bool testWifi(void);
void launchWeb(void);
void setupAP(void);
//////////////////////////////////////////////////////////////////////////////
// Not sure if WiFiClientSecure checks the validity date of the certificate. 
// Setting clock just to be sure...
void setClock() {
  configTime(0, 0, "pool.ntp.org");

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  while (nowSecs < 8 * 3600 * 2) {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }

  Serial.println();
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
  Serial.print(F("Current time: "));
  Serial.print(asctime(&timeinfo));
}
//////////////////////////////////////////////////////////////////////////////
// WiFiMulti WiFiMulti;

//Establishing Local server at port 80
WebServer server(80);

//////////////////////////////////////////////////////////////////////////////
void setup(){
	Serial.begin(9600);
	Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
	pinMode(Wifi_Switch, INPUT_PULLUP);
	pinMode(Manual_Switch, INPUT_PULLUP);

	Serial.println("Disconnecting current wifi connection");
  WiFi.disconnect();
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  //---------------------------------------- Read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");

  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  ////////////////////////////
  Serial.println("Reading EEPROM pass");

  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);


  WiFi.begin(esid.c_str(), epass.c_str());
  delay(5000);
  if ((WiFi.status() == WL_CONNECTED))
  {
  		digitalWrite(LED, HIGH);
  		Wifi_Connected = true;
      // Serial.print("Connected to ");
      // Serial.print(esid);
      // Serial.println(" Successfully");
      delay(2000);
  }
  else{
  	Wifi_Connected = false;
  	digitalWrite(LED, LOW);
    Serial.print("Issue with SSID and Password");
  }

	if(Wifi_Connected) Get_web_Status();
}
//////////////////////////////////////////////////////////////////////////////
void loop(){
	unsigned long last_Time;

	if(push_web_status && Wifi_Connected){
		if(Serial2.available()){
			char command = Serial2.read();
			if((command == 'S') && !Send_trigger){
				// Serial.println("Command S detected");
				Serial2.flush();
				delay(500);
				Serial2.println(web_sequence);
				delay(500);
				Serial2.flush();
				// Serial2.flush();
				digitalWrite(LED, state);
				state =!state;
			}
			else if(command == 's'){
				// Serial.println("Command small 's' detected");
				Send_trigger = true;
				web_sequence = "";
				push_web_status = false;
				Serial2.flush();
				digitalWrite(LED, HIGH);		
				// Serial.println("Samll s trigger!!!!!!!");
			}
		}	
	}
	
	if(Send_trigger && Wifi_Connected){
		delay(polling_time);
		digitalWrite(LED, HIGH);
		Get_web_Status();
		if(send_response){  //Sending response to Master Controller
			// Serial.println("Sending Response to Master");
			////Unlocking doors here////////////////////////////////////////////////	
			for(int i=0; i<box_count; i++){
				if(Unlock_doors_keep_food[i]){
					// Serial.println("Keep Food!!");
					if(i == 0) Serial2.println("A");
					else if(i == 1) Serial2.println("B");
					else if(i == 2) Serial2.println("C");
					else if(i == 3) Serial2.println("D");
					else if(i == 4) Serial2.println("E");
					else if(i == 5) Serial2.println("F");

				}
				else if(Unlock_doors_Collect_food[i]){
					// Serial.println("Collect Food >>>>>>>>>");
					if(i == 0) Serial2.println("a");
					else if(i == 1) Serial2.println("b");
					else if(i == 2) Serial2.println("c");
					else if(i == 3) Serial2.println("d");
					else if(i == 4) Serial2.println("e");
					else if(i == 5) Serial2.println("f");
				} 
			}
			///////////////////////////////////////////////////////////////////////
			//Requesting Sensor data from Master///////////////////////////////////
			// Serial2.println("X");     //Command to request sensor data
			
			//Manipulating Sensor data here ----> received from Master
			for(int i=0; i<box_count; i++){
				if(Unlock_doors_keep_food[i]){
					response_is_locked[i] = true; 
					response_is_Occupied[i] = true; 
					response_temp_threshold[i] = false;	
					update_boxes[i] = true;
				}
				else if(Unlock_doors_Collect_food[i]){
					response_is_locked[i] = true; 
					response_is_Occupied[i] = false; 
					response_temp_threshold[i] = false;		
					update_boxes[i] = true;
				}
			}

			update_response(); //Updating response to the server
			///////////////////////////////////////////////////////////////////////
		}
	}

	if(!(testWifi() && (digitalRead(Wifi_Switch) == 1) )) {
    unsigned long int start_time = millis();
    while(1){
      if(millis() - start_time > 5000) {break;}
      else{
        if(digitalRead(Wifi_Switch) == 1) {Wifi_Connected = false;break;}
        else{
        		if(digitalRead(Manual_Switch) == 0) {load_wifi_config_page=false;break;}
        		else {load_wifi_config_page=true;}
        } 
      }
    }
    if((digitalRead(Wifi_Switch) == 0) && load_wifi_config_page){
      // Serial.println("Connection Status Negative / D15 HIGH");
      Serial.println("Turning the HotSpot On");
      Serial2.println("X");	//Capital X   -->> Turn Off MAchine Light's
      digitalWrite(LED, LOW);
      launchWeb();
      setupAP();// Setup HotSpot
      Serial.println();
      Serial.println("Waiting.");
      // digitalWrite(LED, HIGH);

      while ((WiFi.status() != WL_CONNECTED))
      {
        Serial.print(".");
        delay(100);
        server.handleClient();
      }
      delay(1000);
    }else{
    	for(int i=0; i<3; i++){
    		state =!state;
    		digitalWrite(LED, state);
				delay(100);
				state =!state;
				digitalWrite(LED, state);	
				delay(100);
    	}
   		Wifi_Connected = false;
    }
  }

  if(!Wifi_Connected && (digitalRead(Manual_Switch) == 0)){
  	if(!Manual_Control_Server_Configured){
  		Serial.println("Turning the HotSpot On");
	    Serial2.println("X");	//Capital X   -->> Turn Off MAchine Light's
	    digitalWrite(LED, LOW);
	    launchWebApp(); // WebApp for Manual Control
	    setupAP2();     // Setup HotSpot 2	
	    Manual_Control_Server_Configured = true;
  	}
  	else{
  		RunWebServer2();
  	}
  }
  else{
  	load_wifi_config_page = true;
  	if(digitalRead(Manual_Switch) == 1) {if(Manual_Control_Server_Configured) {delay(5000);ESP.restart();}}
  	else Manual_Control_Server_Configured = false;
  }

  if(!Wifi_Connected || Internet_down){
  	last_Time = millis();
  	while(millis() - last_Time < 10000){
  		if(testWifi()) {Wifi_Connected = true;break;}
  	}
  	if(Wifi_Connected && Internet_down)  {
  		if(!Internet_status_down){
  			Serial2.flush();
  			Serial2.println("X");	//Capital X   -->> Turn Off MAchine Light's
  			Serial2.flush();
  			Internet_status_down = true;
  		}  		
  	}else {
  		if(!Wifi_Connected)  {
	  		if(!Internet_status_down){
	  			Serial2.flush();
	  			Serial2.println("X");	//Capital X   -->> Turn Off MAchine Light's
	  			Serial2.flush();
	  			Internet_status_down = true;
  			}
  		}
  	}
  }
  else{
  	if(Internet_status_down){
  		Serial2.flush();
  		Serial2.println("x");	//Small X   --> Turn On Machine Lights
  		Serial2.flush();
  		Internet_status_down = false;
  	}
  }

  if(!Wifi_Connected || Internet_down){
  	for(int i=0; i<3; i++){
    		state =!state;
    		digitalWrite(LED, state);
    		delay(100);
    		state =!state;
				digitalWrite(LED, state);	
				delay(100);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Get_web_Status(){
	int index=0;
	WiFiClientSecure *client = new WiFiClientSecure;
	if(client) {
	client -> setCACert(rootCACertificate);
	HTTPClient https;

	{
	  String line; 
	  /////////////////////////fetching data here///////////////////////////////////////////////
	  if (https.begin(*client, get_link)) {  // HTTPS
	    int httpCode = https.GET();

	    // httpCode will be negative on error
	    if (httpCode > 0) {
	      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
	        line = https.getString();
	        Internet_down = false;
	      }
	    }
	    else{
	    	Serial.println("Internet_down");
	    	Internet_down = true;
	    } 
	    https.end();
	  }
	  // Use https://arduinojson.org/v6/assistant to compute the capacity.
	  const size_t capacity = 3072; //JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;   //3072
	  DynamicJsonDocument doc(capacity);

	  // Parse JSON object
	  DeserializationError error = deserializeJson(doc, line);
	  if (error) {
	    return;
	  }
	  const char* id = doc["id"]; // "645xxxxxxxxxxxxxxxxxxxc6" 645e48406dd4d02438dea2c6
	  const char* name = doc["name"]; // "rcity locker 1"

	  for (JsonObject locker_boxe : doc["locker_boxes"].as<JsonArray>()) {

	    const char* locker_boxe_id = locker_boxe["id"]; // "64xxxxxxxxxxxxx4", ...
	    int locker_boxe_number = locker_boxe["number"]; // 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
	    bool locker_boxe_is_locked = locker_boxe["is_locked"]; // true, false, false, false, false, false, ...
	    bool locker_boxe_is_occupied = locker_boxe["is_occupied"]; // true, false, false, false, false, false, ...
	    bool locker_boxe_temp_below_threshold = locker_boxe["temp_below_threshold"]; // false, false, false, ...

	    const char* locker_boxe_order_locker_box_content_id = locker_boxe["order"]["locker_box_content_id"];
	    const char* locker_boxe_order_customer_name = locker_boxe["order"]["customer"]["name"]; // "23432432", ...
	    const char* locker_boxe_order_customer_phone = locker_boxe["order"]["customer"]["phone"]; // "3", ...

			if(!Send_trigger){
				if(locker_boxe_is_occupied) web_sequence += "1:";
		    else web_sequence += "0:"; 		
			}
	    else{
	    	if(!locker_boxe_is_locked){
	    		if(!locker_boxe_is_occupied) {Unlock_doors_keep_food[index] = true; Unlock_doors_Collect_food[index] = false;}
	    		else {Unlock_doors_keep_food[index] = false; Unlock_doors_Collect_food[index] = true;}

	    		if(!response_sent[index]){
	    			send_response++;
	    			response_sent[index] = true;
	    		}
	    	}
	    	else{
	    		Unlock_doors_keep_food[index] = false;
	    		Unlock_doors_Collect_food[index] = false;
	    		// response_sent[index] = false;
	    	}
	    }
	    index++;
	  }
	  if((!Send_trigger) && web_sequence != "")web_sequence += "&";
	  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	delete client;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerializeJsonDoc( int i){
	StaticJsonDocument<200> sensor;    //192
	String sensor_json;

	sensor["locker_id"] = "645e48406dd4d02438dea2c6"; 
	sensor["ip_address"] = box_ip;
	sensor["locker_box_id"] = locker_box_ids[i];
	JsonObject properties = sensor.createNestedObject("properties");
	properties["is_locked"] = response_is_locked[i];
	properties["is_occupied"] = response_is_Occupied[i];
	properties["temp_below_threshold"] = response_temp_threshold[i];
	//i = box_count; // force terminating loop here <<<<<<<<<<-------------------------
	update_boxes[i] = false;

	serializeJson(sensor, sensor_json);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// configure traged server and url
	WiFiClientSecure *client = new WiFiClientSecure;
	if(client) {
		client -> setCACert(rootCACertificate);
		HTTPClient https;

		{
		  String line; 
		  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		
		https.begin(*client, put_link); //HTTPS
		https.addHeader("x-api-key", "oplpsOtoCt2b1tyztPsKO233c5w6qi3Mx0B8rsCb");
		https.addHeader("Content-Type", "application/json");
		https.addHeader("Accept","application/json");
		// start connection and send HTTP header and body
		int httpCode = https.PUT(String(sensor_json));

		// httpCode will be negative on error
		if (httpCode > 0) {
			// HTTP header has been send and Server response header has been handled

			// file found at server
			if (httpCode == HTTP_CODE_OK) {
				const String& payload = https.getString();
				response_sent[i] = false;
				send_response--;
				if(send_response<0) send_response=0;
				// index = 999;
			}
		} 
		https.end();
	  delete client;
	}
	//////////////////////////////////////////////////////////////////////////////////////////
}
////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void update_response(){
	int index=0;
	for(int i=0; i<box_count; i++){
  	if(update_boxes[i]){
  		SerializeJsonDoc(i);
	  }
	}

	// for(int i=0, index=0; i<box_count; i++){
	// 	if(response_sent[i]) index--;
	// 	else index++;		
	// }
	// if(index == box_count) send_response = false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fuctions used for WiFi credentials saving and connecting to it which you do not need to change
bool testWifi(void){
  int c = 0;
  //Serial.println("Waiting for Wifi to connect");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
    	Wifi_Connected = true;
      return true;
    }
    delay(500);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out!!!!!");
  return false;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
void launchWeb(){                  //Launch Server for Wifi-Credentials Page
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
void createWebServer(){             //webserver for wifi-Credentials
  
  server.on("/", []() {

    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
    content =  "<!DOCTYPE HTML>\r\n<html>";
   
    content += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    content += "<title>Vendngo Kiosk</title>";
    // content += "<link rel=\"icon\" href=\"data:,\">";
    // content += "<style> body {font-family: Arial, sans-serif; margin: 0; padding: 0; text-align: center; background: #882C88; background-image: url(\"background.jpg\"); background-size: cover; background-repeat: no-repeat; background-position: center; }";
    content += "<style> body {font-family: Arial, sans-serif; margin: 0; padding: 0; text-align: center; background: #882C88;}";
    content += "</style></head>";
    //content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
    
    content += "<body><div>";
    content += "<p style=\"color: white\"; \"font-family: Arial, sans-serif\"; \"font-size: 1.5em\"; >Kiosk Wifi Configuration</h1></div>";
    content += "<hr><p style=\"color: white\";>Device IP: </p><p style=\"color: white\";>";
    content += ipStr;
    content += "</p><hr><p style=\"color: white\";><br>Scanned Networks<br><br></p><hr><p style=\"color: white\";>";
    content += st;
    content += "</p><hr><form method='get' action='setting'>";
    content += "<div><label>SSID: </label><input name='ssid' length=32></div>";
    content += "<div><label>PASS: </label><input name='pass' length=64></div>";
    content += "<hr><br><br><div><input type='submit'></div></form>";
    content += "</body></html>";

    server.send(200, "text/html", content);
  });

  /*
  server.on("/scan", []() {
    //setupAP();
    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

    content = "<!DOCTYPE HTML>\r\n<html>go back";
    server.send(200, "text/html", content);
  });*/

  server.on("/setting", []() {
    String qsid = server.arg("ssid");
    String qpass = server.arg("pass");
    if (qsid.length() > 0 && qpass.length() > 0) {
      Serial.println("clearing eeprom");
      for (int i = 0; i < 96; ++i) {
        EEPROM.write(i, 0);
      }
      Serial.println(qsid);
      Serial.println("");
      Serial.println(qpass);
      Serial.println("");

      Serial.println("writing eeprom ssid:");
      for (int i = 0; i < qsid.length(); ++i)
      {
        EEPROM.write(i, qsid[i]);
        Serial.print("Wrote: ");
        Serial.println(qsid[i]);
      }
      Serial.println("writing eeprom pass:");
      for (int i = 0; i < qpass.length(); ++i)
      {
        EEPROM.write(32 + i, qpass[i]);
        Serial.print("Wrote: ");
        Serial.println(qpass[i]);
      }
      EEPROM.commit();

      content =  "<!DOCTYPE HTML>\r\n<html>";

      content += "<head><meta name=\"viewport1\" content=\"width=device-width, initial-scale=1\">";
	    content += "<style> body {font-family: Arial, sans-serif; margin: 0; padding: 0; text-align: center; background: #882C88; }";
	    content += "</style></head>";
			
	    content += "<h1 style=\"color: white\"; \"font-family: Arial, sans-serif\"; \"font-size: 2.5em\"; >Wi-Fi Credentials saved..<br>Successfully</h1>";
	    content += "</p><hr><p style=\"color: white\";><br><br>Wifi will auto-disconnect in 5 seconds<br>Kindly Close this browser tab and<br>Turn off Kiosk for 1 Minute<br>before restarting Kiosk</p><hr>";
	    content += "</body></html>";

      statusCode = 200;
      server.sendHeader("Access-Control-Allow-Origin", "*");
    	server.send(statusCode, "text/html", content);
      delay(5000);
      ESP.restart();
    } else {
      content = "{\"Error\":\"404 not found\"}";
      statusCode = 404;
      Serial.println("Sending 404");
      server.sendHeader("Access-Control-Allow-Origin", "*");
    	server.send(statusCode, "application/json", content);
    }

  });
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
void setupAP(void){                   //Create Hotspot for Wifi-Credentials Page
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      //Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<ol>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);

    st += ")";
    //st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "</li>";
  }
  st += "</ol>";
  delay(100);
  WiFi.softAP("Kiosk-645*2c6", "");
  Serial.println("Initializing_softap_for_wifi credentials_modification");
  launchWeb();
  Serial.println("over");
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
void setupAP2(void){                   //Create Hotspot for Manual Locker Management Page

  IPAddress IP = WiFi.softAPIP();
	// Serial.print("AP IP address: ");
	// Serial.println(IP);
	WiFi.softAP("Kiosk_ea2c6", "");
	delay(1000);
	// Serial.println("Scan for available Network......");
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
void RunWebServer2(){             //webserver for Manual Control
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("1 open");
              digitalWrite(output2, HIGH);
              delay(250);
              digitalWrite(output2, LOW);
              State_1 = "on";
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("1 off");
              State_1 = "off";  
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("2 Open");
              digitalWrite(output2, HIGH);
              delay(200);
              digitalWrite(output2, LOW);
              delay(200);
              digitalWrite(output2, HIGH);
              delay(200);
              digitalWrite(output2, LOW);
              State_2 = "on";
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("2 off");
              State_2 = "off";  
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("3 Open");
              digitalWrite(output2, HIGH);
              delay(1000);
              digitalWrite(output2, LOW);
              State_3 = "on";
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("3 off");
              State_3 = "off";  
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("4 Open");
              digitalWrite(output2, HIGH);
              delay(500);
              digitalWrite(output2, LOW);
              delay(500);
              digitalWrite(output2, HIGH);
              delay(500);
              digitalWrite(output2, LOW);
              State_4 = "on";
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("4 off");
              State_4 = "off";  
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("5 Open");
              digitalWrite(output2, HIGH);
              State_5 = "on";
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("5 off");
              State_5 = "off";  
            } else if (header.indexOf("GET /6/on") >= 0) {
              Serial.println("6 Open");
              digitalWrite(output2, LOW);
              State_6 = "on";
            } else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("6 off");
              State_6 = "off";  
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<title>Vendngo Kiosk</title>");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style> body {font-family: Arial, sans-serif; margin: 0; padding: 0; text-align: center; background: #882C88; background-image: url(\"background.jpg\"); background-size: cover; background-repeat: no-repeat; background-position: center; }");
            client.println(".container {max-width: 800px; margin: 0 auto; padding: 20px; text-align: center; }");
            client.println(".container h1 {margin: 15px 5px 5px 5px;}");
            client.println(".logo {background: url(\"https://versicles-strapi-media.s3.ap-south-1.amazonaws.com/vendngo_internallogo_f228223dff.png\") no-repeat; height: 56px; width: 264px; margin: auto;} ");
            client.println(".footer_logo {background: url(\"https://versicles-strapi-media.s3.ap-south-1.amazonaws.com/footer_Logointernal_1422be5a5a.png\") no-repeat; width: 77.04px; height: 77.04px; }");
            client.println(".settings-icon {position: fixed; bottom: 20px; right: 20px; font-size: 30px; cursor: pointer; color: #333; }");
            client.println(".button { background-color: #eee808; border: none; border-radius: 10px; color: #882C88; padding: 1px 3px;");            
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println("table, th, td {border:none;}");
            client.println(".button2 {background-color: #4CAF50;}</style></head>");
            
            client.println("<body> <div class=\"container\"> ");
            client.println("<div class=\"logo\"></div>");
            client.println("<h1 style=\"color: white;\">Locker Box Management</h1>");
            client.println("</div>"); 
            client.println("<div class=\"footer_logo settings-icon\"></div>");
            
            
            // client.println("<p> 1 - " + State_1 + "</p>");
            if (State_1=="off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">1.  OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">1. RESET</button></a></p>");
            } 
               
             
            // client.println("<p> 2 - " + State_2 + "</p>");      
            if (State_2=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">2.  OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">2. RESET</button></a></p>");
            }

            // client.println("<p> 3 - " + State_3 + "</p>");     
            if (State_3=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">3.  OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">3. RESET</button></a></p>");
            } 
               
             
            // client.println("<p> 4 - " + State_4 + "</p>");     
            if (State_4=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">4.  OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">4. RESET</button></a></p>");
            }


            // client.println("<p> 5 - " + State_5 + "</p>");      
            if (State_5=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">5.  OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">5. RESET</button></a></p>");
            } 
               
             
            // client.println("<p> 6 - " + State_6 + "</p>");      
            if (State_6=="off") {
              client.println("<p><a href=\"/6/on\"><button class=\"button\">6.  OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/6/off\"><button class=\"button button2\">6. RESET</button></a></p>");
            }


            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
void launchWebApp(){                  //Launch Server for Locker Management Page
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  // RunWebServer2();
  // Start the server
  server.begin();
  Serial.println("Server started");
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////