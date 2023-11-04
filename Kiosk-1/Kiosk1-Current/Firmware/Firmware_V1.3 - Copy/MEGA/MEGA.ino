#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(53, 25); // RX, TX ----> 53,25
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define Boxes 10                 // No. of boxes present in current Kiosk
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LED_PIN  21
#define LED_COUNT 50
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define lock1 12//10 11 12 13 6 7 8 9
#define lock2 7
#define lock3 16
#define lock4 11
#define lock5 6
#define lock6 14
#define lock7 10
#define lock8 8
#define lock9 15
#define lock10 17
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define drive_time 500          // Relay drive time
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define INPUT_SIZE 21            // Size of data stream received from ESP32 to Mega 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int box_Status[Boxes];           // Box state from web stored here
int data_tracker = 0 ;           // tracker to check whether all data is received or not
bool data_recieved = false;      // data-received from ESP8266 or not
unsigned long SendTriggerTime;   // Used to check trigger command duration
bool Internet_Connected = false;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Locks[] = {lock1,lock2,lock3,lock4,lock5,lock6,lock7,lock8,lock9,lock10};
int No_of_locks = Boxes;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int led_sequence[9][4]={{39,40,41,42}, {27,28,29,30}, {15,16,17,18}, {43,44,45,46}, {31,32,33,34}, {19,20,21,22}, {47,48,49,49}, {35,36,37,38}, {23,24,25,26}};
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool web_door_status[Boxes] = {false, false, false, false, false, false, false, false, false, false};  // flag to keep track of -> door unlocked states to keep food or take food
bool send_box_data[Boxes] =  {false, false, false, false, false, false, false, false, false, false};   // flag to keep track of -> Sensor data Push after every door unlocking operation
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void setup() {
  for(int i=0; i<No_of_locks;i++){
    pinMode(Locks[i],OUTPUT);
    digitalWrite(Locks[i], LOW);
  }
 
  Serial.begin(9600);
  mySerial.begin(9600);

  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  // colorWipe(strip.Color(0,   0,   255), 1);

  update_state();
  // Serial.println("Recieved box status");
  // Serial.println("Regular kiosk operation started -------------------------> \nwaiting for commands!!!!");
}
//////////////////////////////////////////////////////////////////////////////// 
void loop() {
  //##################################################################################################################################################################
  ///////////////////////////////////////////////////////////////////////////////////
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  /////////////////////////Process serial command here///////////////////////////////
  if(mySerial.available()){
    char command = mySerial.read();
    // Serial.print("Command = ");
    // Serial.print(command);
    // Serial.println(" Recieved");
    
    if(Internet_Connected ){

      if(command == 'A'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        if(!web_door_status[0]){
          web_door_status[0] = true;
          digitalWrite(lock1, HIGH);
          // Serial.println("Lock1 Unlocked - Keep Food");
          delay(drive_time);
          digitalWrite(lock1, LOW);
          update_led(1, 0);
        }
      }
      else if(command == 'B'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        if(!web_door_status[1]){
          web_door_status[1] = true;
          digitalWrite(lock2, HIGH);
          // Serial.println("Lock2 Unlocked - Keep Food");
          delay(drive_time);
          digitalWrite(lock2, LOW);
          update_led(1, 1);
        }
      }
      else if(command == 'C'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        if(!web_door_status[2]){
          web_door_status[2] = true;
          digitalWrite(lock3, HIGH);
          // Serial.println("Lock3 Unlocked - Keep Food");
          delay(drive_time);
          digitalWrite(lock3, LOW);
          update_led(1, 2);
        }
      }
      else if(command == 'D'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        if(!web_door_status[3]){
          web_door_status[3] = true;
          digitalWrite(lock4, HIGH);
          // Serial.println("Lock4 Unlocked - Keep Food");
          delay(drive_time);
          digitalWrite(lock4, LOW);
          update_led(1, 3);
        }
      }
      else if(command == 'E'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        if(!web_door_status[4]){
          web_door_status[4] = true;
          digitalWrite(lock5, HIGH);
          // Serial.println("Lock5 Unlocked - Keep Food");
          delay(drive_time);
          digitalWrite(lock5, LOW);
          update_led(1, 4);
        }
      }
      else if(command == 'F'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        if(!web_door_status[5]){
          web_door_status[5] = true;
          digitalWrite(lock6, HIGH);
          // Serial.println("Lock6 Unlocked - Keep Food");
          delay(drive_time);
          digitalWrite(lock6, LOW);
          update_led(1, 5);
        }
      }
      else if(command == 'G'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        if(!web_door_status[6]){
          web_door_status[6] = true;
          digitalWrite(lock7, HIGH);
          // Serial.println("Lock7 Unlocked - Keep Food");
          delay(drive_time);
          digitalWrite(lock7, LOW);
          update_led(1, 6);
        }
      }
      else if(command == 'H'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        if(!web_door_status[7]){
          web_door_status[7] = true;
          digitalWrite(lock8, HIGH);
          // Serial.println("Lock8 Unlocked - Keep Food");
          delay(drive_time);
          digitalWrite(lock8, LOW);
          update_led(1, 7);
        }
      }
      else if(command == 'I'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        if(!web_door_status[8]){
          web_door_status[8] = true;
          digitalWrite(lock9, HIGH);
          // Serial.println("Lock9 Unlocked - Keep Food");
          delay(drive_time);
          digitalWrite(lock9, LOW);
          update_led(1, 8);
        }
      }
      else if(command == 'J'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        if(!web_door_status[9]){
          web_door_status[9] = true;
          digitalWrite(lock10, HIGH);
          // Serial.println("Lock10 Unlocked - Keep Food");
          delay(drive_time);
          digitalWrite(lock10, LOW);
          update_led(1, 9);
        }
      }
      else if(command == 'a'){
        if(web_door_status[0]){  
          web_door_status[0] = false;
          digitalWrite(lock1, HIGH);
          // Serial.println("Lock1 Unlocked - Take Food");
          delay(drive_time);
          digitalWrite(lock1, LOW);
          update_led(0, 0);
          send_box_data[0] = true;
          SendTriggerTime = millis();
        }
      }
      else if(command == 'b'){
        if(web_door_status[1]){  
          web_door_status[1] = false;
          digitalWrite(lock2, HIGH);
          // Serial.println("Lock2 Unlocked - Take Food");
          delay(drive_time);
          digitalWrite(lock2, LOW);
          update_led(0, 1);
          send_box_data[1] = true;
          SendTriggerTime = millis();
        }
      }
      else if(command == 'c'){
        if(web_door_status[2]){  
          web_door_status[2] = false;
          digitalWrite(lock3, HIGH);
          // Serial.println("Lock3 Unlocked - Take Food");
          delay(drive_time);
          digitalWrite(lock3, LOW);
          update_led(0, 2);
          send_box_data[2] = true;
          SendTriggerTime = millis();
        }
      }
      else if(command == 'd'){
        if(web_door_status[3]){  
          web_door_status[3] = false;
          digitalWrite(lock4, HIGH);
          // Serial.println("Lock4 Unlocked - Take Food");
          delay(drive_time);
          digitalWrite(lock4, LOW);
          update_led(0, 3);
          send_box_data[3] = true;
          SendTriggerTime = millis();
        }
      }
      else if(command == 'e'){
        if(web_door_status[4]){  
          web_door_status[4] = false;
          digitalWrite(lock5, HIGH);
          // Serial.println("Lock5 Unlocked - Take Food");
          delay(drive_time);
          digitalWrite(lock5, LOW);
          update_led(0, 4);
          send_box_data[4] = true;
          SendTriggerTime = millis();
        }
      }
      else if(command == 'f'){
        if(web_door_status[5]){  
          web_door_status[5] = false;
          digitalWrite(lock6, HIGH);
          // Serial.println("Lock6 Unlocked - Take Food");
          delay(drive_time);
          digitalWrite(lock6, LOW);
          update_led(0, 5);
          send_box_data[5] = true;
          SendTriggerTime = millis();
        }
      }
      else if(command == 'g'){
        if(web_door_status[6]){  
          web_door_status[6] = false;
          digitalWrite(lock7, HIGH);
          // Serial.println("Lock7 Unlocked - Take Food");
          delay(drive_time);
          digitalWrite(lock7, LOW);
          update_led(0, 6);
          send_box_data[6] = true;
          SendTriggerTime = millis();
        }
      }
      else if(command == 'h'){
        if(web_door_status[7]){  
          web_door_status[7] = false;
          digitalWrite(lock8, HIGH);
          // Serial.println("Lock8 Unlocked - Take Food");
          delay(drive_time);
          digitalWrite(lock8, LOW);
          update_led(0, 7);
          send_box_data[7] = true;
          SendTriggerTime = millis();
        }
      }
      else if(command == 'i'){
        if(web_door_status[8]){  
          web_door_status[8] = false;
          digitalWrite(lock9, HIGH);
          // Serial.println("Lock9 Unlocked - Take Food");
          delay(drive_time);
          digitalWrite(lock9, LOW);
          update_led(0, 8);
          send_box_data[8] = true;
          SendTriggerTime = millis();
        }
      }
      else if(command == 'j'){
        if(web_door_status[9]){  
          web_door_status[9] = false;
          digitalWrite(lock10, HIGH);
          // Serial.println("Lock10 Unlocked - Take Food");
          delay(drive_time);
          digitalWrite(lock10, LOW);
          update_led(0, 9);
          send_box_data[9] = true;
          SendTriggerTime = millis();
        }
      }

    }
    
    if(command == 'X'){  //Capital X    <<<<<- Turn off Complete strip
      update_led(2, 9);
      update_led(2, 8);
      update_led(2, 7);
      update_led(2, 6);
      update_led(2, 5);
      update_led(2, 4);
      update_led(2, 3);
      update_led(2, 2);
      update_led(2, 1);
      update_led(2, 0);
      Internet_Connected = false;
    }
    else if(command == 'x'){  //Small x
      Internet_Connected = true;
    }

    command = '#';
  }
  /*for(int i=0; i<10; i++){
    
  }*/
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
      for(int i=0; i<15; i++) { // For each pixel in strip...
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
      for(int i=0; i<15; i++) { // For each pixel in strip...
        strip.setPixelColor(i, strip.Color(0,   255,   0));         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
      }
    }
  }
  else if(state == 2){
    if(box_number >=0 && box_number < 9){
      for(int i=0; i<4; i++) { // For each pixel in strip...
        strip.setPixelColor(led_sequence[box_number][i], strip.Color(0,   0,   0));         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
      }
    }
    else if(box_number == 9){
      for(int i=0; i<15; i++) { // For each pixel in strip...
        strip.setPixelColor(i, strip.Color(0,   0,   0));         //  Set pixel's color (in RAM)
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
    while(1){

      mySerial.println("S");   //Start ---> request to ESP
      // Serial.println("S trigger sent");
      Serial.flush();
      if(mySerial.available()){ //Example String_data="1:1:0:0:1:0:1:1:0:0:0:0:&";
        char input[INPUT_SIZE];

        // size_t size = mySerial.readBytesUntil('&', input, INPUT_SIZE);
        String data = mySerial.readStringUntil('&');
        // Serial.print("data_recieved = ");
        // Serial.println(data);

        data.toCharArray(input, INPUT_SIZE);

        size_t size = strlen(input);
        Serial.print("Size of data_recieved = ");
        Serial.println(size);

        if(size == INPUT_SIZE-1){
          // Serial.println("Processing data...");
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
              // Serial.print("data tracker = "); Serial.println(data_tracker);
            if(data_tracker == Boxes) {data_recieved = true; data_tracker=0;}  
          }
        }
      }

      if(data_recieved){
        // Serial.println("[[[[[[Data received successfully]]]]]]");
        for(int i=0; i<Boxes; i++) {
          if(box_Status[i]==1) {web_door_status[i] = true; update_led(1,i);}
          else {web_door_status[i] = false; update_led(0,i);}
        }
        Internet_Connected = true;
        mySerial.println("s"); //Stop ---> request to ESP
        // Serial.println("small s triggger sent  ------------------------>");
        data_recieved = false;
        break;
      }
      // mySerial.println("Z");   //Start ---> request to ESP
      // Serial.println("Z trigger sent");    
      delay(1000);
    } 
}
////////////////////////////////////////////////////////////////////////////////