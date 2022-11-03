#include <esp_now.h>
#include <WiFi.h>

//Structure example to receive data
//Must match the sender structure
typedef struct test_struct {
  int lock1;
  int green1;
  int lock2;
  int green2;
  int lock3;
  int green3;
} test_struct;

//Create a struct_message called myData
test_struct myData;

//callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("LOCK1: ");
  Serial.println(myData.lock1);
  Serial.print("green1: ");
  Serial.println(myData.green1);
  Serial.print("LOCK2: ");
  Serial.println(myData.lock2);
  Serial.print("green2: ");
  Serial.println(myData.green2);
  Serial.print("LOCK3: ");
  Serial.println(myData.lock3);
  Serial.print("green3: ");
  Serial.println(myData.green3);
  Serial.println();
}
 
void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}
