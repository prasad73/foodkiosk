//////////////////////////////////////////////////////////////////////////////////////
//OUTPUT
/*
void setup(){
	Serial.begin(9600);
		
	pinMode(18, OUTPUT); //tX
	pinMode(19, OUTPUT); //RX

	digitalWrite(18 , LOW);
	digitalWrite(19, LOW);
	Serial.println("Initialized.....");
}

void loop(){
	if(Serial.available()){
		char command = Serial.read();
		if(command == 'a') {
			Serial.println("a sent");
			digitalWrite(18 , LOW);
			digitalWrite(19, HIGH);
		}
		else if(command == 'b') {
			Serial.println("b sent");
			digitalWrite(18 , HIGH);
			digitalWrite(19, LOW);
		}
	}
}
*/
//////////////////////////////////////////////////////////////////////////////////////
//INPUT
void setup(){
	Serial.begin(9600);
		
	pinMode(25, INPUT_PULLUP); //tX
	pinMode(24, INPUT_PULLUP); //RX

	Serial.println("Initialized.....");
}

void loop(){
		if(digitalRead(25) && !digitalRead(24)){
			Serial.println("a");
		}
		else if(!digitalRead(25) && digitalRead(24)){
			Serial.println("b");
		}
}
//////////////////////////////////////////////////////////////////////////////////////