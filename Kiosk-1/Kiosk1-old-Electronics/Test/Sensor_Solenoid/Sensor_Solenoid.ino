#define Sensor1 18
#define lock1 2

void setup(){
	pinMode(Sensor1, INPUT);
	pinMode(lock1, OUTPUT);
	digitalWrite(lock1, LOW);
	Serial.begin(115200);	
}

void loop(){
	Serial.println(digitalRead(Sensor1));

	if(!digitalRead(Sensor1)) digitalWrite(lock1, HIGH);
	else digitalWrite(lock1, LOW);
	
	delay(500);
}