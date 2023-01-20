#define Sensor1 A0
#define Sensor2 A1
#define Sensor3 A2
#define Sensor4 A3
#define Sensor5 A4
#define Sensor6 A5

void setup(){
	pinMode(Sensor1 , INPUT);
	pinMode(Sensor2 , INPUT);
	pinMode(Sensor3 , INPUT);
	pinMode(Sensor4 , INPUT);
	pinMode(Sensor5 , INPUT);
	pinMode(Sensor6 , INPUT);

	Serial.begin(115200);
}

void loop(){
	Serial.print("S1: ");
	Serial.print(digitalRead(Sensor1));
	Serial.print(" S2: ");
	Serial.print(digitalRead(Sensor2));
	Serial.print(" S3: ");
	Serial.print(digitalRead(Sensor3));
	Serial.print(" S4: ");
	Serial.print(digitalRead(Sensor4));
	Serial.print(" S5: ");
	Serial.print(digitalRead(Sensor5));
	Serial.print(" S6: ");
	Serial.println(digitalRead(Sensor6));

	delay(1000);
}