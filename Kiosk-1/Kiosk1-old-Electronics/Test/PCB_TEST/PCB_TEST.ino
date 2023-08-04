#define R 21
#define G 19
#define B 18

#define Lock 22
// #define FeedBack 23

int R_STATE = 0;
int G_STATE = 0;
int B_STATE = 0;

void setup(){
	pinMode(R, OUTPUT);
	pinMode(G, OUTPUT);
	pinMode(B, OUTPUT);
	pinMode(Lock, OUTPUT);
	// pinMode(FeedBack, INPUT);

	digitalWrite(R, LOW);
	digitalWrite(G, LOW);
	digitalWrite(B, LOW);
	digitalWrite(Lock, LOW);

	Serial.begin(115200);

	Serial.println("Food Kiosk PCB Test V1.0");
	Serial.println("--------------------------");
	Serial.println("Press 1: Toggle BLUE Led");
	Serial.println("Press 2: Toggle GREEN Led");
	Serial.println("Press 3: Toggle RED Led");
	Serial.println("Press 4: Turn OFF all LED's");
	Serial.println("Press 5: Turn ON all LED's");
	Serial.println("Press 6: Door Unlock!!!!!");

}

void loop(){

	// Serial.print("Door FeedBack :");
	// if(!(digitalRead(FeedBack))) Serial.println(" LOCKED");
	// else Serial.println(" OPEN");

	if(Serial.available()){
		char data= Serial.read();
		if(data == '1') { R_STATE = !R_STATE; digitalWrite(R, R_STATE);}
		else if(data == '2') { G_STATE = !G_STATE; digitalWrite(G, G_STATE);}
		else if(data == '3') { B_STATE = !B_STATE; digitalWrite(B, B_STATE);}
		else if(data == '4'){
				digitalWrite(R, LOW);
				digitalWrite(G, LOW);
				digitalWrite(B, LOW);	
				R_STATE = 0; G_STATE = 0; B_STATE = 0;		
		}
		else if(data == '6'){
				digitalWrite(Lock , HIGH);
				delay(100);
				digitalWrite(Lock , LOW);

		}
		else if(data == '5'){
				digitalWrite(R, 1);
				digitalWrite(G, 1);
				digitalWrite(B, 1);	
				R_STATE = 1; G_STATE = 1; B_STATE = 1;		
		}
				
	}

	// delay(1000);
	
}