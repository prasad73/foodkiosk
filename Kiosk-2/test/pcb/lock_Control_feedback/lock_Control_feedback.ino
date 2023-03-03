#define lock4 22
#define lock5 24
#define lock6 26
#define lock1 28
#define lock2 30
#define lock3 32
#define lock7 34
#define lock8 36
#define lock9 38
#define lock10 46
#define lock11 42
#define lock12 48

#define lock1F A4
#define lock2F A5
#define lock3F A6
#define lock4F A7
#define lock5F A8
#define lock6F A9
#define lock7F A10
#define lock8F A11
#define lock9F A12
#define lock10F A13
#define lock11F A14
#define lock12F A15

// #define lock10 40
// #define lock13 12
// #define lock14 44


#define drive_time 1200

void setup(){
	Serial.begin(115200);
	Serial.println("Lock control and feedback test - Kiosk2");

	pinMode(lock1, OUTPUT);
	pinMode(lock2, OUTPUT);
	pinMode(lock3, OUTPUT);
	pinMode(lock4, OUTPUT);
	pinMode(lock5, OUTPUT);
	pinMode(lock6, OUTPUT);
	pinMode(lock7, OUTPUT);
	pinMode(lock8, OUTPUT);
	pinMode(lock9, OUTPUT);
	pinMode(lock10, OUTPUT);
	pinMode(lock11, OUTPUT);
	pinMode(lock12, OUTPUT);


	digitalWrite(lock1, LOW);
	digitalWrite(lock2, LOW);
	digitalWrite(lock3, LOW);
	digitalWrite(lock4, LOW);
	digitalWrite(lock5, LOW);
	digitalWrite(lock6, LOW);
	digitalWrite(lock7, LOW);
	digitalWrite(lock8, LOW);
	digitalWrite(lock9, LOW);
	digitalWrite(lock10, LOW);
	digitalWrite(lock11, LOW);
	digitalWrite(lock12, LOW);

	pinMode(lock1F, INPUT);
	pinMode(lock2F, INPUT);
	pinMode(lock3F, INPUT);
	pinMode(lock4F, INPUT);
	pinMode(lock5F, INPUT);
	pinMode(lock6F, INPUT);
	pinMode(lock7F, INPUT);
	pinMode(lock8F, INPUT);
	pinMode(lock9F, INPUT);
	pinMode(lock10F, INPUT);
	pinMode(lock11F, INPUT);
	pinMode(lock12F, INPUT);

}

void loop(){
	if(Serial.available()){
		char command = Serial.read();

		if(command == '1'){
			digitalWrite(lock1, HIGH);
			Serial.println("Lock1 Unlcoked");
			delay(drive_time);
			digitalWrite(lock1, LOW);
		}
		else if(command == '2'){
			digitalWrite(lock2, HIGH);
			Serial.println("Lock2 Unlcoked");
			delay(drive_time);
			digitalWrite(lock2, LOW);
		}
		else if(command == '3'){
			digitalWrite(lock3, HIGH);
			Serial.println("Lock3 Unlcoked");
			delay(drive_time);
			digitalWrite(lock3, LOW);
		}
		else if(command == '4'){
			digitalWrite(lock4, HIGH);
			Serial.println("Lock4 Unlcoked");
			delay(drive_time);
			digitalWrite(lock4, LOW);
		}
		else if(command == '5'){
			digitalWrite(lock5, HIGH);
			Serial.println("Lock5 Unlcoked");
			delay(drive_time);
			digitalWrite(lock5, LOW);
		}
		else if(command == '6'){
			digitalWrite(lock6, HIGH);
			Serial.println("Lock6 Unlcoked");
			delay(drive_time);
			digitalWrite(lock6, LOW);
		}
		else if(command == '7'){
			digitalWrite(lock7, HIGH);
			Serial.println("Lock7 Unlcoked");
			delay(drive_time);
			digitalWrite(lock7, LOW);
		}
		else if(command == '8'){
			digitalWrite(lock8, HIGH);
			Serial.println("Lock8 Unlcoked");
			delay(drive_time);
			digitalWrite(lock8, LOW);
		}
		else if(command == '9'){
			digitalWrite(lock9, HIGH);
			Serial.println("Lock9 Unlcoked");
			delay(drive_time);
			digitalWrite(lock9, LOW);
		}
		else if(command == 'A'){
			digitalWrite(lock10, HIGH);
			Serial.println("Lock10 Unlcoked");
			delay(drive_time);
			digitalWrite(lock10, LOW);
		}
		else if(command == 'B'){
			digitalWrite(lock11, HIGH);
			Serial.println("Lock11 Unlcoked");
			delay(drive_time);
			digitalWrite(lock11, LOW);
		}else if(command == 'C'){
			digitalWrite(lock12, HIGH);
			Serial.println("Lock12 Unlcoked");
			delay(drive_time);
			digitalWrite(lock12, LOW);
		}
	}

	Serial.print("Status: ");
	Serial.print(digitalRead(lock1F));
	Serial.print(":");
	Serial.print(digitalRead(lock2F));
	Serial.print(":");
	Serial.print(digitalRead(lock3F));
	Serial.print(":");
	Serial.print(digitalRead(lock4F));
	Serial.print(":");
	Serial.print(digitalRead(lock5F));
	Serial.print(":");
	Serial.print(digitalRead(lock6F));
	Serial.print(":");
	Serial.print(digitalRead(lock7F));
	Serial.print(":");
	Serial.print(digitalRead(lock8F));
	Serial.print(":");
	Serial.print(digitalRead(lock9F));
	Serial.print(":");
	Serial.print(digitalRead(lock10F));
	Serial.print(":");
	Serial.print(digitalRead(lock11F));
	Serial.print(":");
	Serial.println(digitalRead(lock12F));
	delay(1000);
}