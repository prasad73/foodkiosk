//////////////////////////////////////////////////////////////////////////////////////
//INPUT DATA
/*
void setup(){
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);	
	pinMode(1, INPUT); //tX
	pinMode(3, INPUT); //RX
}

void loop(){
	if(digitalRead(1)&& !digitalRead(3)) digitalWrite(2, LOW); //ON
	else if(!digitalRead(1)&& digitalRead(3)) digitalWrite(2, HIGH); //OFF
}
*/
//////////////////////////////////////////////////////////////////////////////////////
//OUTPUT DATA

void setup(){
	pinMode(1, OUTPUT); //tX
	pinMode(3, OUTPUT); //RX
}

void loop(){
	digitalWrite(1, HIGH);
	digitalWrite(3, LOW);

	delay(3000);

	digitalWrite(3, HIGH);
	digitalWrite(1, LOW);

	delay(3000);	
}

//////////////////////////////////////////////////////////////////////////////////////