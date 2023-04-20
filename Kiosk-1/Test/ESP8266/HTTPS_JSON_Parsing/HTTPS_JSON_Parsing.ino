#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "certs.h"
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "BSNL-FTTH-1908"
#define STAPSK  "vtk2361908"
#endif

#define link "/locker/6418065f4fbb671f149c0823.json"          //Update this link for different lockers
#define parse_check "{\"id\": \"6418065f4fbb671f149c0823\""   //update this json response for every locker

const char* ssid = STASSID;
const char* password = STAPSK;

X509List cert(cert_Amazon_RSA_2048_M01);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set time via NTP, as required for x.509 validation
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("Connecting to ");
  Serial.println(host);

  Serial.printf("Using certificate: %s\n", cert_Amazon_RSA_2048_M01);
  client.setTrustAnchors(&cert);

  if (!client.connect(host, port)) {
    Serial.println("Connection failed");
    return;
  }

  String url = link;
  Serial.print("Requesting URL: ");
  Serial.println(host+url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("Request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith(parse_check)) {
    Serial.println("esp8266/Arduino CI successful!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
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
    client.stop();
    return;
  }

  // Extract values
  Serial.println(F("Response:"));
  Serial.println(doc["sensor"].as<const char*>());
  Serial.println(doc["time"].as<long>());
  Serial.println(doc["data"][0].as<float>(), 6);
  Serial.println(doc["data"][1].as<float>(), 6);

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
  }

  // Disconnect
  client.stop();
}

void loop() {
}
