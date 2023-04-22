////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <NewPing.h>            // Ultrasonic Sensor library
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////Light Control pins & it's libraries//////////////////////////////////////////////////////////////////////////////
#include <Adafruit_NeoPixel.h>
//////////////////////////////////
//////LED Control pins////////////
	#define LED_PIN_1    13
	#define LED_PIN_2    21
	#define LED_PIN_3    20
	#define LED_PIN_4    51
//////////////////////////////////
#define LED_COUNT_1 15          // No. of LED's in Column
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define Item_distance 30        // Max Detectable object distance from Ultrasonic Sensor (in cm)
////////////////////////////Lock Control pins///////////////////////////////////////////////////////////////////////////////////////
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
	// #define lock13 12
	// #define lock14 44
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////Lock Feedback pins//////////////////////////////////////////////////////////////////////////////////////
	#define lock1F A4
	#define lock2F A5
	#define lock3F A6
	#define lock4F A7
	#define lock5F A8
	#define lock6F A9
	#define lock7F A10
	#define lock8F A11
	#define lock9F A12
	#define lock10F A13
	#define lock11F A14
	#define lock12F A15
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Temperature feedback pins////////////////////////////////////////////////////////////////////////////////
	#define TF1 23
	#define TF2 25
	#define TF3 27
	#define TF4 29
	#define TF5 31
	#define TF6 33
	#define TF7 35
	#define TF8 37
	#define TF9 39
	#define TF10 41
	#define TF11 43
	#define TF12 47
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define buzzer 53                // Buzzer Control
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define drive_time 1200          // Relay drive time
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////Ultrasonic Sensor Pins and Controls//////////////////////////////////////////////////////////////////////////
	#define TRIGGER_PIN  52          // Trigger pin on the ultrasonic sensor.
	#define ECHO_PIN     52          // Echo pin on the ultrasonic sensor.
	#define MAX_DISTANCE 400         // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

	#define EN 50                    // Enable pin for MUX
	#define S0 A0                    // Selection pin for MUX
	#define S1 A1                    // Selection pin for MUX
	#define S2 A2                    // Selection pin for MUX
	#define S3 A3                    // Selection pin for MUX

	NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

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
int box_number = 0;            //Used for ultrasonic sensor
int distance = 0;              //Used for ultrasonic sensor
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define Boxes 12                 // No. of boxes present in current Kiosk
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define INPUT_SIZE 25            // Size of data stream received from ESP32 to Mega 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int box_Status[Boxes];           // Box state from web stored here
int data_tracker = 0 ;           // tracker to check whether all data is received or not
bool data_recieved = false;      // data-received from ESP8266/ESP32 or not
unsigned long SendTriggerTime;   // Used to check trigger command duration
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool door_lock_state[Boxes] = {false, false, false, false, false, false, false, false, false, false, false, false};
bool food_present_state[Boxes] = {false, false, false, false, false, false, false, false, false, false, false, false};
bool web_door_status[Boxes] = {false, false, false, false, false, false, false, false, false, false, false, false};
bool send_box_data[Boxes] = {false, false, false, false, false, false, false, false, false, false, false, false};   // flag to keep track of -> Sensor data Push after every door unlocking operation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX//
void setup(){
	Serial.begin(9600);
	Serial3.begin(9600);
	///////////////////////////////////////////////////////////////////////////////////
	// Lock Initilization//////////////////////////////////////////////////////////////
	pinMode(lock1, OUTPUT);
	pinMode(lock2, OUTPUT);
	pinMode(lock3, OUTPUT);
	pinMode(lock4, OUTPUT);
	pinMode(lock5, OUTPUT);
	pinMode(lock6, OUTPUT);
	pinMode(lock7, OUTPUT);
	pinMode(lock8, OUTPUT);
	pinMode(lock9, OUTPUT);
	pinMode(lock10, OUTPUT);
	pinMode(lock11, OUTPUT);
	pinMode(lock12, OUTPUT);

	digitalWrite(lock1, LOW);
	digitalWrite(lock2, LOW);
	digitalWrite(lock3, LOW);
	digitalWrite(lock4, LOW);
	digitalWrite(lock5, LOW);
	digitalWrite(lock6, LOW);
	digitalWrite(lock7, LOW);
	digitalWrite(lock8, LOW);
	digitalWrite(lock9, LOW);
	digitalWrite(lock10, LOW);
	digitalWrite(lock11, LOW);
	digitalWrite(lock12, LOW);
	///////////////////////////////////////////////////////////////////////////////////
	//LOCK Feedback Initialization/////////////////////////////////////////////////////
	pinMode(lock1F, INPUT);
	pinMode(lock2F, INPUT);
	pinMode(lock3F, INPUT);
	pinMode(lock4F, INPUT);
	pinMode(lock5F, INPUT);
	pinMode(lock6F, INPUT);
	pinMode(lock7F, INPUT);
	pinMode(lock8F, INPUT);
	pinMode(lock9F, INPUT);
	pinMode(lock10F, INPUT);
	pinMode(lock11F, INPUT);
	pinMode(lock12F, INPUT);
	///////////////////////////////////////////////////////////////////////////////////
	//Temperature Feedback Initialization//////////////////////////////////////////////
	pinMode(TF1, INPUT);
	pinMode(TF2, INPUT);
	pinMode(TF3, INPUT);
	pinMode(TF4, INPUT);
	pinMode(TF5, INPUT);
	pinMode(TF6, INPUT);
	pinMode(TF7, INPUT);
	pinMode(TF8, INPUT);
	pinMode(TF9, INPUT);
	pinMode(TF10, INPUT);
	pinMode(TF11, INPUT);
	pinMode(TF12, INPUT);
	///////////////////////////////////////////////////////////////////////////////////
	//Buzzer Initialization////////////////////////////////////////////////////////////
	pinMode(buzzer, OUTPUT);
	digitalWrite(buzzer, LOW);      //Turn off Buzzer
	///////////////////////////////////////////////////////////////////////////////////
	//Ultrasonic Sensor Initialization/////////////////////////////////////////////////
	pinMode(EN, OUTPUT);
  	pinMode(S0, OUTPUT);
  	pinMode(S1, OUTPUT);
  	pinMode(S2, OUTPUT);
  	pinMode(S3, OUTPUT);

  	digitalWrite(EN , LOW);
  	digitalWrite(S0 , LOW);
  	digitalWrite(S1 , LOW);
  	digitalWrite(S2 , LOW);
  	digitalWrite(S3 , LOW);

  ///////////////////////////////////////////////////////////////////////////////////
	//WS2812 LED Initialization////////////////////////////////////////////////////////
	strip1.begin();               	// INITIALIZE NeoPixel strip object (REQUIRED)
	strip1.show();                	// Turn OFF all pixels ASAP
    strip1.setBrightness(255);    	// Set BRIGHTNESS to about 1/5 (max = 255)

    strip2.begin();           	  	// INITIALIZE NeoPixel strip object (REQUIRED)
    strip2.show();            		// Turn OFF all pixels ASAP
    strip2.setBrightness(255); 		// Set BRIGHTNESS to about 1/5 (max = 255)

    strip3.begin();           		// INITIALIZE NeoPixel strip object (REQUIRED)
    strip3.show();            		// Turn OFF all pixels ASAP
    strip3.setBrightness(255); 		// Set BRIGHTNESS to about 1/5 (max = 255)

    strip4.begin();           		// INITIALIZE NeoPixel strip object (REQUIRED)
    strip4.show();            		// Turn OFF all pixels ASAP
    strip4.setBrightness(255); 		// Set BRIGHTNESS to about 1/5 (max = 255)
  ///////////////////////////////////////////////////////////////////////////////////
  update_state();
  update_web_status();
  update_led_status();

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop(){

	//##################################################################################################################################################################
	///////////////////////////////////////////////////////////////////////////////////
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	/////////////////////////Process serial command here///////////////////////////////
	if(Serial3.available()){
		char command = Serial3.read();
		
		// LED Status update command
		// update_column1(0, 0);update_column1(1, 0);update_column1(0, 1);update_column1(1, 1);update_column1(0, 2);update_column1(1, 2);
		// update_column1(State-0(blue)/1(green), box-0/1/2);

		//Lock-open(1) closed(0)
		//Temperature default 1 : above threshold 0
		//U.S: W/o >30 W<30

		if(command == 'A'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			web_door_status[0] = true;
				if(door_lock_state[0] == false){
					digitalWrite(lock1, HIGH);
					Serial.println("Lock1 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door1 already open");
				}
				digitalWrite(lock1, LOW);

			//////////////////////////
			//update door state
			door_lock_state[0] = true; 
			//////////////////////////
		}
		else if(command == 'B'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			web_door_status[1] = true;
				if(door_lock_state[1] == false){
					digitalWrite(lock2, HIGH);
					Serial.println("Lock2 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door2 already open");
				}
				digitalWrite(lock2, LOW);

			//////////////////////////
			//update door state
			door_lock_state[1] = true; 
			//////////////////////////
		}
		else if(command == 'C'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			web_door_status[2] = true;
				if(door_lock_state[2] == false){
					digitalWrite(lock3, HIGH);
					Serial.println("Lock3 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door3 already open");
				}
				digitalWrite(lock3, LOW);

			//////////////////////////
			//update door state
			door_lock_state[2] = true; 
			//////////////////////////
		}
		else if(command == 'D'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			web_door_status[3] = true;
				if(door_lock_state[3] == false){
					digitalWrite(lock4, HIGH);
					Serial.println("Lock4 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door4 already open");
				}
				digitalWrite(lock4, LOW);

			//////////////////////////
			//update door state
			door_lock_state[3] = true; 
			//////////////////////////
		}
		else if(command == 'E'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			web_door_status[4] = true;
				if(door_lock_state[4] == false){
					digitalWrite(lock5, HIGH);
					Serial.println("Lock5 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door5 already open");
				}
				digitalWrite(lock5, LOW);

			//////////////////////////
			//update door state
			door_lock_state[4] = true; 
			//////////////////////////
		}
		else if(command == 'F'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			web_door_status[5] = true;
				if(door_lock_state[5] == false){
					digitalWrite(lock6, HIGH);
					Serial.println("Lock6 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door6 already open");
				}
				digitalWrite(lock6, LOW);

			//////////////////////////
			//update door state
			door_lock_state[5] = true; 
			//////////////////////////
		}
		else if(command == 'G'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			web_door_status[6] = true;
				if(door_lock_state[6] == false){
					digitalWrite(lock7, HIGH);
					Serial.println("Lock7 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door7 already open");
				}
				digitalWrite(lock7, LOW);

			//////////////////////////
			//update door state
			door_lock_state[6] = true; 
			//////////////////////////
		}
		else if(command == 'H'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			web_door_status[7] = true;
				if(door_lock_state[7] == false){
					digitalWrite(lock8, HIGH);
					Serial.println("Lock8 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door8 already open");
				}
				digitalWrite(lock8, LOW);

			//////////////////////////
			//update door state
			door_lock_state[7] = true; 
			//////////////////////////
		}
		else if(command == 'I'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			web_door_status[8] = true;
				if(door_lock_state[8] == false){
					digitalWrite(lock9, HIGH);
					Serial.println("Lock9 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door9 already open");
				}
				digitalWrite(lock9, LOW);

			//////////////////////////
			//update door state
			door_lock_state[8] = true; 
			//////////////////////////
		}
		else if(command == 'J'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			web_door_status[9] = true;
				if(door_lock_state[9] == false){
					digitalWrite(lock10, HIGH);
					Serial.println("Lock10 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door10 already open");
				}
				digitalWrite(lock10, LOW);

			//////////////////////////
			//update door state
			door_lock_state[9] = true; 
			//////////////////////////
		}
		else if(command == 'K'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			web_door_status[10] = true;
				if(door_lock_state[10] == false){
					digitalWrite(lock11, HIGH);
					Serial.println("Lock11 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door11 already open");
				}
				digitalWrite(lock11, LOW);

			//////////////////////////
			//update door state
			door_lock_state[10] = true; 
			//////////////////////////
		}
		else if(command == 'L'){//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			web_door_status[11] = true;
				if(door_lock_state[11] == false){
					digitalWrite(lock12, HIGH);
					Serial.println("Lock12 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door12 already open");
				}
				digitalWrite(lock12, LOW);

			//////////////////////////
			//update door state
			door_lock_state[11] = true; 
			//////////////////////////
		}
		else if(command == 'a'){
			web_door_status[0] = false;
				if(door_lock_state[0] == false){
					digitalWrite(lock1, HIGH);
					Serial.println("Lock1 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door1 already open");
				}
				digitalWrite(lock1, LOW);

			//////////////////////////
			//update door state
			door_lock_state[0] = true; 
			//////////////////////////
		}
		else if(command == 'b'){
			web_door_status[1] = false;
				if(door_lock_state[1] == false){
					digitalWrite(lock2, HIGH);
					Serial.println("Lock2 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door2 already open");
				}
				digitalWrite(lock2, LOW);

			//////////////////////////
			//update door state
			door_lock_state[1] = true; 
			//////////////////////////
		}
		else if(command == 'c'){
			web_door_status[2] = false;
				if(door_lock_state[2] == false){
					digitalWrite(lock3, HIGH);
					Serial.println("Lock3 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door3 already open");
				}
				digitalWrite(lock3, LOW);

			//////////////////////////
			//update door state
			door_lock_state[2] = true; 
			//////////////////////////
		}
		else if(command == 'd'){
			web_door_status[3] = false;
				if(door_lock_state[3] == false){
					digitalWrite(lock4, HIGH);
					Serial.println("Lock4 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door4 already open");
				}
				digitalWrite(lock4, LOW);

			//////////////////////////
			//update door state
			door_lock_state[3] = true; 
			//////////////////////////
		}
		else if(command == 'e'){
			web_door_status[4] = false;
				if(door_lock_state[4] == false){
					digitalWrite(lock5, HIGH);
					Serial.println("Lock5 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door5 already open");
				}
				digitalWrite(lock5, LOW);

			//////////////////////////
			//update door state
			door_lock_state[4] = true; 
			//////////////////////////
		}
		else if(command == 'f'){
			web_door_status[5] = false;
				if(door_lock_state[5] == false){
					digitalWrite(lock6, HIGH);
					Serial.println("Lock6 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door6 already open");
				}
				digitalWrite(lock6, LOW);

			//////////////////////////
			//update door state
			door_lock_state[5] = true; 
			//////////////////////////
		}
		else if(command == 'g'){
			web_door_status[6] = false;
				if(door_lock_state[6] == false){
					digitalWrite(lock7, HIGH);
					Serial.println("Lock7 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door7 already open");
				}
				digitalWrite(lock7, LOW);

			//////////////////////////
			//update door state
			door_lock_state[6] = true; 
			//////////////////////////
		}
		else if(command == 'h'){
			web_door_status[7] = false;
				if(door_lock_state[7] == false){
					digitalWrite(lock8, HIGH);
					Serial.println("Lock8 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door8 already open");
				}
				digitalWrite(lock8, LOW);

			//////////////////////////
			//update door state
			door_lock_state[7] = true; 
			//////////////////////////
		}
		else if(command == 'i'){
			web_door_status[8] = false;
				if(door_lock_state[8] == false){
					digitalWrite(lock9, HIGH);
					Serial.println("Lock9 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door9 already open");
				}
				digitalWrite(lock9, LOW);

			//////////////////////////
			//update door state
			door_lock_state[8] = true; 
			//////////////////////////
		}
		else if(command == 'j'){
			web_door_status[9] = false;
				if(door_lock_state[9] == false){
					digitalWrite(lock10, HIGH);
					Serial.println("Lock10 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door10 already open");
				}
				digitalWrite(lock10, LOW);

			//////////////////////////
			//update door state
			door_lock_state[9] = true; 
			//////////////////////////
		}
		else if(command == 'k'){
			web_door_status[10] = false;
				if(door_lock_state[10] == false){
					digitalWrite(lock11, HIGH);
					Serial.println("Lock11 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door11 already open");
				}
				digitalWrite(lock11, LOW);

			//////////////////////////
			//update door state
			door_lock_state[10] = true; 
			//////////////////////////
		}
		else if(command == 'l'){
			web_door_status[11] = false;
				if(door_lock_state[11] == false){
					digitalWrite(lock12, HIGH);
					Serial.println("Lock12 Unlocked");
					delay(drive_time);
				}
				else{
					Serial.println("Door12 already open");
				}
				digitalWrite(lock12, LOW);

			//////////////////////////
			//update door state
			door_lock_state[11] = true; 
			//////////////////////////
		}
		command = '#';

	}
	///////////////////////////////////////////////////////////////////////////////////
	update_state();
	///////////////////////////////////////////////////////////////////////////////////
	update_led_status();
	//##################################################################################################################################################################

}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////LED Control Function's/////////////////////////////////////////////////////////////////////////////////////
void update_column1(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(0,   0,   255));         	//  Set pixel's color (in RAM)
        strip4.show();                          										//  Update strip to match
        delay(1);                             											//  Pause for a moment
    }
  }
  else if(state == 1){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(0,   255,   0));         	//  Set pixel's color (in RAM)
        strip4.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
  else if(state == 2){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(255,   0,  0));         	//  Set pixel's color (in RAM)
        strip4.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
  else if(state == 3){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(0,   0,  0));         	//  Set pixel's color (in RAM)
        strip4.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
  else if(state == 4){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(255,   120,  0));         	//  Set pixel's color (in RAM)
        strip4.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
}
////////////////////////////////////////////////////////////////////////////////
void update_column2(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip3.setPixelColor(led_column[box][i], strip3.Color(0,   0,   255));         	//  Set pixel's color (in RAM)
        strip3.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    }
  }
  else if(state == 1){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip3.setPixelColor(led_column[box][i], strip3.Color(0,   255,   0));         	//  Set pixel's color (in RAM)
        strip3.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
  else if(state == 2){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip3.setPixelColor(led_column[box][i], strip3.Color(255,   0,   0));         	//  Set pixel's color (in RAM)
        strip3.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
  else if(state == 3){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip3.setPixelColor(led_column[box][i], strip3.Color(0,   0,   0));         	//  Set pixel's color (in RAM)
        strip3.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
  else if(state == 4){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip3.setPixelColor(led_column[box][i], strip3.Color(255,   120,   0));     	//  Set pixel's color (in RAM)
        strip3.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
}
////////////////////////////////////////////////////////////////////////////////
void update_column3(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip2.setPixelColor(led_column[box][i], strip2.Color(0,   0,   255));         	//  Set pixel's color (in RAM)
        strip2.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    }
  }
  else if(state == 1){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip2.setPixelColor(led_column[box][i], strip2.Color(0,   255,   0));         	//  Set pixel's color (in RAM)
        strip2.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
  else if(state == 2){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip2.setPixelColor(led_column[box][i], strip2.Color(255,   0,   0));         	//  Set pixel's color (in RAM)
        strip2.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
  else if(state == 3){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip2.setPixelColor(led_column[box][i], strip2.Color(0,   0,   0));         	//  Set pixel's color (in RAM)
        strip2.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
  else if(state == 4){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip2.setPixelColor(led_column[box][i], strip2.Color(255,   120,   0));         	//  Set pixel's color (in RAM)
        strip2.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
}
////////////////////////////////////////////////////////////////////////////////
void update_column4(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip1.setPixelColor(led_column[box][i], strip1.Color(0,   0,   255));         	//  Set pixel's color (in RAM)
        strip1.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    }
  }
  else if(state == 1){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip1.setPixelColor(led_column[box][i], strip1.Color(0,   255,   0));         	//  Set pixel's color (in RAM)
        strip1.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
  else if(state == 2){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip1.setPixelColor(led_column[box][i], strip1.Color(255,   0,   0));         	//  Set pixel's color (in RAM)
        strip1.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
  else if(state == 3){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip1.setPixelColor(led_column[box][i], strip1.Color(0,   0,   0));         	//  Set pixel's color (in RAM)
        strip1.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
  else if(state == 4){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip1.setPixelColor(led_column[box][i], strip1.Color(255,   120,   0));         	//  Set pixel's color (in RAM)
        strip1.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
}
//////////////////////////////////false//////////////////////////////////////////////////////////////////////////////////////////////
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXtrueXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX//
////////////////////////////////////////////////////////////////////////////////
void update_state(){
	//##################################################################################################################################################################
	//Update logic States for door Opening/closing || Occupied or not
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	///////////////////////////////////////////////////////////////////////////////////
		if(!digitalRead(lock1F)) {door_lock_state[0] = false;}
		else{ door_lock_state[0] = true;	}

		//Ultrasonic Controls
		digitalWrite(S0 , LOW);
		digitalWrite(S1 , LOW);
		digitalWrite(S2 , LOW);
		digitalWrite(S3 , LOW);
		//Serial.println("US-1  Selected");  
		
		distance = sonar.ping_cm();
		if(distance > 0){
			if(distance < Item_distance) food_present_state[0] = true;
			else food_present_state[0] = false;
			delay(50);
		} 
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if(!digitalRead(lock2F)) {door_lock_state[1] = false;}
		else{ door_lock_state[1] = true;	}

		//Ultrasonic controls
		digitalWrite(S0 , HIGH);
		digitalWrite(S1 , LOW);
		digitalWrite(S2 , LOW);
		digitalWrite(S3 , LOW);
		//Serial.println("US-2  Selected");  
		  
		distance = sonar.ping_cm();
		if(distance > 0){
			if(distance < Item_distance) food_present_state[1] = true;
			else food_present_state[1] = false;
			delay(50);
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if(!digitalRead(lock3F)) {door_lock_state[2] = false;}
		else{ door_lock_state[2] = true;	}

		//Ultrasonic Controls
		digitalWrite(S0 , LOW);
		digitalWrite(S1 , HIGH);
		digitalWrite(S2 , LOW);
		digitalWrite(S3 , LOW);
		//Serial.println("US-3  Selected");  
		  
		distance = sonar.ping_cm();
		if(distance > 0){
			if(distance < Item_distance) food_present_state[2] = true;
			else food_present_state[2] = false;
			delay(50);
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if(!digitalRead(lock4F)) {door_lock_state[3] = false;}
		else{ door_lock_state[3] = true;	}

		//Ultrasonic Controls
		digitalWrite(S0 , HIGH);
		digitalWrite(S1 , HIGH);
		digitalWrite(S2 , LOW);
		digitalWrite(S3 , LOW);
		//Serial.println("US-4  Selected");  
		  
		distance = sonar.ping_cm();
		if(distance > 0){
			if(distance < Item_distance) food_present_state[3] = true;
			else food_present_state[3] = false;
			delay(50);
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if(!digitalRead(lock5F)) {door_lock_state[4] = false;}
		else{ door_lock_state[4] = true;	}

		//Ultrasonic Controls
		digitalWrite(S0 , LOW);
		digitalWrite(S1 , LOW);
		digitalWrite(S2 , HIGH);
		digitalWrite(S3 , LOW);
		//Serial.println("US-5  Selected");  
		  
		distance = sonar.ping_cm();
		if(distance > 0){
			if(distance < Item_distance) food_present_state[4] = true;
			else food_present_state[4] = false;
			delay(50);
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if(!digitalRead(lock6F)) {door_lock_state[5] = false;}
		else{ door_lock_state[5] = true;	}

		//Ultrasonic Controls
		digitalWrite(S0 , HIGH);
		digitalWrite(S1 , LOW);
		digitalWrite(S2 , HIGH);
		digitalWrite(S3 , LOW);
		//Serial.println("US-6  Selected");  
		  
		distance = sonar.ping_cm();
		if(distance > 0){
			if(distance < Item_distance) food_present_state[5] = true;
			else food_present_state[5] = false;
			delay(50);
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if(!digitalRead(lock7F)) {door_lock_state[6] = false;}
		else{ door_lock_state[6] = true;	}

		//Ultrasonic Controls
		digitalWrite(S0 , LOW);
		digitalWrite(S1 , HIGH);
		digitalWrite(S2 , HIGH);
		digitalWrite(S3 , LOW);
		//Serial.println("US-7  Selected");  
		  
		distance = sonar.ping_cm();
		if(distance > 0){
			if(distance < Item_distance) food_present_state[6] = true;
			else food_present_state[6] = false;
			delay(50);
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if(!digitalRead(lock8F)) {door_lock_state[7] = false;}
		else{ door_lock_state[7] = true;	}

		//Ultrasonic Controls
		digitalWrite(S0 , HIGH);
		digitalWrite(S1 , HIGH);
		digitalWrite(S2 , HIGH);
		digitalWrite(S3 , LOW);
		//Serial.println("US-8  Selected");  
		  
		distance = sonar.ping_cm();
		if(distance > 0){
			if(distance < Item_distance) food_present_state[7] = true;
			else food_present_state[7] = false;
			delay(50);
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if(!digitalRead(lock9F)) {door_lock_state[8] = false;}
		else{ door_lock_state[8] = true;	}

		//Ultrasonic Controls
		digitalWrite(S0 , LOW);
		digitalWrite(S1 , LOW);
		digitalWrite(S2 , LOW);
		digitalWrite(S3 , HIGH);
		//Serial.println("US-9  Selected");  
		  
		distance = sonar.ping_cm();
		if(distance > 0){
			if(distance < Item_distance) food_present_state[8] = true;
			else food_present_state[8] = false;
			delay(50);
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if(!digitalRead(lock10F)) {door_lock_state[9] = false;}
		else{ door_lock_state[9] = true;	}

		//Ultrasonic Controls
		digitalWrite(S0 , HIGH);
		digitalWrite(S1 , LOW);
		digitalWrite(S2 , LOW);
		digitalWrite(S3 , HIGH);
		//Serial.println("US-10  Selected");  
		  
		distance = sonar.ping_cm();
		if(distance > 0){
			if(distance < Item_distance) food_present_state[9] = true;
			else food_present_state[9] = false;
			delay(50);
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if(!digitalRead(lock11F)) {door_lock_state[10] = false;}
		else{ door_lock_state[10] = true;	}

		//Ultrasonic Controls
		digitalWrite(S0 , LOW);
		digitalWrite(S1 , HIGH);
		digitalWrite(S2 , LOW);
		digitalWrite(S3 , HIGH);
		//Serial.println("US-11  Selected");  
		  
		distance = sonar.ping_cm();
		if(distance > 0){
			if(distance < Item_distance) food_present_state[10] = true;
			else food_present_state[10] = false;
			delay(50);
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if(!digitalRead(lock12F)) {door_lock_state[11] = false;}
		else{ door_lock_state[11] = true;	}

		//Ultrasonic Controls
		digitalWrite(S0 , HIGH);
	    digitalWrite(S1 , HIGH);	
	    digitalWrite(S2 , LOW);
	    digitalWrite(S3 , HIGH);
		//Serial.println("US-12  Selected");  
		  
		distance = sonar.ping_cm();
		if(distance > 0){
			if(distance < Item_distance) food_present_state[11] = true;
			else food_present_state[11] = false;
			delay(50);
		}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	///////////////////////////////////////////////////////////////////////////////////

	//##################################################################################################################################################################
}
////////////////////////////////////////////////////////////////////////////////
void update_web_status(){
  //##################################################################################################################################################################
  //Update logic States for door Occupied or not
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    while(1){

      Serial3.println("S");   //Start ---> request to ESP
      // Serial.println("S trigger sent");
      Serial.flush();
      if(Serial3.available()){ //Example String_data="1:1:0:0:1:0:1:1:0:0:0:0:&";
        char input[INPUT_SIZE];

        // size_t size = Serial3.readBytesUntil('&', input, INPUT_SIZE);
        String data = Serial3.readStringUntil('&');
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
          if(box_Status[i]==1) {web_door_status[i] = true;}
          else {web_door_status[i] = false;}
        }
        Serial3.println("s"); //Stop ---> request to ESP
        // Serial.println("small s triggger sent  ------------------------>");
        data_recieved = false;
        break;
      }
      // Serial3.println("Z");   //Start ---> request to ESP
      // Serial.println("Z trigger sent");    
      delay(1000);
    } 
}
////////////////////////////////////////////////////////////////////////////////
void update_led_status(){
//Update led States for door Opening/closing || Occupied or not
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if((!door_lock_state[0] && !food_present_state[0]) && !web_door_status[0]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to blue
					///////////////////////////
					update_column1(0, 0);
					///////////////////////////
			}
			if((!door_lock_state[0] && food_present_state[0]) && web_door_status[0]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to green
					///////////////////////////
					update_column1(1, 0);
					///////////////////////////
			}
			if((!door_lock_state[0] && food_present_state[0]) && !web_door_status[0]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to red
					///////////////////////////
					update_column1(2, 0);
					///////////////////////////
			}
			if((!door_lock_state[0] && !food_present_state[0]) && web_door_status[0]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to yellow
					///////////////////////////
					update_column1(4, 0);
					///////////////////////////
			}
			if(door_lock_state[0]) update_column1(3, 0);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if((!door_lock_state[1] && !food_present_state[1]) && !web_door_status[1]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to blue
					///////////////////////////
					update_column1(0, 1);
					///////////////////////////
			}
			if((!door_lock_state[1] && food_present_state[1]) && web_door_status[1]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to green
					///////////////////////////
					update_column1(1, 1);
					///////////////////////////
			}
			if((!door_lock_state[1] && food_present_state[1]) && !web_door_status[1]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to red
					///////////////////////////
					update_column1(2, 1);
					///////////////////////////
			}
			if((!door_lock_state[1] && !food_present_state[1]) && web_door_status[1]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to yellow
					///////////////////////////
					update_column1(4, 1);
					///////////////////////////
			}
			if(door_lock_state[1]) update_column1(3, 1);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if((!door_lock_state[2] && !food_present_state[2]) && !web_door_status[2]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to blue
					///////////////////////////
					update_column1(0, 2);
					///////////////////////////
			}
			if((!door_lock_state[2] && food_present_state[2]) && web_door_status[2]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to green
					///////////////////////////
					update_column1(1, 2);
					///////////////////////////
			}
			if((!door_lock_state[2] && food_present_state[2]) && !web_door_status[2]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to red
					///////////////////////////
					update_column1(2, 2);
					///////////////////////////
			}
			if((!door_lock_state[2] && !food_present_state[2]) && web_door_status[2]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to yellow
					///////////////////////////
					update_column1(4, 2);
					///////////////////////////
			}
			if(door_lock_state[2]) update_column1(3, 2);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if((!door_lock_state[3] && !food_present_state[3]) && !web_door_status[3]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to blue
					///////////////////////////
					update_column2(0, 0);
					///////////////////////////
			}
			if((!door_lock_state[3] && food_present_state[3]) && web_door_status[3]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to green
					///////////////////////////
					update_column2(1, 0);
					///////////////////////////
			}
			if((!door_lock_state[3] && food_present_state[3]) && !web_door_status[3]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to red
					///////////////////////////
					update_column2(2, 0);
					///////////////////////////
			}
			if((!door_lock_state[3] && !food_present_state[3]) && web_door_status[3]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to yellow
					///////////////////////////
					update_column2(4, 0);
					///////////////////////////
			}
			if(door_lock_state[3]) update_column2(3, 0);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if((!door_lock_state[4] && !food_present_state[4]) && !web_door_status[4]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to blue
					///////////////////////////
					update_column2(0, 1);
					///////////////////////////
			}
			if((!door_lock_state[4] && food_present_state[4]) && web_door_status[4]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to green
					///////////////////////////
					update_column2(1, 1);
					///////////////////////////
			}
			if((!door_lock_state[4] && food_present_state[4]) && !web_door_status[4]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to red
					///////////////////////////
					update_column2(2, 1);
					///////////////////////////
			}
			if((!door_lock_state[4] && !food_present_state[4]) && web_door_status[4]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to yellow
					///////////////////////////
					update_column2(4, 1);
					///////////////////////////
			}
			if(door_lock_state[4]) update_column2(3, 1);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if((!door_lock_state[5] && !food_present_state[5]) && !web_door_status[5]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to blue
					///////////////////////////
					update_column2(0, 2);
					///////////////////////////
			}
			if((!door_lock_state[5] && food_present_state[5]) && web_door_status[5]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to green
					///////////////////////////
					update_column2(1, 2);
					///////////////////////////
			}
			if((!door_lock_state[5] && food_present_state[5]) && !web_door_status[5]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to red
					///////////////////////////
					update_column2(2, 2);
					///////////////////////////
			}
			if((!door_lock_state[5] && !food_present_state[5]) && web_door_status[5]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to yellow
					///////////////////////////
					update_column2(4, 2);
					///////////////////////////
			}
			if(door_lock_state[5]) update_column2(3, 2);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if((!door_lock_state[6] && !food_present_state[6]) && !web_door_status[6]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to blue
					///////////////////////////
					update_column3(0, 0);
					///////////////////////////
			}
			if((!door_lock_state[6] && food_present_state[6]) && web_door_status[6]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to green
					///////////////////////////
					update_column3(1, 0);
					///////////////////////////
			}
			if((!door_lock_state[6] && food_present_state[6]) && !web_door_status[6]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to red
					///////////////////////////
					update_column3(2, 0);
					///////////////////////////
			}
			if((!door_lock_state[6] && !food_present_state[6]) && web_door_status[6]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to yellow
					///////////////////////////
					update_column3(4, 0);
					///////////////////////////
			}
			if(door_lock_state[6]) update_column3(3, 0);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if((!door_lock_state[7] && !food_present_state[7]) && !web_door_status[7]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to blue
					///////////////////////////
					update_column3(0, 1);
					///////////////////////////
			}
			if((!door_lock_state[7] && food_present_state[7]) && web_door_status[7]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to green
					///////////////////////////
					update_column3(1, 1);
					///////////////////////////
			}
			if((!door_lock_state[7] && food_present_state[7]) && !web_door_status[7]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to red
					///////////////////////////
					update_column3(2, 1);
					///////////////////////////
			}
			if((!door_lock_state[7] && !food_present_state[7]) && web_door_status[7]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to yellow
					///////////////////////////
					update_column3(4, 1);
					///////////////////////////
			}
			if(door_lock_state[7]) update_column3(3, 1);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if((!door_lock_state[8] && !food_present_state[8]) && !web_door_status[8]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to blue
					///////////////////////////
					update_column3(0, 2);
					///////////////////////////
			}
			if((!door_lock_state[8] && food_present_state[8]) && web_door_status[8]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to green
					///////////////////////////
					update_column3(1, 2);
					///////////////////////////
			}
			if((!door_lock_state[8] && food_present_state[8]) && !web_door_status[8]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to red
					///////////////////////////
					update_column3(2, 2);
					///////////////////////////
			}
			if((!door_lock_state[8] && !food_present_state[8]) && web_door_status[8]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to yellow
					///////////////////////////
					update_column3(4, 2);
					///////////////////////////
			}
			if(door_lock_state[8]) update_column3(3, 2);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if((!door_lock_state[9] && !food_present_state[9]) && !web_door_status[9]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to blue
					///////////////////////////
					update_column4(0, 0);
					///////////////////////////
			}
			if((!door_lock_state[9] && food_present_state[9]) && web_door_status[9]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to green
					///////////////////////////
					update_column4(1, 0);
					///////////////////////////
			}
			if((!door_lock_state[9] && food_present_state[9]) && !web_door_status[9]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to red
					///////////////////////////
					update_column4(2, 0);
					///////////////////////////
			}
			if((!door_lock_state[9] && !food_present_state[9]) && web_door_status[9]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to yellow
					///////////////////////////
					update_column4(4, 0);
					///////////////////////////
			}
			if(door_lock_state[9]) update_column4(3, 0);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if((!door_lock_state[10] && !food_present_state[10]) && !web_door_status[10]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to blue
					///////////////////////////
					update_column4(0, 1);
					///////////////////////////
			}
			if((!door_lock_state[10] && food_present_state[10]) && web_door_status[10]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to green
					///////////////////////////
					update_column4(1, 1);
					///////////////////////////
			}
			if((!door_lock_state[10] && food_present_state[10]) && !web_door_status[10]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to red
					///////////////////////////
					update_column4(2, 1);
					///////////////////////////
			}
			if((!door_lock_state[10] && !food_present_state[10]) && web_door_status[10]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to yellow
					///////////////////////////
					update_column4(4, 1);
					///////////////////////////
			}
			if(door_lock_state[10]) update_column4(3, 1);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if((!door_lock_state[11] && !food_present_state[11]) && !web_door_status[11]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to blue
					///////////////////////////
					update_column4(0, 2);
					///////////////////////////
			}
			if((!door_lock_state[11] && food_present_state[11]) && web_door_status[11]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to green
					///////////////////////////
					update_column4(1, 2);
					///////////////////////////
			}
			if((!door_lock_state[11] && food_present_state[11]) && !web_door_status[11]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to red
					///////////////////////////
					update_column4(2, 2);
					///////////////////////////
			}
			if((!door_lock_state[11] && !food_present_state[11]) && web_door_status[11]) // false: door closed | No food Present | Locker not occupied on the Web
			{
				///////////////////////////
					//update LED color to yellow
					///////////////////////////
					update_column4(4, 2);
					///////////////////////////
			}
			if(door_lock_state[11]) update_column4(3, 2);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	///////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////
/* Ultrasonic Channel Selection guide

	S0 S1 S2 S3 E Channel
	X  X  X  X  1 None
	0  0  0  0  0 0
	1  0  0  0  0 1
	0  1  0  0  0 2
	1  1  0  0  0 3
	0  0  1  0  0 4
	1  0  1  0  0 5
	0  1  1  0  0 6
	1  1  1  0  0 7
	0  0  0  1  0 8
	1  0  0  1  0 9
	0  1  0  1  0 10
	1  1  0  1  0 11
	0  0  1  1  0 12
	1  0  1  1  0 13
	0  1  1  1  0 14
	1  1  1  1  0 15
*///////////////////////////////////////////////////
// Lock-open(1) closed(0)
// Temperature default 1 : above threshold 0
// U.S: W/o >30 W<30

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX//