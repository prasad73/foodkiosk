#define LED 2

#define RXD2 16
#define TXD2 17

bool Send_trigger = false;
bool state = HIGH;

String test_sequence = "0:1:0:0:0:1:0:0:0:0:&";

// HardwareSerial Serial2(2) // use UART2

void setup(){
	Serial.begin(9600);
	Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
	Serial.println("Initialization Done!!");
}

void loop(){
	if(Serial2.available()){
		char command = Serial2.read();
		if((command == 'S') && !Send_trigger){
			Serial.println("Command S detected");
			Serial2.flush();
			delay(500);
			Serial2.println(test_sequence);
			delay(500);
			Serial2.flush();
			// Serial2.flush();
			digitalWrite(LED, state);
			state =!state;
		}
		else if(command == 's'){
			Serial.println("Command small 's' detected");
			Send_trigger = true;
		}
	}

	if(Send_trigger){
		digitalWrite(LED, LOW);
		Serial.println("A");
		Serial2.println("A");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("B");
		Serial2.println("B");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("C");
		Serial2.println("C");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("D");
		Serial2.println("D");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("E");
		Serial2.println("E");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("F");
		Serial2.println("F");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("G");
		Serial2.println("G");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("H");
		Serial2.println("H");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("I");
		Serial2.println("I");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("J");
		Serial2.println("J");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("a");
		Serial2.println("a");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("b");
		Serial2.println("b");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("c");
		Serial2.println("c");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("d");
		Serial2.println("d");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("e");
		Serial2.println("e");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("f");
		Serial2.println("f");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("g");
		Serial2.println("g");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("h");
		Serial2.println("h");
		delay(4000);
		digitalWrite(LED, LOW);
		Serial.println("i");
		Serial2.println("i");
		delay(4000);
		digitalWrite(LED, HIGH);
		Serial.println("j");
		Serial2.println("j");
		delay(4000);
		Send_trigger = false;
	}
}