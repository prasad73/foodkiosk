#define lock1 22
#define lock2 24
#define lock3 26
#define lock4 28
#define lock5 30
#define lock6 32
#define lock7 34
#define lock8 36
#define lock9 38
#define lock10 46
#define lock11 42
#define lock12 48

// #define lock10 40
// #define lock13 12
// #define lock14 44


#define drive_time 1500

void setup(){
	Serial.begin(115200);
	Serial.println("Lock test - Kiosk2");

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


	digitalWrite(lock1, HIGH);
	Serial.println("Lock1 Unlcoked");
	delay(drive_time);
	digitalWrite(lock1, LOW);
	delay(2000);

	digitalWrite(lock2, HIGH);
	Serial.println("Lock2 Unlcoked");
	delay(drive_time);
	digitalWrite(lock2, LOW);
	delay(2000);

	digitalWrite(lock3, HIGH);
	Serial.println("Lock3 Unlcoked");
	delay(drive_time);
	digitalWrite(lock3, LOW);
	delay(2000);

	digitalWrite(lock4, HIGH);
	Serial.println("Lock4 Unlcoked");
	delay(drive_time);
	digitalWrite(lock4, LOW);
	delay(2000);

	digitalWrite(lock5, HIGH);
	Serial.println("Lock5 Unlcoked");
	delay(drive_time);
	digitalWrite(lock5, LOW);
	delay(2000);

	digitalWrite(lock6, HIGH);
	Serial.println("Lock6 Unlcoked");
	delay(drive_time);
	digitalWrite(lock6, LOW);
	delay(2000);

	digitalWrite(lock7, HIGH);
	Serial.println("Lock7 Unlcoked");
	delay(drive_time);
	digitalWrite(lock7, LOW);
	delay(2000);

	
	digitalWrite(lock8, HIGH);
	Serial.println("Lock8 Unlcoked");
	delay(drive_time);
	digitalWrite(lock8, LOW);
	delay(2000);

	digitalWrite(lock9, HIGH);
	Serial.println("Lock9 Unlcoked");
	delay(drive_time);
	digitalWrite(lock9, LOW);
	delay(2000);

	digitalWrite(lock10, HIGH);
	Serial.println("Lock10 Unlcoked");
	delay(drive_time);
	digitalWrite(lock10, LOW);
	delay(2000);

	digitalWrite(lock11, HIGH);
	Serial.println("Lock11 Unlcoked");
	delay(drive_time);
	digitalWrite(lock11, LOW);
	delay(2000);

	digitalWrite(lock12, HIGH);
	Serial.println("Lock12 Unlcoked");
	delay(drive_time);
	digitalWrite(lock12, LOW);
	delay(2000);

	// digitalWrite(lock13, HIGH);
	// Serial.println("Lock13 Unlcoked");
	// delay(drive_time);
	// digitalWrite(lock13, LOW);
	// delay(2000);

	// digitalWrite(lock14, HIGH);
	// Serial.println("Lock14 Unlcoked");
	// delay(drive_time);
	// digitalWrite(lock14, LOW);
	// delay(2000);

	// digitalWrite(lock15, HIGH);
	// Serial.println("Lock15 Unlcoked");
	// delay(drive_time);
	// digitalWrite(lock15, LOW);
	// delay(2000);

}

void loop(){
	
}