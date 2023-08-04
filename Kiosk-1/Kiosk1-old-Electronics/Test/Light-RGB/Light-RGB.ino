#define R 21
#define G 19
#define B 18

int R_STATE = 1;
int G_STATE = 1;
int B_STATE = 1;

void setup(){
	pinMode(R, OUTPUT);
	pinMode(G, OUTPUT);
	pinMode(B, OUTPUT);

	digitalWrite(R, HIGH);
	digitalWrite(G, HIGH);
	digitalWrite(B, HIGH);

	Serial.begin(115200);

	Serial.println("RGB LED Control V1.0");
	Serial.println("--------------------------");
	Serial.println("Press 1: Toggle RED Led");
	Serial.println("Press 2: Toggle GREEN Led");
	Serial.println("Press 3: Toggle BLUE Led");
	Serial.println("Press 4: Turn OFF all LED's");
}

void loop(){

	if(Serial.available()){
		char data= Serial.read();
		if(data == '1') { R_STATE = !R_STATE; digitalWrite(R, R_STATE);}
		else if(data == '2') { G_STATE = !G_STATE; digitalWrite(G, G_STATE);}
		else if(data == '3') { B_STATE = !B_STATE; digitalWrite(B, B_STATE);}
		else if(data == '4'){
				digitalWrite(R, HIGH);
				digitalWrite(G, HIGH);
				digitalWrite(B, HIGH);	
				R_STATE = 1; G_STATE = 1; B_STATE = 1;		
		}
	}
	
}