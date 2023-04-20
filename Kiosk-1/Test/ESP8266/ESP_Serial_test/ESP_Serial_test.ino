#define LED 9

bool Send_trigger = false;
bool state = HIGH;
char* MyString = "1:0:0:0:0:0:0:0:0:0:&";

void setup(){
	Serial.begin(9600);
	Serial.set_tx(2);
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
	// Send_trigger = true;	
	delay(10000);
}

void loop(){
	if(Serial.available()){
		char command = Serial.read();
		if((command == 'S') && !Send_trigger){
			Serial.println("1:0:0:0:0:0:0:0:0:0:&");
			delay(100);
			Serial.flush();
			digitalWrite(LED, state);
			state =!state;
			delay(1000);
		}
		else if(command == 's'){
			Send_trigger = true;
		}
		else if((command == 'Z')&& !Send_trigger){
			Serial.write(MyString, sizeof(MyString));
			Serial.flush();
			digitalWrite(LED, HIGH);
			delay(10000);
		}
	}

	if(Send_trigger){
		digitalWrite(LED, LOW);
		Serial.println("A");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("B");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("C");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("D");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("E");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("F");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("G");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("H");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("I");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("J");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("a");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("b");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("c");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("d");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("e");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("f");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("g");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("h");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("i");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("j");
		delay(4000);
		Send_trigger = false;
	}
}