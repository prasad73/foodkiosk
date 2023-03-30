#include <Adafruit_NeoPixel.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define Boxes 10                 // No. of boxes present in current Kiosk
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LED_PIN  21
#define LED_COUNT 51
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define Lock1 12
#define Lock2 7
#define Lock3 16
#define Lock4 11
#define Lock5 6
#define Lock6 14
#define Lock7 10
#define Lock8 8
#define Lock9 15
#define Lock10 17
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define drive_time 500          // Relay drive time
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define INPUT_SIZE 20            // Size of data stream received from ESP8266 to Mega 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int box_Status[Boxes];           // Box state from web stored here
int data_tracker = 0 ;           // tracker to check whether all data is received or not
bool data_recieved = false;      // data-received from ESP8266 or not
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Locks[] = {Lock1,Lock2,Lock3,Lock4,Lock5,Lock6,Lock7,Lock8,Lock9,Lock10};
int No_of_locks = Boxes;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int led_sequence[9][4]={{40,41,42,43}, {28,29,30,31}, {16,17,18,19}, {44,45,46,47}, {32,33,34,35}, {20,21,22,23}, {48,49,50,50}, {36,37,38,39}, {24,25,26,27}};
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool web_door_status[Boxes] = {false, false, false, false, false, false, false, false, false, false};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void setup() {
  for(int i=0; i<No_of_locks;i++){
    pinMode(Locks[i],OUTPUT);
    digitalWrite(Locks[i], LOW);
  }
 
  Serial.begin(115200);
  Serial1.begin(115200);

  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  // colorWipe(strip.Color(0,   0,   255), 1);

  update_state();
}
//////////////////////////////////////////////////////////////////////////////// 
void loop() {
  //##################################################################################################################################################################
  ///////////////////////////////////////////////////////////////////////////////////
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  /////////////////////////Process serial command here///////////////////////////////
  if(Serial1.available()){
    char command = Serial1.read();
    
    if(command == 'A'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      web_door_status[0] = true;
      digitalWrite(lock1, HIGH);
      Serial.println("Lock1 Unlocked - Keep Food");
      delay(drive_time);
      digitalWrite(lock1, LOW);
      update_led(1, 0);
    }
    else if(command == 'B'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      web_door_status[1] = true;
      digitalWrite(lock2, HIGH);
      Serial.println("Lock2 Unlocked - Keep Food");
      delay(drive_time);
      digitalWrite(lock2, LOW);
      update_led(1, 1);
    }
    else if(command == 'C'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      web_door_status[2] = true;
      digitalWrite(lock3, HIGH);
      Serial.println("Lock3 Unlocked - Keep Food");
      delay(drive_time);
      digitalWrite(lock3, LOW);
      update_led(1, 2);
    }
    else if(command == 'D'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      web_door_status[3] = true;
      digitalWrite(lock4, HIGH);
      Serial.println("Lock4 Unlocked - Keep Food");
      delay(drive_time);
      digitalWrite(lock4, LOW);
      update_led(1, 3);
    }
    else if(command == 'E'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      web_door_status[4] = true;
      digitalWrite(lock5, HIGH);
      Serial.println("Lock5 Unlocked - Keep Food");
      delay(drive_time);
      digitalWrite(lock5, LOW);
      update_led(1, 4);
    }
    else if(command == 'F'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      web_door_status[5] = true;
      digitalWrite(lock6, HIGH);
      Serial.println("Lock6 Unlocked - Keep Food");
      delay(drive_time);
      digitalWrite(lock6, LOW);
      update_led(1, 5);
    }
    else if(command == 'G'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      web_door_status[6] = true;
      digitalWrite(lock7, HIGH);
      Serial.println("Lock7 Unlocked - Keep Food");
      delay(drive_time);
      digitalWrite(lock7, LOW);
      update_led(1, 6);
    }
    else if(command == 'H'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      web_door_status[7] = true;
      digitalWrite(lock8, HIGH);
      Serial.println("Lock8 Unlocked - Keep Food");
      delay(drive_time);
      digitalWrite(lock8, LOW);
      update_led(1, 7);
    }
    else if(command == 'I'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      web_door_status[8] = true;
      digitalWrite(lock9, HIGH);
      Serial.println("Lock9 Unlocked - Keep Food");
      delay(drive_time);
      digitalWrite(lock9, LOW);
      update_led(1, 8);
    }
    else if(command == 'J'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      web_door_status[9] = true;
      digitalWrite(lock10, HIGH);
      Serial.println("Lock10 Unlocked - Keep Food");
      delay(drive_time);
      digitalWrite(lock10, LOW);
      update_led(1, 9);
    }
    else if(command == 'a'){
      web_door_status[0] = false;
      digitalWrite(lock1, HIGH);
      Serial.println("Lock1 Unlocked - Take Food");
      delay(drive_time);
      digitalWrite(lock1, LOW);
      update_led(0, 0);
    }
    else if(command == 'b'){
      web_door_status[1] = false;
      digitalWrite(lock2, HIGH);
      Serial.println("Lock2 Unlocked - Take Food");
      delay(drive_time);
      digitalWrite(lock2, LOW);
      update_led(0, 1);
    }
    else if(command == 'c'){
      web_door_status[2] = false;
      digitalWrite(lock3, HIGH);
      Serial.println("Lock3 Unlocked - Take Food");
      delay(drive_time);
      digitalWrite(lock3, LOW);
      update_led(0, 2);
    }
    else if(command == 'd'){
      web_door_status[3] = false;
      digitalWrite(lock4, HIGH);
      Serial.println("Lock4 Unlocked - Take Food");
      delay(drive_time);
      digitalWrite(lock4, LOW);
      update_led(0, 3);
    }
    else if(command == 'e'){
      web_door_status[4] = false;
      digitalWrite(lock5, HIGH);
      Serial.println("Lock5 Unlocked - Take Food");
      delay(drive_time);
      digitalWrite(lock5, LOW);
      update_led(0, 4);
    }
    else if(command == 'f'){
      web_door_status[5] = false;
      digitalWrite(lock6, HIGH);
      Serial.println("Lock6 Unlocked - Take Food");
      delay(drive_time);
      digitalWrite(lock6, LOW);
      update_led(0, 5);
    }
    else if(command == 'g'){
      web_door_status[6] = false;
      digitalWrite(lock7, HIGH);
      Serial.println("Lock7 Unlocked - Take Food");
      delay(drive_time);
      digitalWrite(lock7, LOW);
      update_led(0, 6);
    }
    else if(command == 'h'){
      web_door_status[7] = false;
      digitalWrite(lock8, HIGH);
      Serial.println("Lock8 Unlocked - Take Food");
      delay(drive_time);
      digitalWrite(lock8, LOW);
      update_led(0, 7);
    }
    else if(command == 'i'){
      web_door_status[8] = false;
      digitalWrite(lock9, HIGH);
      Serial.println("Lock9 Unlocked - Take Food");
      delay(drive_time);
      digitalWrite(lock9, LOW);
      update_led(0, 8);
    }
    else if(command == 'j'){
      web_door_status[9] = false;
      digitalWrite(lock10, HIGH);
      Serial.println("Lock10 Unlocked - Take Food");
      delay(drive_time);
      digitalWrite(lock10, LOW);
      update_led(0, 9);
    }
    command = '#';
  }
  ///////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
////////////////////////////////////////////////////////////////////////////////
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
        delay(1);                              //  Pause for a moment
      }
    }
    else if(box_number == 9){
      for(int i=0; i<16; i++) { // For each pixel in strip...
        strip.setPixelColor(i, strip.Color(0,   255,   0));         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
      }
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
void update_state(){
  //##################################################################################################################################################################
  //Update logic States for door Occupied or not
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    Serial1.println('S');   //Start ---> request to ESP
    while(1){
      if(Serial1.available()){ //Example String_data="1:1:0:0:1:0:1:1:0:0:0:0:&";
        char input[INPUT_SIZE];
        size_t size = Serial1.readBytesUntil('&', input, INPUT_SIZE);
        Serial.print("data_recieved = ");
        Serial.println(input);
        Serial.print("Size of data_recieved = ");
        Serial.println(size);


        if(size == INPUT_SIZE){
          // Read each command pair 
          char* command = strtok(input, ":");
          int index=0;
          if((command[0] == '0') || (command[0] == '1')){
            while (command != NULL)
            { 
                if(index<(INPUT_SIZE/2)) {
                  box_Status[index++] = atoi(command);
                }          
                // Find the next command in input string
                command = strtok(NULL, ":");
            }
            for(int i=0; i<Boxes;i++) if((box_Status[i]>=0) &&(box_Status[i]<=1)) data_tracker++;
            if(data_tracker == Boxes) {data_recieved = true; data_tracker=0;}  
          }
        }
      }

      if(data_recieved){
        for(int i=0; i<Boxes; i++) {
          if(box_Status[i]==1) {web_door_status[i] = true; update_led(1,i);}
          else {web_door_status[i] = false; update_led(0,i);}
        }
        Serial1.println('s'); //Stop ---> request to ESP
        data_recieved = false;
        break;
      }    
    } 
}
////////////////////////////////////////////////////////////////////////////////