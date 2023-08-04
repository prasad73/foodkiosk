#define lock1 23
#define lock2 25
#define lock3 27
#define lock4 29
#define lock5 31
#define lock6 33
#define lock7 35
#define lock8 37
#define lock9 39
#define lock10 41
#define lock11 43
#define lock12 47

#define drive_time 1000

void setup(){
	Serial.begin(115200);
	Serial.println("Temp feedback test - Kiosk5");

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