#define lock1 22
#define lock2 24
#define lock3 26
#define lock4 28
#define lock5 30
#define lock6 32
#define lock7 34
#define lock8 36
#define lock9 40
#define lock10 44
#define lock11 42
#define lock12 12

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
	Serial.println("Lock control and feedback test - Kiosk5");

	pinMode(lock1, OUTPUT);
	pinMode(lock2, OUTPUT);
	pinMode(lock3, OUTPUT);
	pinMode(lock4, OUTPUT);
	pinMode(lock5, OUTPUT);
	pinMode(lock6, OUTPUT);

	digitalWrite(lock1, LOW);
	digitalWrite(lock2, LOW);
	digitalWrite(lock3, LOW);
	digitalWrite(lock4, LOW);
	digitalWrite(lock5, LOW);
	digitalWrite(lock6, LOW);
	
	pinMode(lock1F, INPUT);
	pinMode(lock2F, INPUT);
	pinMode(lock3F, INPUT);
	pinMode(lock4F, INPUT);
	pinMode(lock5F, INPUT);
	pinMode(lock6F, INPUT);
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
		else if(command == 'a'){
			digitalWrite(lock10, HIGH);
			Serial.println("Lock10 Unlcoked");
			delay(drive_time);
			digitalWrite(lock10, LOW);
		}
		else if(command == 'b'){
			digitalWrite(lock11, HIGH);
			Serial.println("Lock11 Unlcoked");
			delay(drive_time);
			digitalWrite(lock11, LOW);
		}
		else if(command == 'c'){
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
	delay(1000);
}