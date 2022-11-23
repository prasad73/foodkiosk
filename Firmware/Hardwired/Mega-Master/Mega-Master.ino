#include <Adafruit_NeoPixel.h>
#define LED_PIN  21
#define LED_COUNT 51

#define Lock1 12 //6
#define Lock2 7
#define Lock3 16 //8
#define Lock4 11 //9
#define Lock5 6 //10
#define Lock6 14 //11
#define Lock7 10 //12
#define Lock8 8 //13
#define Lock9 15 //14
#define Lock10 17 //15

#define INPUT_SIZE 20

// char Serial_buffer[20];
int box_Status[10];

int data_tracker = 0 ;
bool data_recieved = false;
bool first_serial_data = false;
boolean Customer_unlock[] = {false, false, false, false, false, false, false,false, false, false};

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int Locks[] = {Lock1,Lock2,Lock3,Lock4,Lock5,Lock6,Lock7,Lock8,Lock9,Lock10};
int No_of_locks = 10;

// int led_sequence[]={10,3,6,9,2,5,8,1,4,7};
// int box_led_3[] ={17,18,19,20};
// int box_led_6[] ={21,22,23,24};
// int box_led_9[] ={25,26,27,28};
// int box_led_2[] ={29,30,31,32};
// int box_led_5[] ={33,34,35,36};
// int box_led_8[] ={37,38,39,40};
// int box_led_1[] ={41,42,43,44};
// int box_led_4[] ={45,46,47,48};
// int led_sequence[8][4]={{17,18,19,20}, {21,22,23,24}, {25,26,27,28}, {29,30,31,32}, {33,34,35,36}, {37,38,39,40}, {41,42,43,44}, {45,46,47,48}};
int led_sequence[9][4]={{40,41,42,43}, {28,29,30,31}, {16,17,18,19}, {44,45,46,47}, {32,33,34,35}, {20,21,22,23}, {48,49,50,50}, {36,37,38,39}, {24,25,26,27}};

/*led_map[]={
  {41,42,43,44},
  {29,30,31,32},
  {17,18,19,20},
  {45,46,47,48},
  {33,34,35,36},
  {21,22,23,24},
  {49,50,51},
  {37,38,39,40},
  {25,26,27,28},
  {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}
}*/
 
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
  colorWipe(strip.Color(0,   0,   255), 1);
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
      for(int i=0; i<10; i++) if(box_Status[i]==1) {Customer_unlock[i] = true;update_led(1,i);}
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
              update_led(1, i);
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
              update_led(0 , i);
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

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void update_led(int state, int box_number){
  if(state == 0){
    if(box_number >=0 && box_number < 9){

      for(int i=0; i<4; i++) { // For each pixel in strip...
        strip.setPixelColor(led_sequence[box_number][i], strip.Color(0,   0,   255));         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
      }
    }
    else if(box_number == 9){
      for(int i=0; i<16; i++) { // For each pixel in strip...
        strip.setPixelColor(i, strip.Color(0,   0,   255));         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
      } 
    }
  }
  else if(state == 1){
    if(box_number >=0 && box_number < 9){
      for(int i=0; i<4; i++) { // For each pixel in strip...
        strip.setPixelColor(led_sequence[box_number][i], strip.Color(0,   255,   0));         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        delay(1);                           //  Pause for a moment
      }
    }
    else if(box_number == 9){
      for(int i=0; i<16; i++) { // For each pixel in strip...
        strip.setPixelColor(i, strip.Color(0,   255,   0));         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        delay(1);                           //  Pause for a moment
      }
    }
  }
}