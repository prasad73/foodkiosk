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
#define Switch 23

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
String st;
String content;
String esid;
String epass = "";
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
	pinMode(Switch, INPUT_PULLUP);

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

	if(!(testWifi() && (digitalRead(Switch) == 1))){
    unsigned long int start_time = millis();
    while(1){
      if(millis() - start_time > 5000) {break;}
      else{
        if(digitalRead(Switch) == 1) {Wifi_Connected = false;break;}    
      }
    }
    if(digitalRead(Switch) == 0){
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

  if(!Wifi_Connected || Internet_down){
  	last_Time = millis();
  	while(millis() - last_Time < 10000){
  		if(testWifi()) {Wifi_Connected = true;break;}
  	}
  	if(!Wifi_Connected)  {
  		if(!Internet_status_down){
  			Serial2.flush();
  			Serial2.println("X");	//Capital X   -->> Turn Off MAchine Light's
  			Serial2.flush();
  			Internet_status_down = true;
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

  if(!Wifi_Connected){
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
void launchWeb(){
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
void createWebServer(){
  
  server.on("/", []() {

    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
    content = "<!DOCTYPE HTML>\r\n<html>Welcome to Wifi Credentials Update page";
    content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
    content += ipStr;
    content += "<p>";
    content += st;
    content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
    content += "</html>";
    server.send(200, "text/html", content);
  });

  server.on("/scan", []() {
    //setupAP();
    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

    content = "<!DOCTYPE HTML>\r\n<html>go back";
    server.send(200, "text/html", content);
  });

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

      content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
      statusCode = 200;
      ESP.restart();
    } else {
      content = "{\"Error\":\"404 not found\"}";
      statusCode = 404;
      Serial.println("Sending 404");
    }
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(statusCode, "application/json", content);

  });
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
void setupAP(void){
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////