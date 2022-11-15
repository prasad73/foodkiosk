#include <esp_now.h>
#include <WiFi.h>

#define R1 21
#define G1 19
#define B1 18

#define R2 27
#define G2 26
#define B2 25

#define R3 13
#define G3 33
#define B3 32

#define Lock1 22

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

bool lock1flag = false;
bool Lock1on = false;
bool light1on = false;
bool light2on = false;
bool light3on = false;

int R1_STATE = 0;
int G1_STATE = 0;
int B1_STATE = 0;

int R2_STATE = 0;
int G2_STATE = 0;
int B2_STATE = 0;

int R3_STATE = 0;
int G3_STATE = 0;
int B3_STATE = 0;

//Create a struct_message called myData
test_struct myData;

//callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  // Serial.print("Bytes received: ");
  // Serial.println(len);
  // Serial.print("LOCK1: ");
  // Serial.println(myData.lock1);
  // Serial.print("green1: ");
  // Serial.println(myData.green1);
  // Serial.print("LOCK2: ");
  // Serial.println(myData.lock2);
  // Serial.print("green2: ");
  // Serial.println(myData.green2);
  // Serial.print("LOCK3: ");
  // Serial.println(myData.lock3);
  // Serial.print("green3: ");
  // Serial.println(myData.green3);
  // Serial.println();

  if(myData.lock1 == 1) Lock1on = true; else Lock1on = false;
  if(myData.green1 == 0) light1on = true; else light1on = false;
  if(myData.green2 == 0) light2on = true; else light2on = false;
  if(myData.green3 == 0) light3on = true; else light3on = false;
}
 
void setup() {
  pinMode(R1, OUTPUT);
  pinMode(G1, OUTPUT);
  pinMode(B1, OUTPUT);

  pinMode(R2, OUTPUT);
  pinMode(G2, OUTPUT);
  pinMode(B2, OUTPUT);
  
  pinMode(R3, OUTPUT);
  pinMode(G3, OUTPUT);
  pinMode(B3, OUTPUT);

  pinMode(Lock1, OUTPUT);
  digitalWrite(Lock1, LOW);

  // pinMode(FeedBack, INPUT);

  digitalWrite(R1, LOW);
  digitalWrite(G1, HIGH);
  digitalWrite(B1, HIGH);

  digitalWrite(R2, LOW);
  digitalWrite(G2, HIGH);
  digitalWrite(B2, HIGH);

  digitalWrite(R3, LOW);
  digitalWrite(G3, HIGH);
  digitalWrite(B3, HIGH);

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

  Serial.begin(115200);
}
 
void loop() {

  if(Serial.available){
    char data = Serial.read();
    if(data=='2') digitalWrite(Lock1, LOW);
    else if(data=='3') digitalWrite(Lock1, HIGH);
  }

  if(Lock1on) {
    if(!lock1flag){
      digitalWrite(Lock1 , HIGH);
      delay(1500);
      digitalWrite(Lock1 , LOW);
      lock1flag =!lock1flag;
    }
    digitalWrite(G1, LOW);
    digitalWrite(B1, LOW);
  }else{
    if(light1on){
      digitalWrite(G1, HIGH);
      digitalWrite(B1, HIGH);  
    }else{
      digitalWrite(G1, LOW);
      digitalWrite(B1, LOW);  
    }   
  }

  if(light2on){
      digitalWrite(G2, HIGH);
      digitalWrite(B2, HIGH);  
  }else{
      digitalWrite(G2, LOW);
      digitalWrite(B2, LOW);      
  }    

  if(light3on){
      digitalWrite(G3, HIGH);
      digitalWrite(B3, HIGH);  
  }else{
      digitalWrite(G3, LOW);
      digitalWrite(B3, LOW);    
  }

}
