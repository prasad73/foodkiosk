#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#define LED 2
#define RXD2 16
#define TXD2 17
#define box_count 10

#define box_ip "111.222.333.444"
#define polling_time 2000

/*#ifndef STASSID
#define STASSID "BSNL-FTTH-1908"
#define STAPSK  "vtk2361908"
#endif*/

// #ifndef STASSID
// #define STASSID "Rapid-Abhi"
// #define STAPSK  "Rapidcode12"
// #endif

#ifndef STASSID
#define STASSID "Nokia C01 Plus"
#define STAPSK  "versicles123"
#endif


#define get_link "https://locker-api.versicles.com/locker/6418065f4fbb671f149c0823.json"  //Update this link for different lockers
#define parse_check "{\"id\": \"6418065f4fbb671f149c0823\""                               //update this json response for every locker
#define put_link "https://locker-iot-api.versicles.com/locker-box"                        //Update this link for different lockers
//////////////////////////////////////////////////////////////////////////////
const char* put_host = "https://locker-iot-api.versicles.com";
const uint16_t port = 443;

const char* ssid = STASSID;
const char* password = STAPSK;
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

bool Send_trigger = false;
bool state = HIGH;
bool send_response = false;

String web_sequence = "";   //"0:0:0:0:0:0:0:0:0:0:&"
bool Unlock_doors_keep_food[] = {false,false,false,false,false,false,false,false,false,false};
bool Unlock_doors_Collect_food[] = {false,false,false,false,false,false,false,false,false,false};

bool response_is_locked[] =  {true, true, true, true, true, true, true, true, true, true};
bool response_is_Occupied[] = {false,false,false,false,false,false,false,false,false,false};
bool response_temp_threshold[] = {false,false,false,false,false,false,false,false,false,false};
bool update_boxes[] = {false,false,false,false,false,false,false,false,false,false};
bool response_sent[] = {false,false,false,false,false,false,false,false,false,false};

String locker_box_ids[] ={"6418065f4fbb671f149c0824","6418065f4fbb671f149c0825","6418065f4fbb671f149c0826","6418065f4fbb671f149c0827","6418065f4fbb671f149c0828","6418065f4fbb671f149c0829","6418065f4fbb671f149c082a","6418065f4fbb671f149c082b","6418065f4fbb671f149c082c","6418065f4fbb671f149c082d"};

// HardwareSerial Serial2(2) // use UART2

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
WiFiMulti WiFiMulti;
//////////////////////////////////////////////////////////////////////////////

void setup(){
	Serial.begin(9600);
	Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);

	Serial.println();
	Serial.println();
	Serial.println();
	
	WiFi.mode(WIFI_STA);
	WiFiMulti.addAP(ssid, password);

	// wait for WiFi connection
	Serial.print("Waiting for WiFi to connect...");
	while ((WiFiMulti.run() != WL_CONNECTED)) {
	Serial.print(".");
	}
	Serial.println(" connected");

	setClock();  
	Serial.println("Initialization Done!!");

	Get_web_Status();
}

