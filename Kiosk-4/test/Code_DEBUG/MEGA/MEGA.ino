#include <Adafruit_NeoPixel.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define Boxes 12                 // No. of boxes present in current Kiosk
//////////////////////////////////
//////LED Control pins////////////
  #define LED_PIN_1    13
  #define LED_PIN_2    21
  #define LED_PIN_3    20
  #define LED_PIN_4    51
//////////////////////////////////
#define LED_COUNT_1 15          // No. of LED's in Column
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define lock1 28
#define lock2 30
#define lock3 32
#define lock4 22
#define lock5 24
#define lock6 26
#define lock7 34
#define lock8 36
#define lock9 38
#define lock10 46
#define lock11 42
#define lock12 48
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define drive_time 1000          // Relay drive time
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define INPUT_SIZE 25            // Size of data stream received from ESP32 to Mega 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int box_Status[Boxes];           // Box state from web stored here
int data_tracker = 0 ;           // tracker to check whether all data is received or not
bool data_recieved = false;      // data-received from ESP8266 or not
unsigned long SendTriggerTime;   // Used to check trigger command duration
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Locks[] = {lock1,lock2,lock3,lock4,lock5,lock6,lock7,lock8,lock9,lock10,lock11,lock12};
int No_of_locks = Boxes;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declare our NeoPixel strip object:
  Adafruit_NeoPixel strip1(LED_COUNT_1, LED_PIN_1, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel strip2(LED_COUNT_1, LED_PIN_2, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel strip3(LED_COUNT_1, LED_PIN_3, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel strip4(LED_COUNT_1, LED_PIN_4, NEO_GRB + NEO_KHZ800);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////LED arrangmenet MAP in Column//////////////////////////////////////////////////////////////////////////////////////
int led_column[3][5]={{0,1,2,3,4},{5,6,7,8,9},{10,11,12,13,14}};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool web_door_status[Boxes] = {false, false, false, false, false, false, false, false, false, false, false, false};  // flag to keep track of -> door unlocked states to keep food or take food
bool send_box_data[Boxes] =  {false, false, false, false, false, false, false, false, false, false, false, false};   // flag to keep track of -> Sensor data Push after every door unlocking operation
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void setup() {
  for(int i=0; i<No_of_locks;i++){
    pinMode(Locks[i],OUTPUT);
    digitalWrite(Locks[i], LOW);
  }
  ///////////////////////////////////////////////////////////////////////////////////
  //WS2812 LED Initialization////////////////////////////////////////////////////////
  strip1.begin();                 // INITIALIZE NeoPixel strip object (REQUIRED)
  strip1.show();                  // Turn OFF all pixels ASAP
  strip1.setBrightness(255);      // Set BRIGHTNESS to about 1/5 (max = 255)

  strip2.begin();                 // INITIALIZE NeoPixel strip object (REQUIRED)
  strip2.show();                // Turn OFF all pixels ASAP
  strip2.setBrightness(255);    // Set BRIGHTNESS to about 1/5 (max = 255)

  strip3.begin();               // INITIALIZE NeoPixel strip object (REQUIRED)
  strip3.show();                // Turn OFF all pixels ASAP
  strip3.setBrightness(255);    // Set BRIGHTNESS to about 1/5 (max = 255)

  strip4.begin();               // INITIALIZE NeoPixel strip object (REQUIRED)
  strip4.show();                // Turn OFF all pixels ASAP
  strip4.setBrightness(255);    // Set BRIGHTNESS to about 1/5 (max = 255)
  ///////////////////////////////////////////////////////////////////////////////////
 
  Serial.begin(9600);
  Serial3.begin(9600);

  update_state();
  update_led_status();
  Serial.println("Recieved box status");
  Serial.println("Regular kiosk operation started -------------------------> \nwaiting for commands!!!!");
}
//////////////////////////////////////////////////////////////////////////////// 
void loop() {
  //##################################################################################################################################################################
  ///////////////////////////////////////////////////////////////////////////////////
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  /////////////////////////Process serial command here///////////////////////////////
  if(Serial3.available()){
    char command = Serial3.read();
    Serial.print("Command = ");
    Serial.print(command);
    Serial.println(" Recieved");
    
    if(command == 'A'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      if(!web_door_status[0]){
        web_door_status[0] = true;
        digitalWrite(lock1, HIGH);
        Serial.println("Lock1 Unlocked - Keep Food");
        delay(drive_time);
        digitalWrite(lock1, LOW);
      }
    }
    else if(command == 'B'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      if(!web_door_status[1]){
        web_door_status[1] = true;
        digitalWrite(lock2, HIGH);
        Serial.println("Lock2 Unlocked - Keep Food");
        delay(drive_time);
        digitalWrite(lock2, LOW);
      }
    }
    else if(command == 'C'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      if(!web_door_status[2]){
        web_door_status[2] = true;
        digitalWrite(lock3, HIGH);
        Serial.println("Lock3 Unlocked - Keep Food");
        delay(drive_time);
        digitalWrite(lock3, LOW);
      }
    }
    else if(command == 'D'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      if(!web_door_status[3]){
        web_door_status[3] = true;
        digitalWrite(lock4, HIGH);
        Serial.println("Lock4 Unlocked - Keep Food");
        delay(drive_time);
        digitalWrite(lock4, LOW);
      }
    }
    else if(command == 'E'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      if(!web_door_status[4]){
        web_door_status[4] = true;
        digitalWrite(lock5, HIGH);
        Serial.println("Lock5 Unlocked - Keep Food");
        delay(drive_time);
        digitalWrite(lock5, LOW);
      }
    }
    else if(command == 'F'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      if(!web_door_status[5]){
        web_door_status[5] = true;
        digitalWrite(lock6, HIGH);
        Serial.println("Lock6 Unlocked - Keep Food");
        delay(drive_time);
        digitalWrite(lock6, LOW);
      }
    }
    else if(command == 'G'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      if(!web_door_status[6]){
        web_door_status[6] = true;
        digitalWrite(lock7, HIGH);
        Serial.println("Lock7 Unlocked - Keep Food");
        delay(drive_time);
        digitalWrite(lock7, LOW);
      }
    }
    else if(command == 'H'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      if(!web_door_status[7]){
        web_door_status[7] = true;
        digitalWrite(lock8, HIGH);
        Serial.println("Lock8 Unlocked - Keep Food");
        delay(drive_time);
        digitalWrite(lock8, LOW);
      }
    }
    else if(command == 'I'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      if(!web_door_status[8]){
        web_door_status[8] = true;
        digitalWrite(lock9, HIGH);
        Serial.println("Lock9 Unlocked - Keep Food");
        delay(drive_time);
        digitalWrite(lock9, LOW);
      }
    }
    else if(command == 'J'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      if(!web_door_status[9]){
        web_door_status[9] = true;
        digitalWrite(lock10, HIGH);
        Serial.println("Lock10 Unlocked - Keep Food");
        delay(drive_time);
        digitalWrite(lock10, LOW);
      }
    }
    else if(command == 'K'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      if(!web_door_status[10]){
        web_door_status[10] = true;
        digitalWrite(lock11, HIGH);
        Serial.println("Lock11 Unlocked - Keep Food");
        delay(drive_time);
        digitalWrite(lock11, LOW);
      }
    }
    else if(command == 'L'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      if(!web_door_status[11]){
        web_door_status[11] = true;
        digitalWrite(lock12, HIGH);
        Serial.println("Lock12 Unlocked - Keep Food");
        delay(drive_time);
        digitalWrite(lock12, LOW);
      }
    }
    else if(command == 'a'){
      if(web_door_status[0]){  
        web_door_status[0] = false;
        digitalWrite(lock1, HIGH);
        Serial.println("Lock1 Unlocked - Take Food");
        delay(drive_time);
        digitalWrite(lock1, LOW);
        send_box_data[0] = true;
        SendTriggerTime = millis();
      }
    }
    else if(command == 'b'){
      if(web_door_status[1]){  
        web_door_status[1] = false;
        digitalWrite(lock2, HIGH);
        Serial.println("Lock2 Unlocked - Take Food");
        delay(drive_time);
        digitalWrite(lock2, LOW);
        send_box_data[1] = true;
        SendTriggerTime = millis();
      }
    }
    else if(command == 'c'){
      if(web_door_status[2]){  
        web_door_status[2] = false;
        digitalWrite(lock3, HIGH);
        Serial.println("Lock3 Unlocked - Take Food");
        delay(drive_time);
        digitalWrite(lock3, LOW);
        send_box_data[2] = true;
        SendTriggerTime = millis();
      }
    }
    else if(command == 'd'){
      if(web_door_status[3]){  
        web_door_status[3] = false;
        digitalWrite(lock4, HIGH);
        Serial.println("Lock4 Unlocked - Take Food");
        delay(drive_time);
        digitalWrite(lock4, LOW);
        send_box_data[3] = true;
        SendTriggerTime = millis();
      }
    }
    else if(command == 'e'){
      if(web_door_status[4]){  
        web_door_status[4] = false;
        digitalWrite(lock5, HIGH);
        Serial.println("Lock5 Unlocked - Take Food");
        delay(drive_time);
        digitalWrite(lock5, LOW);
        send_box_data[4] = true;
        SendTriggerTime = millis();
      }
    }
    else if(command == 'f'){
      if(web_door_status[5]){  
        web_door_status[5] = false;
        digitalWrite(lock6, HIGH);
        Serial.println("Lock6 Unlocked - Take Food");
        delay(drive_time);
        digitalWrite(lock6, LOW);
        send_box_data[5] = true;
        SendTriggerTime = millis();
      }
    }
    else if(command == 'g'){
      if(web_door_status[6]){  
        web_door_status[6] = false;
        digitalWrite(lock7, HIGH);
        Serial.println("Lock7 Unlocked - Take Food");
        delay(drive_time);
        digitalWrite(lock7, LOW);
        send_box_data[6] = true;
        SendTriggerTime = millis();
      }
    }
    else if(command == 'h'){
      if(web_door_status[7]){  
        web_door_status[7] = false;
        digitalWrite(lock8, HIGH);
        Serial.println("Lock8 Unlocked - Take Food");
        delay(drive_time);
        digitalWrite(lock8, LOW);
        send_box_data[7] = true;
        SendTriggerTime = millis();
      }
    }
    else if(command == 'i'){
      if(web_door_status[8]){  
        web_door_status[8] = false;
        digitalWrite(lock9, HIGH);
        Serial.println("Lock9 Unlocked - Take Food");
        delay(drive_time);
        digitalWrite(lock9, LOW);
        send_box_data[8] = true;
        SendTriggerTime = millis();
      }
    }
    else if(command == 'j'){
      if(web_door_status[9]){  
        web_door_status[9] = false;
        digitalWrite(lock10, HIGH);
        Serial.println("Lock10 Unlocked - Take Food");
        delay(drive_time);
        digitalWrite(lock10, LOW);
        send_box_data[9] = true;
        SendTriggerTime = millis();
      }
    }
    else if(command == 'k'){
      if(web_door_status[10]){  
        web_door_status[10] = false;
        digitalWrite(lock11, HIGH);
        Serial.println("Lock11 Unlocked - Take Food");
        delay(drive_time);
        digitalWrite(lock11, LOW);
        send_box_data[10] = true;
        SendTriggerTime = millis();
      }
    }
    else if(command == 'l'){
      if(web_door_status[11]){  
        web_door_status[11] = false;
        digitalWrite(lock12, HIGH);
        Serial.println("Lock12 Unlocked - Take Food");
        delay(drive_time);
        digitalWrite(lock12, LOW);
        send_box_data[11] = true;
        SendTriggerTime = millis();
      }
    }
    command = '#';
  }
  /*for(int i=0; i<10; i++){
    
  }*/
  ///////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////LED Control Function's/////////////////////////////////////////////////////////////////////////////////////
void update_column1(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(0,   0,   255));          //  Set pixel's color (in RAM)
        strip4.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    }
  }
  else if(state == 1){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(0,   255,   0));          //  Set pixel's color (in RAM)
        strip4.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
  else if(state == 2){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(255,   0,  0));           //  Set pixel's color (in RAM)
        strip4.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
  else if(state == 3){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(0,   0,  0));           //  Set pixel's color (in RAM)
        strip4.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
  else if(state == 4){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(255,   120,  0));           //  Set pixel's color (in RAM)
        strip4.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
}
////////////////////////////////////////////////////////////////////////////////
void update_column2(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip3.setPixelColor(led_column[box][i], strip3.Color(0,   0,   255));          //  Set pixel's color (in RAM)
        strip3.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    }
  }
  else if(state == 1){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip3.setPixelColor(led_column[box][i], strip3.Color(0,   255,   0));          //  Set pixel's color (in RAM)
        strip3.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
  else if(state == 2){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip3.setPixelColor(led_column[box][i], strip3.Color(255,   0,   0));          //  Set pixel's color (in RAM)
        strip3.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
  else if(state == 3){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip3.setPixelColor(led_column[box][i], strip3.Color(0,   0,   0));          //  Set pixel's color (in RAM)
        strip3.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
  else if(state == 4){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip3.setPixelColor(led_column[box][i], strip3.Color(255,   120,   0));      //  Set pixel's color (in RAM)
        strip3.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
}
////////////////////////////////////////////////////////////////////////////////
void update_column3(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip2.setPixelColor(led_column[box][i], strip2.Color(0,   0,   255));          //  Set pixel's color (in RAM)
        strip2.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    }
  }
  else if(state == 1){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip2.setPixelColor(led_column[box][i], strip2.Color(0,   255,   0));          //  Set pixel's color (in RAM)
        strip2.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
  else if(state == 2){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip2.setPixelColor(led_column[box][i], strip2.Color(255,   0,   0));          //  Set pixel's color (in RAM)
        strip2.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
  else if(state == 3){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip2.setPixelColor(led_column[box][i], strip2.Color(0,   0,   0));          //  Set pixel's color (in RAM)
        strip2.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
  else if(state == 4){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip2.setPixelColor(led_column[box][i], strip2.Color(255,   120,   0));          //  Set pixel's color (in RAM)
        strip2.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
}
////////////////////////////////////////////////////////////////////////////////
void update_column4(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip1.setPixelColor(led_column[box][i], strip1.Color(0,   0,   255));          //  Set pixel's color (in RAM)
        strip1.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    }
  }
  else if(state == 1){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip1.setPixelColor(led_column[box][i], strip1.Color(0,   255,   0));          //  Set pixel's color (in RAM)
        strip1.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
  else if(state == 2){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip1.setPixelColor(led_column[box][i], strip1.Color(255,   0,   0));          //  Set pixel's color (in RAM)
        strip1.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
  else if(state == 3){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip1.setPixelColor(led_column[box][i], strip1.Color(0,   0,   0));          //  Set pixel's color (in RAM)
        strip1.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
  else if(state == 4){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip1.setPixelColor(led_column[box][i], strip1.Color(255,   120,   0));          //  Set pixel's color (in RAM)
        strip1.show();                                              //  Update strip to match
        delay(1);                                                   //  Pause for a moment
    } 
  }
}
//////////////////////////////////false//////////////////////////////////////////////////////////////////////////////////////////////
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXtrueXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void update_led_status(){
//Update led States for door Opening/closing || Occupied or not
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if(!web_door_status[0]) 
      {
        ///////////////////////////
          //update LED color to blue
          ///////////////////////////
          update_column1(2, 0);
          ///////////////////////////
      }
      if(web_door_status[0])
      {
        ///////////////////////////
          //update LED color to green
          ///////////////////////////
          update_column1(1, 0);
          ///////////////////////////
      }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if(!web_door_status[1])
      {
        ///////////////////////////
          //update LED color to blue
          ///////////////////////////
          update_column1(2, 1);
          ///////////////////////////
      }
      if(web_door_status[1])
      {
        ///////////////////////////
          //update LED color to green
          ///////////////////////////
          update_column1(1, 1);
          ///////////////////////////
      }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if(!web_door_status[2]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to blue
          ///////////////////////////
          update_column1(2, 2);
          ///////////////////////////
      }
      if(web_door_status[2]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to green
          ///////////////////////////
          update_column1(1, 2);
          ///////////////////////////
      }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if(!web_door_status[3]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to blue
          ///////////////////////////
          update_column2(2, 0);
          ///////////////////////////
      }
      if(web_door_status[3]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to green
          ///////////////////////////
          update_column2(1, 0);
          ///////////////////////////
      }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if(!web_door_status[4]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to blue
          ///////////////////////////
          update_column2(2, 1);
          ///////////////////////////
      }
      if(web_door_status[4]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to green
          ///////////////////////////
          update_column2(1, 1);
          ///////////////////////////
      }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if(!web_door_status[5]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to blue
          ///////////////////////////
          update_column2(2, 2);
          ///////////////////////////
      }
      if(web_door_status[5]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to green
          ///////////////////////////
          update_column2(1, 2);
          ///////////////////////////
      }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if(!web_door_status[6]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to blue
          ///////////////////////////
          update_column3(2, 0);
          ///////////////////////////
      }
      if(web_door_status[6]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to green
          ///////////////////////////
          update_column3(1, 0);
          ///////////////////////////
      }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if(!web_door_status[7]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to blue
          ///////////////////////////
          update_column3(2, 1);
          ///////////////////////////
      }
      if(web_door_status[7]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to green
          ///////////////////////////
          update_column3(1, 1);
          ///////////////////////////
      }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if(!web_door_status[8]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to blue
          ///////////////////////////
          update_column3(2, 2);
          ///////////////////////////
      }
      if(web_door_status[8]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to green
          ///////////////////////////
          update_column3(1, 2);
          ///////////////////////////
      }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if(!web_door_status[9]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to blue
          ///////////////////////////
          update_column4(2, 0);
          ///////////////////////////
      }
      if(web_door_status[9]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to green
          ///////////////////////////
          update_column4(1, 0);
          ///////////////////////////
      }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if(!web_door_status[10]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to blue
          ///////////////////////////
          update_column4(2, 1);
          ///////////////////////////
      }
      if(web_door_status[10]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to green
          ///////////////////////////
          update_column4(1, 1);
          ///////////////////////////
      }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      if(!web_door_status[11]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to blue
          ///////////////////////////
          update_column4(2, 2);
          ///////////////////////////
      }
      if(web_door_status[11]) // false: door closed | No food Present | Locker not occupied on the Web
      {
        ///////////////////////////
          //update LED color to green
          ///////////////////////////
          update_column4(1, 2);
          ///////////////////////////
      }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  ///////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void update_state(){
  //##################################################################################################################################################################
  //Update logic States for door Occupied or not
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    while(1){

      Serial3.println("S");   //Start ---> request to ESP
      Serial.println("S trigger sent");
      Serial.flush();
      if(Serial3.available()){ //Example String_data="1:1:0:0:1:0:1:1:0:0:0:0:&";
        char input[INPUT_SIZE];

        // size_t size = Serial3.readBytesUntil('&', input, INPUT_SIZE);
        String data = Serial3.readStringUntil('&');
        Serial.print("data_recieved = ");
        Serial.println(data);

        data.toCharArray(input, INPUT_SIZE);

        size_t size = strlen(input);
        Serial.print("Size of data_recieved = ");
        Serial.println(size);

        if(size == INPUT_SIZE-1){
          Serial.println("Processing data...");
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
              Serial.print("data tracker = "); Serial.println(data_tracker);
            if(data_tracker == Boxes) {data_recieved = true; data_tracker=0;}  
          }
        }
      }

      if(data_recieved){
        Serial.println("[[[[[[Data received successfully]]]]]]");
        for(int i=0; i<Boxes; i++) {
          if(box_Status[i]==1) {web_door_status[i] = true; }
          else {web_door_status[i] = false; }
        }
        Serial3.println("s"); //Stop ---> request to ESP
        Serial.println("small s triggger sent  ------------------------>");
        data_recieved = false;
        break;
      }
      // Serial3.println("Z");   //Start ---> request to ESP
      // Serial.println("Z trigger sent");    
      delay(1000);
    } 
}
////////////////////////////////////////////////////////////////////////////////