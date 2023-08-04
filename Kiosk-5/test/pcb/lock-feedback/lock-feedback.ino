#define lock1 A4
#define lock2 A5
#define lock3 A6
#define lock4 A7
#define lock5 A8
#define lock6 A9
#define lock7 A10
#define lock8 A11
#define lock9 A12
#define lock10 A13
#define lock11 A14
#define lock12 A15


#define drive_time 1000

void setup(){
	Serial.begin(115200);
	Serial.println("Lock feedback test - Kiosk2");

	pinMode(lock1, INPUT);
	pinMode(lock2, INPUT);
	pinMode(lock3, INPUT);
	pinMode(lock4, INPUT);
	pinMode(lock5, INPUT);
	pinMode(lock6, INPUT);
	pinMode(lock7, INPUT);
	pinMode(lock8, INPUT);
	pinMode(lock9, INPUT);
	pinMode(lock10, INPUT);
	pinMode(lock11, INPUT);
	pinMode(lock12, INPUT);

	delay(2000);
}

void loop(){
	Serial.print("Status: ");
	Serial.print(digitalRead(lock1));
	Serial.print(":");
	Serial.print(digitalRead(lock2));
	Serial.print(":");
	Serial.print(digitalRead(lock3));
	Serial.print(":");
	Serial.print(digitalRead(lock4));
	Serial.print(":");
	Serial.print(digitalRead(lock5));
	Serial.print(":");
	Serial.print(digitalRead(lock6));
	Serial.print(":");
	Serial.print(digitalRead(lock7));
	Serial.print(":");
	Serial.print(digitalRead(lock8));
	Serial.print(":");
	Serial.print(digitalRead(lock9));
	Serial.print(":");
	Serial.print(digitalRead(lock10));
	Serial.print(":");
	Serial.print(digitalRead(lock11));
	Serial.print(":");
	Serial.println(digitalRead(lock12));
	delay(1000);
}