void loop(){
	if(Serial2.available()){
		char command = Serial2.read();
		if((command == 'S') && !Send_trigger){
			Serial.println("Command S detected");
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
			Serial.println("Command small 's' detected");
			Send_trigger = true;
			web_sequence = "";
		}
	}

	if(Send_trigger){
		Get_web_Status();
		delay(polling_time);
		if(send_response){
			////Unlocking doors here////////////////////////////////////////////////	
			for(int i=0; i<box_count; i++){
				if(Unlock_doors_keep_food[i]){
					if(i == 0) Serial2.println("A");
					else if(i == 1) Serial2.println("B");
					else if(i == 2) Serial2.println("C");
					else if(i == 3) Serial2.println("D");
					else if(i == 4) Serial2.println("E");
					else if(i == 5) Serial2.println("F");
					else if(i == 6) Serial2.println("G");
					else if(i == 7) Serial2.println("H");
					else if(i == 8) Serial2.println("I");
					else if(i == 9) Serial2.println("J");
				}
				else if(Unlock_doors_Collect_food[i]){
					if(i == 0) Serial2.println("a");
					else if(i == 1) Serial2.println("b");
					else if(i == 2) Serial2.println("c");
					else if(i == 3) Serial2.println("d");
					else if(i == 4) Serial2.println("e");
					else if(i == 5) Serial2.println("f");
					else if(i == 6) Serial2.println("g");
					else if(i == 7) Serial2.println("h");
					else if(i == 8) Serial2.println("i");
					else if(i == 9) Serial2.println("j");
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

			update_response();
			///////////////////////////////////////////////////////////////////////
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
	  // Use WiFiClientSecure class to create TLS connection=
	  Serial.print("Connecting to ");
	  Serial.println(get_link);

	  Serial.print("[HTTPS] begin...\n");
	  if (https.begin(*client, get_link)) {  // HTTPS
	    Serial.print("[HTTPS] GET...\n");
	    // start connection and send HTTP header
	    int httpCode = https.GET();

	    // httpCode will be negative on error
	    if (httpCode > 0) {
	      // HTTP header has been send and Server response header has been handled
	      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

	      // file found at server
	      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
	        line = https.getString();
	        Serial.println(line);
	      }
	    } else {
	      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
	    }

	    https.end();
	  } else {
	    Serial.printf("[HTTPS] Unable to connect\n");
	  }

	  if (line.startsWith(parse_check)) {
	    Serial.println("Device ID matched successfully!");
	  } else {
	    Serial.println("Issue with data retrieval!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	  }
	  Serial.println("Reply was:");
	  Serial.println("==========");
	  Serial.println(line);
	  Serial.println("==========");
	  Serial.println("Closing connection");

	  Serial.println("Parsing Json from here ----------------------------->");

	  // Allocate the JSON document
	  // Use https://arduinojson.org/v6/assistant to compute the capacity.
	  const size_t capacity = 3072; //JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
	  DynamicJsonDocument doc(capacity);

	  // Parse JSON object
	  DeserializationError error = deserializeJson(doc, line);
	  if (error) {
	    Serial.print(F("deserializeJson() failed: "));
	    Serial.println(error.f_str());
	    return;
	  }
	  const char* id = doc["id"]; // "6418065f4fbb671f149c0823"
	  const char* name = doc["name"]; // "lulu locker 1"

	  Serial.println("#################################################################");
	  Serial.print("locker_id =");
	  Serial.println(id);
	  Serial.print("locker_name =");
	  Serial.println(name);
	  Serial.println("#################################################################");


	  for (JsonObject locker_boxe : doc["locker_boxes"].as<JsonArray>()) {

	    const char* locker_boxe_id = locker_boxe["id"]; // "6418065f4fbb671f149c0824", ...
	    int locker_boxe_number = locker_boxe["number"]; // 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	    bool locker_boxe_is_locked = locker_boxe["is_locked"]; // true, false, false, false, false, false, ...
	    bool locker_boxe_is_occupied = locker_boxe["is_occupied"]; // true, false, false, false, false, false, ...
	    bool locker_boxe_temp_below_threshold = locker_boxe["temp_below_threshold"]; // false, false, false, ...

	    const char* locker_boxe_order_locker_box_content_id = locker_boxe["order"]["locker_box_content_id"];
	    const char* locker_boxe_order_customer_name = locker_boxe["order"]["customer"]["name"]; // "23432432", ...
	    const char* locker_boxe_order_customer_phone = locker_boxe["order"]["customer"]["phone"]; // "3", ...
	    /*
	    Serial.print("box_id =");
	    Serial.println(locker_boxe_id);
	    Serial.print("box_no =");
	    Serial.println(locker_boxe_number);
	    Serial.print("box_is_locked =");
	    Serial.println(locker_boxe_is_locked);
	    Serial.print("box_is_occupied =");
	    Serial.println(locker_boxe_is_occupied);
	    Serial.print("box_temp_below_threshold =");
	    Serial.println(locker_boxe_temp_below_threshold);
	    Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	    Serial.print("box order id:");
	    Serial.println(locker_boxe_order_locker_box_content_id);
	    Serial.print("box order customer name:");
	    Serial.println(locker_boxe_order_customer_name);
	    Serial.print("box order customer phone:");
	    Serial.println(locker_boxe_order_customer_phone);
	    Serial.println("---------------------------------------------------------------");
		*/
		if(!Send_trigger){
			if(locker_boxe_is_occupied) web_sequence += "1:";
	    	else web_sequence += "0:"; 		
		}
	    else{
	    	if(!locker_boxe_is_locked){
	    		if(!locker_boxe_is_occupied) {Unlock_doors_keep_food[index] = true; Unlock_doors_Collect_food[index] = false;}
	    		else {Unlock_doors_keep_food[index] = false; Unlock_doors_Collect_food[index] = true;}

	    		if(!response_sent[index]){
	    			send_response = true;
	    			response_sent[index] = true;
	    		}
	    	}
	    	else{
	    		Unlock_doors_keep_food[index] = false;
	    		Unlock_doors_Collect_food[index] = false;
	    	}
	    }
	    index++;
	  }
	  if((!Send_trigger) && web_sequence != "")web_sequence += "&";
	  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	delete client;
	} else {
	Serial.println("Unable to create client");
	}

	Serial.println();
	Serial.println("Fetch data cycle finished...");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void update_response(){
	int index = 0;
	WiFiClientSecure *client = new WiFiClientSecure;
	if(client) {
	client -> setCACert(rootCACertificate);
	HTTPClient https;

	{
	  String line; 
	  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	{
	  ///////////////////////////posting data here//////////////////////////////////////////////

	  // Use WiFiClientSecure class to create TLS connection
	  Serial.print("Connecting to ");
	  Serial.println(put_link);

	  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  //JSON CREATION
	  Serial.println("Starting JSON Creation");
	  // char json[] = "{\"locker_id\": \"6418065f4fbb671f149c0823\", \"ip_address\": \"222.444.111.333\", \"locker_box_id\": \"6418065f4fbb671f149c0828\", \"properties\":{\"is_locked\": true, \"is_occupied\": false, \"temp_below_threshold\": true}}";
	  
	  StaticJsonDocument<192> sensor;
	  String sensor_json;

	  sensor["locker_id"] = "6418065f4fbb671f149c0824"; 
	  sensor["ip_address"] = box_ip;

	  for(int i=0; i<box_count; i++){

	  	if(update_boxes[i]){
	  		sensor["locker_box_id"] = locker_box_ids[i];
	  		JsonObject properties = sensor.createNestedObject("properties");
	  		properties["is_locked"] = response_is_locked[i];
	  		properties["is_occupied"] = response_is_Occupied[i];
	  		properties["temp_below_threshold"] = response_temp_threshold[i];
	  		//i = box_count; // force terminating loop here <<<<<<<<<<-------------------------
	  		update_boxes[i] = false;
	  		index = i;

	  		serializeJson(sensor, sensor_json);
			Serial.print("sensor_json= ");
			Serial.println(sensor_json);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			Serial.print("[HTTPS] begin...\n");
			// configure traged server and url
			https.begin(*client, put_link); //HTTPS
			https.addHeader("x-api-key", "oplpsOtoCt2b1tyztPsKO233c5w6qi3Mx0B8rsCb");
			https.addHeader("Content-Type", "application/json");
			https.addHeader("Accept","application/json");
			Serial.print("[HTTPS] PUT...\n");
			// start connection and send HTTP header and body
			int httpCode = https.PUT(String(sensor_json));

			// httpCode will be negative on error
			if (httpCode > 0) {
				// HTTP header has been send and Server response header has been handled
				Serial.printf("[HTTPS] PUT... code: %d\n", httpCode);

				// file found at server
				if (httpCode == HTTP_CODE_OK) {
					const String& payload = https.getString();
					Serial.println("received payload:\n<<");
					Serial.println(payload);
					Serial.println(">>");
					response_sent[index] = false;
					index = 999;
				}
			} else {
				Serial.printf("[HTTPS] PUT... failed, error: %s\n", https.errorToString(httpCode).c_str());
			}
			https.end();
			//////////////////////////////////////////////////////////////////////////////////////////
	  	}
	  }
	}
	delete client;
	} else {
	Serial.println("Unable to create client");
	}

	for(int i=0, index=0; i<box_count; i++){
		if(response_sent[i]) index--;
		else index++;		
	}
	if(index == box_count) send_response = false;
	Serial.println();
}