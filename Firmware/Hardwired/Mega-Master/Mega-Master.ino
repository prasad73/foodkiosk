#include <Adafruit_NeoPixel.h>
#define LED_PIN  21
#define LED_COUNT 3

#define Lock1 6
#define Lock2 7
#define Lock3 8
#define Lock4 9
#define Lock5 10
#define Lock6 11
#define Lock7 14
#define Lock8 15
#define Lock9 16
#define Lock10 17
#define Lock11 12
#define Lock12 13

#define INPUT_SIZE 20

// char Serial_buffer[20];
int box_Status[10];

int data_tracker = 0 ;
bool data_recieved = false;
bool first_serial_data = false;
boolean Customer_unlock[] = {false, false, false, false, false, false, false,false, false, false};

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int Locks[] = {Lock1,Lock2,Lock3,Lock4,Lock5,Lock6,Lock7,Lock8,Lock9,Lock10, Lock11, Lock12};
int No_of_locks = 12;
 
void setup() {
  for(int i=0; i<No_of_locks;i++){
    pinMode(Locks[i],OUTPUT);
    digitalWrite(Locks[i], LOW);
  }
 
  Serial.begin(115200);
  // Serial.setTimeout(3000);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)

}
 
void loop() {

  if(Serial.available()){     //Example String_data="1:1:0:0:1:0:1:1:0:0:&";
    char input[INPUT_SIZE];
    // byte size = Serial.readBytes(input, INPUT_SIZE);
    size_t size = Serial.readBytesUntil('&', input, INPUT_SIZE);

    if(size == 20){
        // Read each command pair 
        char* command = strtok(input, ":");
        int index=0;
        if((command[0] == '0') || (command[0] == '1')){
          while (command != NULL)
          { 
              if(index<10) {
                box_Status[index++] = atoi(command);
              }          
              // Find the next command in input string
              command = strtok(NULL, ":");
          }
          for(int i=0; i<10;i++) if((box_Status[i]>=0) &&(box_Status[i]<=1)) data_tracker++;
          if(data_tracker == 10) {data_recieved = true; data_tracker=0;}  
        }
    }

  }

  if(data_recieved){
    if(!first_serial_data){
      first_serial_data = true; 
    }
    else{
      // sprintf(Serial_buffer, "%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:", box_Status[0],box_Status[1],box_Status[2],box_Status[3],box_Status[4],box_Status[5],box_Status[6],box_Status[7],box_Status[8],box_Status[9]);
      // Serial.println(Serial_buffer);
        for(int i=0; i<10; i++){
          if(!Customer_unlock[i]){
           if(box_Status[i]==1){
              digitalWrite(Locks[i] , HIGH);
              delay(500);
              digitalWrite(Locks[i] , LOW);
              Customer_unlock[i] = true;
            }
            else{
              digitalWrite(Locks[i] , LOW);
            }
          }   
          else{
           if(box_Status[i]==0){
              digitalWrite(Locks[i] , HIGH);
              delay(500);
              digitalWrite(Locks[i] , LOW);
              Customer_unlock[i] = false;
            }
            else{
              digitalWrite(Locks[i] , LOW);
            }  
          }
        }
    }
    data_recieved=false;
    for(int i=0; i<10;i++) box_Status[i]=0;
  }

  delay(500);
}
