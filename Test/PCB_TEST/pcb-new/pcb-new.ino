#include <Adafruit_NeoPixel.h>
#define LED_PIN  21 //SCL
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
//#define Lock11 16
//#define Lock12 17

bool R_state = false;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int Locks[] = {Lock1,Lock2,Lock3,Lock4,Lock5,Lock6,Lock7,Lock8,Lock9,Lock10};
int No_of_locks = 10;

void setup(){
	for(int i=0; i<No_of_locks;i++){
		pinMode(Locks[i],OUTPUT);
		digitalWrite(Locks[i], LOW);
	}

	Serial.begin(115200);

	Serial.println("Food Kiosk PCB Test V1.1");
	Serial.println("--------------------------");
	Serial.println("Press 1: open Lock1");
	Serial.println("Press 2: open Lock2");
	Serial.println("Press 3: open Lock3");
	Serial.println("Press 4: open Lock4");
	Serial.println("Press 5: open Lock5");
	Serial.println("Press 6: open Lock6");
	Serial.println("Press 7: open Lock7");
	Serial.println("Press 8: open Lock8");
	Serial.println("Press 9: open Lock9");
	Serial.println("Press A: open Lock10");
	Serial.println("Press B: open Lock11");
	Serial.println("Press C: open Lock12");
	Serial.println("Press D: Toggle RED Led");
	Serial.println("Press E: Turn OFF all LED's");
	Serial.println("Press F: Turn ON all LED's");

	strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    strip.show();            // Turn OFF all pixels ASAP
    strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop(){
	if(Serial.available()){
		char data= Serial.read();
		if(data == 'D') { 
			if(R_state)  
				colorWipe(strip.Color(255,   0,   0), 5); // Red
			else
				colorWipe(strip.Color(0,   0,   0), 1); // off
			R_state = !R_state;
		}
		else if(data == 'E') { colorWipe(strip.Color(0,   0,   0), 1);} // off
		else if(data == 'F') { colorWipe(strip.Color(255,   255,   255), 1);} // off
		else if(data == '1'){
				digitalWrite(Locks[0] , HIGH);
				delay(500);
				digitalWrite(Locks[0] , LOW);

		}
		else if(data == '2'){
				digitalWrite(Locks[1] , HIGH);
				delay(500);
				digitalWrite(Locks[1] , LOW);
		}		
		else if(data == '3'){
				digitalWrite(Locks[2] , HIGH);
				delay(500);
				digitalWrite(Locks[2] , LOW);

		}
		else if(data == '4'){
				digitalWrite(Locks[3] , HIGH);
				delay(500);
				digitalWrite(Locks[3] , LOW);
		}			
		else if(data == '5'){
				digitalWrite(Locks[4] , HIGH);
				delay(500);
				digitalWrite(Locks[4] , LOW);

		}
		else if(data == '6'){
				digitalWrite(Locks[5] , HIGH);
				delay(500);
				digitalWrite(Locks[5] , LOW);
		}		
		else if(data == '7'){
				digitalWrite(Locks[6] , HIGH);
				delay(500);
				digitalWrite(Locks[6] , LOW);

		}
		else if(data == '8'){
				digitalWrite(Locks[7] , HIGH);
				delay(500);
				digitalWrite(Locks[7] , LOW);
		}	
		else if(data == '9'){
				digitalWrite(Locks[8] , HIGH);
				delay(500);
				digitalWrite(Locks[8] , LOW);

		}
		else if(data == 'A'){
				digitalWrite(Locks[9] , HIGH);
				delay(500);
				digitalWrite(Locks[9] , LOW);
		}		
		// else if(data == 'B'){
		// 		digitalWrite(Locks[10] , HIGH);
		// 		delay(500);
		// 		digitalWrite(Locks[10] , LOW);

		// }
		// else if(data == 'C'){
		// 		digitalWrite(Locks[11] , HIGH);
		// 		delay(500);
		// 		digitalWrite(Locks[11] , LOW);
		// }					
	}	
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}