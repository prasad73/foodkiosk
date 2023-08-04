#define ir_data 7

void setup(){
	pinMode(ir_data, INPUT);	
	Serial.begin(9600);
}

void loop(){
	Serial.println(digitalRead(ir_data));
	delay(2000);	
}