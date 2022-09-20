#define Sensor1 18

void setup(){
	pinMode(Sensor1, INPUT);
	Serial.begin(115200);	
}

void loop(){
	Serial.println(digitalRead(Sensor1));
	delay(500);
}