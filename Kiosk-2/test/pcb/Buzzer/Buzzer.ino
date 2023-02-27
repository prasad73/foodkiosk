#define buzzer 53

void setup(){
	Serial.begin(115200);
	Serial.println("Buzzer test - Kiosk2");

	pinMode(buzzer, OUTPUT);
	

	digitalWrite(buzzer, HIGH);
	Serial.println("------------>>>>>>> buzzer tone started");
	delay(5000);
	digitalWrite(buzzer, LOW);
	Serial.println("buzzer tone finished !!!!");
}

void loop(){
	
}