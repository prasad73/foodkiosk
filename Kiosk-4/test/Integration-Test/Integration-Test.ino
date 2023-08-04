////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <NewPing.h>            // Ultrasonic Sensor library
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////Light Control pins & it's libraries//////////////////////////////////////////////////////////////////////////////
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>         // Required for 16 MHz Adafruit Trinket
#endif
//////////////////////////////////
//////LED Control pins////////////
// #define LED_PIN_2    21
// #define LED_PIN_3    20
// #define LED_PIN_1    13
#define LED_PIN_4    51
//////////////////////////////////
#define LED_COUNT_1 60          // Total No. of LED's
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
#define buzzer 53                // Buzzer feedback
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define drive_time 1200          // Relay drive time
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TRIGGER_PIN  52          // Trigger pin on the ultrasonic sensor.
#define ECHO_PIN     52          // Echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400         // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define EN 50                    // Enable pin for MUX
#define S0 A0                    // Selection pin for MUX
#define S1 A1                    // Selection pin for MUX
#define S2 A2                    // Selection pin for MUX
#define S3 A3                    // Selection pin for MUX

////////////////////////////////////////////////////
/* Channel Selection guide


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

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declare our NeoPixel strip object:
// Adafruit_NeoPixel strip1(LED_COUNT_1, LED_PIN_1, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel strip2(LED_COUNT_1, LED_PIN_2, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel strip3(LED_COUNT_1, LED_PIN_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4(LED_COUNT_1, LED_PIN_4, NEO_GRB + NEO_KHZ800);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////LED arrangmenet MAP in Column//////////////////////////////////////////////////////////////////////////////////////
// int led_column[3][5]={{0,1,2,3,4},{5,6,7,8,9},{10,11,12,13,14}};
 int led_column[12][5]={{0,1,2,3,4},{5,6,7,8,9},{10,11,12,13,14},{15,16,17,18,19},{20,21,22,23,24},{25,26,27,28,29},{30,31,32,33,34},{35,36,37,38,39},{40,41,42,43,44},{45,46,47,48,49},{50,51,52,53,54},{55,56,57,58,59}};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int box_number = 0;            //Used for ultrasonic sensor
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(){
	Serial.begin(115200);
	Serial.println("Kiosk2 Integrated code test ");

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

	pinMode(buzzer, OUTPUT);
	digitalWrite(buzzer, LOW);      //Turn off Buzzer

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

		// strip1.begin();               	// INITIALIZE NeoPixel strip object (REQUIRED)
		// strip1.show();                	// Turn OFF all pixels ASAP
    // strip1.setBrightness(255);    	// Set BRIGHTNESS to about 1/5 (max = 255)

    // strip2.begin();           	  	// INITIALIZE NeoPixel strip object (REQUIRED)
    // strip2.show();            		// Turn OFF all pixels ASAP
    // strip2.setBrightness(255); 		// Set BRIGHTNESS to about 1/5 (max = 255)

    // strip3.begin();           		// INITIALIZE NeoPixel strip object (REQUIRED)
    // strip3.show();            		// Turn OFF all pixels ASAP
    // strip3.setBrightness(255); 		// Set BRIGHTNESS to about 1/5 (max = 255)

    strip4.begin();           		// INITIALIZE NeoPixel strip object (REQUIRED)
    strip4.show();            		// Turn OFF all pixels ASAP
    strip4.setBrightness(255); 		// Set BRIGHTNESS to about 1/5 (max = 255)
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop(){
	if(Serial.available()){
		char command = Serial.read();
		
		// LED Status update command
		// update_column1(0, 0);update_column1(1, 0);update_column1(0, 1);update_column1(1, 1);update_column1(0, 2);update_column1(1, 2);
		// update_column1(State-0/1, box-0/1/2);

		if(command == '1'){
			digitalWrite(lock1, HIGH);
			Serial.println("Lock1 Unlcoked");
			delay(drive_time);
			digitalWrite(lock1, LOW);

			update_led(1,0);
			update_led(0,1);
			update_led(0,2);
			update_led(0,3);
			update_led(0,4);
			update_led(0,5);
			update_led(0,6);
			update_led(0,7);
			update_led(0,8);
			update_led(0,9);
			update_led(0,10);
			update_led(0,11);

			digitalWrite(S0 , LOW);
	    digitalWrite(S1 , LOW);
	    digitalWrite(S2 , LOW);
	    digitalWrite(S3 , LOW);
	    Serial.println("Sensor-1  Selected");  
	    box_number = 1;
		}
		else if(command == '2'){
			digitalWrite(lock2, HIGH);
			Serial.println("Lock2 Unlcoked");
			delay(drive_time);
			digitalWrite(lock2, LOW);

			update_led(0,0);
			update_led(1,1);
			update_led(0,2);
			update_led(0,3);
			update_led(0,4);
			update_led(0,5);
			update_led(0,6);
			update_led(0,7);
			update_led(0,8);
			update_led(0,9);
			update_led(0,10);
			update_led(0,11);

			digitalWrite(S0 , HIGH);
	    digitalWrite(S1 , LOW);
	    digitalWrite(S2 , LOW);
	    digitalWrite(S3 , LOW);
	    Serial.println("Sensor-2  Selected");  
	    box_number = 2;
		}
		else if(command == '3'){
			digitalWrite(lock3, HIGH);
			Serial.println("Lock3 Unlcoked");
			delay(drive_time);
			digitalWrite(lock3, LOW);

			update_led(0,0);
			update_led(0,1);
			update_led(1,2);
			update_led(0,3);
			update_led(0,4);
			update_led(0,5);
			update_led(0,6);
			update_led(0,7);
			update_led(0,8);
			update_led(0,9);
			update_led(0,10);
			update_led(0,11);

			digitalWrite(S0 , LOW);
	    digitalWrite(S1 , HIGH);
	    digitalWrite(S2 , LOW);
	    digitalWrite(S3 , LOW);
	    Serial.println("Sensor-3  Selected");  
	    box_number = 3;
		}
		else if(command == '4'){
			digitalWrite(lock4, HIGH);
			Serial.println("Lock4 Unlcoked");
			delay(drive_time);
			digitalWrite(lock4, LOW);

			update_led(0,0);
			update_led(0,1);
			update_led(0,2);
			update_led(0,3);
			update_led(1,4);
			update_led(0,5);
			update_led(0,6);
			update_led(0,7);
			update_led(0,8);
			update_led(0,9);
			update_led(0,10);
			update_led(0,11);

			digitalWrite(S0 , HIGH);
	    digitalWrite(S1 , HIGH);
	    digitalWrite(S2 , LOW);
	    digitalWrite(S3 , LOW);
	    Serial.println("Sensor-4  Selected");  
	    box_number = 4;
		}
		else if(command == '5'){
			digitalWrite(lock5, HIGH);
			Serial.println("Lock5 Unlcoked");
			delay(drive_time);
			digitalWrite(lock5, LOW);

			digitalWrite(S0 , LOW);
	    digitalWrite(S1 , LOW);
	    digitalWrite(S2 , HIGH);
	    digitalWrite(S3 , LOW);
	    Serial.println("Sensor-5  Selected");  
	    box_number = 5;
		}
		else if(command == '6'){
			digitalWrite(lock6, HIGH);
			Serial.println("Lock6 Unlcoked");
			delay(drive_time);
			digitalWrite(lock6, LOW);

			update_led(0,0);
			update_led(0,1);
			update_led(0,2);
			update_led(0,3);
			update_led(0,4);
			update_led(1,5);
			update_led(0,6);
			update_led(0,7);
			update_led(0,8);
			update_led(0,9);
			update_led(0,10);
			update_led(0,11);

			digitalWrite(S0 , HIGH);
	    digitalWrite(S1 , LOW);
	    digitalWrite(S2 , HIGH);
	    digitalWrite(S3 , LOW);
	    Serial.println("Sensor-6  Selected");  
	    box_number = 6;
		}
		else if(command == '7'){
			digitalWrite(lock7, HIGH);
			Serial.println("Lock7 Unlcoked");
			delay(drive_time);
			digitalWrite(lock7, LOW);

			update_led(0,0);
			update_led(0,1);
			update_led(0,2);
			update_led(0,3);
			update_led(0,4);
			update_led(0,5);
			update_led(1,6);
			update_led(0,7);
			update_led(0,8);
			update_led(0,9);
			update_led(0,10);
			update_led(0,11);

			digitalWrite(S0 , LOW);
	    digitalWrite(S1 , HIGH);
	    digitalWrite(S2 , HIGH);
	    digitalWrite(S3 , LOW);
	    Serial.println("Sensor-7  Selected");  
	    box_number = 7;
		}
		else if(command == '8'){
			digitalWrite(lock8, HIGH);
			Serial.println("Lock8 Unlcoked");
			delay(drive_time);
			digitalWrite(lock8, LOW);

			update_led(0,0);
			update_led(0,1);
			update_led(0,2);
			update_led(0,3);
			update_led(0,4);
			update_led(0,5);
			update_led(0,6);
			update_led(1,7);
			update_led(0,8);
			update_led(0,9);
			update_led(0,10);
			update_led(0,11);

			digitalWrite(S0 , HIGH);
	    digitalWrite(S1 , HIGH);
	    digitalWrite(S2 , HIGH);
	    digitalWrite(S3 , LOW);
	    Serial.println("Sensor-8  Selected");  
	    box_number = 8;
		}
		else if(command == '9'){
			digitalWrite(lock9, HIGH);
			Serial.println("Lock9 Unlcoked");
			delay(drive_time);
			digitalWrite(lock9, LOW);

			update_led(0,0);
			update_led(0,1);
			update_led(0,2);
			update_led(0,3);
			update_led(0,4);
			update_led(0,5);
			update_led(0,6);
			update_led(0,7);
			update_led(1,8);
			update_led(0,9);
			update_led(0,10);
			update_led(0,11);

			digitalWrite(S0 , LOW);
	    digitalWrite(S1 , LOW);
	    digitalWrite(S2 , LOW);
	    digitalWrite(S3 , HIGH);
	    Serial.println("Sensor-9  Selected");  
	    box_number = 9;
		}
		else if(command == 'A'){
			digitalWrite(lock10, HIGH);
			Serial.println("Lock10 Unlcoked");
			delay(drive_time);
			digitalWrite(lock10, LOW);

			update_led(0,0);
			update_led(0,1);
			update_led(0,2);
			update_led(0,3);
			update_led(0,4);
			update_led(0,5);
			update_led(0,6);
			update_led(0,7);
			update_led(0,8);
			update_led(1,9);
			update_led(0,10);
			update_led(0,11);

			digitalWrite(S0 , HIGH);
	    digitalWrite(S1 , LOW);
	    digitalWrite(S2 , LOW);
	    digitalWrite(S3 , HIGH);
	    Serial.println("Sensor-10  Selected");  
	    box_number = 10;
		}
		else if(command == 'B'){
			digitalWrite(lock11, HIGH);
			Serial.println("Lock11 Unlcoked");
			delay(drive_time);
			digitalWrite(lock11, LOW);

			update_led(0,0);
			update_led(0,1);
			update_led(0,2);
			update_led(0,3);
			update_led(0,4);
			update_led(0,5);
			update_led(0,6);
			update_led(0,7);
			update_led(0,8);
			update_led(0,9);
			update_led(1,10);
			update_led(0,11);

			digitalWrite(S0 , LOW);
	    digitalWrite(S1 , HIGH);
	    digitalWrite(S2 , LOW);
	    digitalWrite(S3 , HIGH);
	    Serial.println("Sensor-11  Selected");  
	    box_number = 11;
		}else if(command == 'C'){
			digitalWrite(lock12, HIGH);
			Serial.println("Lock12 Unlcoked");
			delay(drive_time);
			digitalWrite(lock12, LOW);

			update_led(0,0);
			update_led(0,1);
			update_led(0,2);
			update_led(0,3);
			update_led(0,4);
			update_led(0,5);
			update_led(0,6);
			update_led(0,7);
			update_led(0,8);
			update_led(0,9);
			update_led(0,10);
			update_led(1,11);

			digitalWrite(S0 , HIGH);
      digitalWrite(S1 , HIGH);	
      digitalWrite(S2 , LOW);
      digitalWrite(S3 , HIGH);
      Serial.println("Sensor-12  Selected");  
      box_number = 12;
		}
	}

	Serial.print("LOCK Status: ");
	Serial.print(digitalRead(lock1F));
	Serial.print(":");
	Serial.print(digitalRead(lock2F));
	Serial.print(":");
	Serial.print(digitalRead(lock3F));
	Serial.print(":");
	Serial.print(digitalRead(lock4F));
	Serial.print(":");
	Serial.print(digitalRead(lock5F));
	Serial.print(":");
	Serial.print(digitalRead(lock6F));
	Serial.print(":");
	Serial.print(digitalRead(lock7F));
	Serial.print(":");
	Serial.print(digitalRead(lock8F));
	Serial.print(":");
	Serial.print(digitalRead(lock9F));
	Serial.print(":");
	Serial.print(digitalRead(lock10F));
	Serial.print(":");
	Serial.print(digitalRead(lock11F));
	Serial.print(":");
	Serial.println(digitalRead(lock12F));

	Serial.print("Temperature Status: ");
	Serial.print(digitalRead(TF1));
	Serial.print(":");
	Serial.print(digitalRead(TF2));
	Serial.print(":");
	Serial.print(digitalRead(TF3));
	Serial.print(":");
	Serial.print(digitalRead(TF4));
	Serial.print(":");
	Serial.print(digitalRead(TF5));
	Serial.print(":");
	Serial.print(digitalRead(TF6));
	Serial.print(":");
	Serial.print(digitalRead(TF7));
	Serial.print(":");
	Serial.print(digitalRead(TF8));
	Serial.print(":");
	Serial.print(digitalRead(TF9));
	Serial.print(":");
	Serial.print(digitalRead(TF10));
	Serial.print(":");
	Serial.print(digitalRead(TF11));
	Serial.print(":");
	Serial.println(digitalRead(TF12));

	Serial.print(box_number);
	Serial.print(" : ");
  	Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  	Serial.println("cm");
	delay(1000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////LED Control Function's/////////////////////////////////////////////////////////////////////////////////////
/*
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
}
*/
////////////////////////////////////////////////////////////////////////////////
void update_led(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(0,   0,   255));         	//  Set pixel's color (in RAM)
        strip4.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    }
  }
  else if(state == 1){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(0,   255,   0));         	//  Set pixel's color (in RAM)
        strip4.show();                          										//  Update strip to match
        delay(1);                              											//  Pause for a moment
    } 
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////