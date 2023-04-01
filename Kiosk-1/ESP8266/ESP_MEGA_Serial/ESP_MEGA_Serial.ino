#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "certs.h"
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define LED 2
#define fetch_duration 3000                                           //Json fetch every 3rd-seconds

#ifndef STASSID
#define STASSID "BSNL-FTTH-1908"
#define STAPSK  "vtk2361908"
#endif

/*#ifndef STASSID
#define STASSID "Rapid-Abhi"
#define STAPSK  "Rapidcode12"
#endif*/

#define get_link "/locker/6418065f4fbb671f149c0823.json"              //Update this link for different lockers
#define post_link "/locker-box"                                       //Update this link for different lockers
#define parse_check "{\"id\": \"6418065f4fbb671f149c0823\""           //update this json response for every locker
#define put_link "https://locker-iot-api.versicles.com/locker-box"

const char* ssid = STASSID;
const char* password = STAPSK;

X509List cert(cert_Amazon_RSA_2048_M01);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String box_status = "";
WiFiClientSecure client; 
bool send_box_status = true;
bool locker_state[] ={false, false, false, false, false, false, false, false, false, false};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  	digitalWrite(LED, HIGH);
    delay(250);
    digitalWrite(LED, LOW);
    delay(250);
    // Serial.print(".");
  }
  digitalWrite(LED, LOW);
  // Serial.println("");
  // Serial.println("WiFi connected");
  // Serial.println("IP address: ");
  // Serial.println(WiFi.localIP());
  
  // fetch_json();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
	if(Serial.available()){
		char command = Serial.read();
		if((command == 'S') && send_box_status){
			fetch_json();
			Serial.println(box_status);
		}
		else if(command == 's'){
			send_box_status = false;
		}
	}

	delay(fetch_duration);
	fetch_json();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fetch_json(){
 ///////////////////////////posting data here//////////////////////////////////////////////
  /*
  // Use WiFiClientSecure class to create TLS connection
  Serial.print("Connecting to ");
  Serial.println(post_host);

  Serial.printf("Using certificate: %s\n", cert_Amazon_RSA_2048_M01);
  client.setTrustAnchors(&cert);

  if (!client.connect(post_host, port)) {
    Serial.println("Connection failed");
    return;
  }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //JSON CREATION
  Serial.println("Starting JSON Creation");
  // char json[] = "{\"locker_id\": \"6418065f4fbb671f149c082c\", \"ip_address\": \"222.444.111.333\", \"locker_box_id\": \"9\", \"properties\":{\"is_locked\": true, \"is_occupied\": false, \"temp_below_threshold\": true}}";
  
  StaticJsonDocument<192> sensor;
  String sensor_json;

  sensor["locker_id"] = "6418065f4fbb671f149c0826";
  sensor["ip_address"] = "222.444.111.333";
  sensor["locker_box_id"] = "3";

  JsonObject properties = sensor.createNestedObject("properties");
  properties["is_locked"] = true;
  properties["is_occupied"] = true;
  properties["temp_below_threshold"] = true;

  serializeJson(sensor, sensor_json);
  Serial.print("sensor_json= ");
  Serial.println(sensor_json);
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    // configure traged server and url
    https.begin(client, put_link); //HTTPS
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
      }
    } else {
      Serial.printf("[HTTPS] PUT... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
    client.stop();
  }
  */
 //////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////fetching data here///////////////////////////////////////////////
  // Use WiFiClientSecure class to create TLS connection
  // Serial.print("Connecting to ");
  // Serial.println(get_host);

  // Serial.printf("Using certificate: %s\n", cert_Amazon_RSA_2048_M01);
 client.setTrustAnchors(&cert);

  if (!client.connect(get_host, port)) {
    // Serial.println("Connection failed");
    return;
  }

  String url = get_link;
  // Serial.print("Requesting URL: ");
  // Serial.println(get_host+url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + get_host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  // Serial.println("Request sent");
  
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      // Serial.println("Headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith(parse_check)) {
    // Serial.println("Device ID matched successfully!");
  } else {
    // Serial.println("Issue with data retrieval!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    while(1){
    	pinMode(LED, HIGH);
    	delay(2000);
    	pinMode(LED, LOW);
    	delay(2000);
    }
  }
  const size_t capacity = 3072; //JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
  DynamicJsonDocument doc(capacity);

  // Parse JSON object
  DeserializationError error = deserializeJson(doc, line);
  if (error) {
    // Serial.print(F("deserializeJson() failed: "));
    // Serial.println(error.f_str());
    client.stop();
    while(1){
    	pinMode(LED, HIGH);
    	delay(2000);
    	pinMode(LED, LOW);
    	delay(2000);
    }
  }
  const char* id = doc["id"]; // "6418065f4fbb671f149c0823"
  const char* name = doc["name"]; // "lulu locker 1"

  // Serial.println("#################################################################");
  // Serial.print("locker_id =");
  // Serial.println(id);
  // Serial.print("locker_name =");
  // Serial.println(name);
  // Serial.println("#################################################################");

  int counter = 0;

  for (JsonObject locker_boxe : doc["locker_boxes"].as<JsonArray>()) {

    const char* locker_boxe_id = locker_boxe["id"]; // "6418065f4fbb671f149c0824", ...
    int locker_boxe_number = locker_boxe["number"]; // 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    bool locker_boxe_is_locked = locker_boxe["is_locked"]; // true, false, false, false, false, false, ...
    bool locker_boxe_is_occupied = locker_boxe["is_occupied"]; // true, false, false, false, false, false, ...
    bool locker_boxe_temp_below_threshold = locker_boxe["temp_below_threshold"]; // false, false, false, ...

    const char* locker_boxe_order_locker_box_content_id = locker_boxe["order"]["locker_box_content_id"];
    const char* locker_boxe_order_customer_name = locker_boxe["order"]["customer"]["name"]; // "23432432", ...
    const char* locker_boxe_order_customer_phone = locker_boxe["order"]["customer"]["phone"]; // "3", ...

    if(!send_box_status){
    	if(locker_boxe_is_occupied){
    		if(!locker_state[counter]){
    			if(counter == 0) Serial.println("A");
    			else if(counter == 1) Serial.println("B");
    			else if(counter == 2) Serial.println("C");
    			else if(counter == 3) Serial.println("D");
    			else if(counter == 4) Serial.println("E");
    			else if(counter == 5) Serial.println("F");
    			else if(counter == 6) Serial.println("G");
    			else if(counter == 7) Serial.println("H");
    			else if(counter == 8) Serial.println("I");
    			else if(counter == 9) Serial.println("J");

    			locker_state[counter] = true;
    		}
    	}else{
    		if(locker_state[counter]){
    			if(counter == 0) Serial.println("a");
    			else if(counter == 1) Serial.println("b");
    			else if(counter == 2) Serial.println("c");
    			else if(counter == 3) Serial.println("d");
    			else if(counter == 4) Serial.println("e");
    			else if(counter == 5) Serial.println("f");
    			else if(counter == 6) Serial.println("g");
    			else if(counter == 7) Serial.println("h");
    			else if(counter == 8) Serial.println("i");
    			else if(counter == 9) Serial.println("j");

    			locker_state[counter] = false;
    		}
    	}
    }else{
    	if(locker_boxe_is_occupied){
	    	box_status += "1:";
	    	locker_state[counter] = true;
	    }
	    else{
	    	box_status += "0:";
	    	locker_state[counter] = false;
	    }
    }
    // Serial.print("box_id =");
    // Serial.println(locker_boxe_id);
    // Serial.print("box_no =");
    // Serial.println(locker_boxe_number);
    // Serial.print("box_is_locked =");
    // Serial.println(locker_boxe_is_locked);
    // Serial.print("box_is_occupied =");
    // Serial.println(locker_boxe_is_occupied);
    // Serial.print("box_temp_below_threshold =");
    // Serial.println(locker_boxe_temp_below_threshold);
    // Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    // Serial.print("box order id:");
    // Serial.println(locker_boxe_order_locker_box_content_id);
    // Serial.print("box order customer name:");
    // Serial.println(locker_boxe_order_customer_name);
    // Serial.print("box order customer phone:");
    // Serial.println(locker_boxe_order_customer_phone);
    // Serial.println("---------------------------------------------------------------");
    counter++;
  }

 
	if(send_box_status){
		box_status += "&";
	}

  // Disconnect
  client.stop();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////