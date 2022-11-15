#include <esp_now.h>
#include <WiFi.h>
#define INPUT_SIZE 19
#define R1 21
#define G1 19
#define B1 18

String String_data="1:1&0:0&1:0&1:1&0:0"; //"1:1:0:0:1:0:1:1:0:0";


// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress1[] = {0xC8, 0xF0, 0x9E, 0x9F, 0x50, 0x5C};
uint8_t broadcastAddress2[] = {0xC8, 0xF0, 0x9E, 0x9F, 0x40, 0xEC};
uint8_t broadcastAddress3[] = {0x24, 0x6F, 0x28, 0x17, 0xCC, 0x1C};  

int box_Status[10];
// char Serial_buffer[19] = {'0'};

typedef struct test_struct {
  int lock1;
  int green1;
  int lock2;
  int green2;
  int lock3;
  int green3;

} test_struct;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {

  pinMode(R1, OUTPUT);
  pinMode(G1, OUTPUT);
  pinMode(B1, OUTPUT);

  // digitalWrite(R1, LOW);
  digitalWrite(G1, 1);
  digitalWrite(B1, 1);
 
  Serial.begin(115200);
  Serial.setTimeout(3000);
 
  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  // register peer
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
    
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

}
 
void loop() {
  test_struct Box147;
  test_struct Box258;
  test_struct Box369;

/* Decode Value - Pair of 2 from String // Example: String_data="1:1&0:0&1:0&1:1&0:0";
  if(Serial.available()){
    char input[INPUT_SIZE + 1];
    byte size = Serial.readBytes(input, INPUT_SIZE);
    // Add the final 0 to end the C string
    input[size] = 0;

    // Read each command pair 
    char* command = strtok(input, "&");
    while (command != 0)
    {
        // Split the command in two values
        char* separator = strchr(command, ':');
        if (separator != 0)
        {
            // Actually split the string in 2: replace ':' with 0
            *separator = 0;
            int servoId = atoi(command);
            ++separator;
            int position = atoi(separator);

            Serial.println(servoId);
            Serial.println(position);
            // Do something with servoId and position
        }
        // Find the next command in input string
        command = strtok(0, "&");
    }
  }
  */
  if(Serial.available()){     //Example String_data="1:1:0:0:1:0:1:1:0:0";
    char input[INPUT_SIZE];
    byte size = Serial.readBytes(input, INPUT_SIZE);
    // Add the final 0 to end the C string
    // input[size] = 0;

    // Read each command pair 
    char* command = strtok(input, ":");
    int index=0;
    while (command != NULL)
    {
        if(index<10) {
          box_Status[index++] = atoi(command);
        }          
        // Find the next command in input string
        command = strtok(NULL, ":");
    }
    // sprintf(Serial_buffer, "%d:%d:%d:%d:%d:%d:%d:%d:%d:%d", box_Status[0],box_Status[1],box_Status[2],box_Status[3],box_Status[4],box_Status[5],box_Status[6],box_Status[7],box_Status[8],box_Status[9]);
    // Serial.println(Serial_buffer);
  }

  if(box_Status[0]==1){
    Box147.lock1 = 1;
    Box147.green1 = 1;  
  }
  else{
    Box147.lock1 = 0;
    Box147.green1 = 0;   
  }

  if(box_Status[1]==1){
    Box147.lock2 = 1;
    Box147.green2 = 1;  
  }
  else{
    Box147.lock2 = 0;
    Box147.green2 = 0;   
  }

  if(box_Status[2]==1){
    Box147.lock3 = 1;
    Box147.green3 = 1;  
  }
  else{
    Box147.lock3 = 0;
    Box147.green3 = 0;   
  }
//------------------------------------------------------

  if(box_Status[3]==1){
    Box258.lock1 = 1;
    Box258.green1 = 1;  
  }
  else{
    Box258.lock1 = 0;
    Box258.green1 = 0;   
  }

  if(box_Status[4]==1){
    Box258.lock2 = 1;
    Box258.green2 = 1;  
  }
  else{
    Box258.lock2 = 0;
    Box258.green2 = 0;   
  }

  if(box_Status[5]==1){
    Box258.lock3 = 1;
    Box258.green3 = 1;  
  }
  else{
    Box258.lock3 = 0;
    Box258.green3 = 0;   
  }
  
//------------------------------------------------------

  if(box_Status[6]==1){
    Box369.lock1 = 1;
    Box369.green1 = 1;  
  }
  else{
    Box369.lock1 = 0;
    Box369.green1 = 0;   
  }  

  if(box_Status[7]==1){
    Box369.lock2 = 1;
    Box369.green2 = 1;  
  }
  else{
    Box369.lock2 = 0;
    Box369.green2 = 0;   
  }  

  if(box_Status[8]==1){
    Box369.lock3 = 1;
    Box369.green3 = 1;  
  }
  else{
    Box369.lock3 = 0;
    Box369.green3 = 0;   
  } 
//------------------------------------------------------ 
  esp_err_t result1 = esp_now_send(
    broadcastAddress1, 
    (uint8_t *) &Box147,
    sizeof(test_struct));
  /* 
  if (result1 == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }*/
  delay(500);
  
  esp_err_t result2 = esp_now_send(
    broadcastAddress2, 
    (uint8_t *) &Box258,
    sizeof(test_struct));
  /*
  if (result2 == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }*/
  delay(500);  
  
  esp_err_t result3 = esp_now_send(
    broadcastAddress3, 
    (uint8_t *) &Box369,
    sizeof(test_struct));
   /*
  if (result3 == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }*/

  delay(500);
}
