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
#define Lock2 17
#define Lock3 16

// #define FeedBack 23

int R1_STATE = 0;
int G1_STATE = 0;
int B1_STATE = 0;

int R2_STATE = 0;
int G2_STATE = 0;
int B2_STATE = 0;

int R3_STATE = 0;
int G3_STATE = 0;
int B3_STATE = 0;

void setup(){
	pinMode(R1, OUTPUT);
	pinMode(G1, OUTPUT);
	pinMode(B1, OUTPUT);
	pinMode(Lock1, OUTPUT);

	pinMode(R2, OUTPUT);
	pinMode(G2, OUTPUT);
	pinMode(B2, OUTPUT);
	pinMode(Lock2, OUTPUT);
	
	pinMode(R3, OUTPUT);
	pinMode(G3, OUTPUT);
	pinMode(B3, OUTPUT);
	pinMode(Lock3, OUTPUT);

	// pinMode(FeedBack, INPUT);

	digitalWrite(R1, LOW);
	digitalWrite(G1, LOW);
	digitalWrite(B1, LOW);
	digitalWrite(Lock1, LOW);

	digitalWrite(R2, LOW);
	digitalWrite(G2, LOW);
	digitalWrite(B2, LOW);
	digitalWrite(Lock2, LOW);

	digitalWrite(R3, LOW);
	digitalWrite(G3, LOW);
	digitalWrite(B3, LOW);
	digitalWrite(Lock3, LOW);

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

/*
	if(Serial.available()){
		char data= Serial.read();
		if(data == '1') { R1_STATE = !R1_STATE; digitalWrite(R1, R1_STATE);R2_STATE = !R2_STATE; digitalWrite(R2, R2_STATE);R3_STATE = !R3_STATE; digitalWrite(R3, R3_STATE);}
		else if(data == '2') { G1_STATE = !G1_STATE; digitalWrite(G1, G1_STATE);G2_STATE = !G2_STATE; digitalWrite(G2, G2_STATE);G3_STATE = !G3_STATE; digitalWrite(G3, G3_STATE);}
		else if(data == '3') { B1_STATE = !B1_STATE; digitalWrite(B1, B1_STATE); B2_STATE = !B2_STATE; digitalWrite(B2, B2_STATE); B3_STATE = !B3_STATE; digitalWrite(B3, B3_STATE);}
		else if(data == '4'){
				digitalWrite(R1, LOW);digitalWrite(R2, LOW);digitalWrite(R3, LOW);
				digitalWrite(G1, LOW);digitalWrite(G2, LOW);digitalWrite(G3, LOW);
				digitalWrite(B1, LOW);digitalWrite(B2, LOW);digitalWrite(B3, LOW);			
				R1_STATE = 0; G1_STATE = 0; B1_STATE = 0;		
				R2_STATE = 0; G2_STATE = 0; B2_STATE = 0;		
				R3_STATE = 0; G3_STATE = 0; B3_STATE = 0;		
		}
		else if(data == '6'){
				digitalWrite(Lock1 , HIGH);
				digitalWrite(Lock2 , HIGH);
				digitalWrite(Lock3 , HIGH);
				delay(200);
				digitalWrite(Lock1 , LOW);
				digitalWrite(Lock2 , LOW);
				digitalWrite(Lock3 , LOW);

		}
		else if(data == '5'){
				digitalWrite(R1, 1);
				digitalWrite(G1, 1);
				digitalWrite(B1, 1);	

				digitalWrite(R2, 1);
				digitalWrite(G2, 1);
				digitalWrite(B2, 1);	

				digitalWrite(R3, 1);
				digitalWrite(G3, 1);
				digitalWrite(B3, 1);	
				R1_STATE = 1; G1_STATE = 1; B1_STATE = 1;		
				R2_STATE = 1; G2_STATE = 1; B2_STATE = 1;		
				R3_STATE = 1; G3_STATE = 1; B3_STATE = 1;		
		}
				
	}

*/


		// { R1_STATE = !R1_STATE; digitalWrite(R1, R1_STATE);R2_STATE = !R2_STATE; digitalWrite(R2, R2_STATE);R3_STATE = !R3_STATE; digitalWrite(R3, R3_STATE);}
		// delay(3000);
		// TurnoffAllLed();
		// delay(2000);
		// { G1_STATE = !G1_STATE; digitalWrite(G1, G1_STATE);G2_STATE = !G2_STATE; digitalWrite(G2, G2_STATE);G3_STATE = !G3_STATE; digitalWrite(G3, G3_STATE);}
		// delay(3000);
		// TurnoffAllLed();
		// delay(2000);
		// { B1_STATE = !B1_STATE; digitalWrite(B1, B1_STATE); B2_STATE = !B2_STATE; digitalWrite(B2, B2_STATE); B3_STATE = !B3_STATE; digitalWrite(B3, B3_STATE);}
		// delay(3000);
		{ 
			B1_STATE = !B1_STATE; digitalWrite(B1, B1_STATE);
			G1_STATE = !G1_STATE; digitalWrite(G1, G1_STATE);

			B2_STATE = !B2_STATE; digitalWrite(B2, B2_STATE);
			G2_STATE = !G2_STATE; digitalWrite(G2, G2_STATE);

			B3_STATE = !B3_STATE; digitalWrite(B3, R3_STATE);
			G3_STATE = !G3_STATE; digitalWrite(G3, G3_STATE);
		}
		delay(1500);	
		TurnoffAllLed();
		delay(2000);
		{
				digitalWrite(Lock1 , HIGH);
				// digitalWrite(Lock2 , HIGH);
				// digitalWrite(Lock3 , HIGH);
				delay(1500);
				digitalWrite(Lock1 , LOW);
				// digitalWrite(Lock2 , LOW);
				// digitalWrite(Lock3 , LOW);

		}
		// TurnonAllLed();
		// delay(2000);
		// TurnoffAllLed();
		// delay(1000);
		delay(10000);
	
}

void TurnoffAllLed(){
	{
				digitalWrite(R1, LOW);digitalWrite(R2, LOW);digitalWrite(R3, LOW);
				digitalWrite(G1, LOW);digitalWrite(G2, LOW);digitalWrite(G3, LOW);
				digitalWrite(B1, LOW);digitalWrite(B2, LOW);digitalWrite(B3, LOW);			
				R1_STATE = 0; G1_STATE = 0; B1_STATE = 0;		
				R2_STATE = 0; G2_STATE = 0; B2_STATE = 0;		
				R3_STATE = 0; G3_STATE = 0; B3_STATE = 0;		
	}
}

void TurnonAllLed(){
	{
				digitalWrite(R1, 1);
				digitalWrite(G1, 1);
				digitalWrite(B1, 1);	

				digitalWrite(R2, 1);
				digitalWrite(G2, 1);
				digitalWrite(B2, 1);	

				digitalWrite(R3, 1);
				digitalWrite(G3, 1);
				digitalWrite(B3, 1);	
				R1_STATE = 1; G1_STATE = 1; B1_STATE = 1;		
				R2_STATE = 1; G2_STATE = 1; B2_STATE = 1;		
				R3_STATE = 1; G3_STATE = 1; B3_STATE = 1;		
		}
}