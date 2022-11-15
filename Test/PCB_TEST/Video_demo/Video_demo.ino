#define R1 21
#define G1 19
#define B1 18

#define R2 27
#define G2 26
#define B2 25

#define R3 13
#define G3 33
#define B3 32

#define Lock1 22
#define Lock2 17
#define Lock3 16

// #define FeedBack 23

int R1_STATE = 0;
int G1_STATE = 0;
int B1_STATE = 0;

int R2_STATE = 0;
int G2_STATE = 0;
int B2_STATE = 0;

int R3_STATE = 0;
int G3_STATE = 0;
int B3_STATE = 0;

void setup(){
	pinMode(R1, OUTPUT);
	pinMode(G1, OUTPUT);
	pinMode(B1, OUTPUT);
	pinMode(Lock1, OUTPUT);

	pinMode(R2, OUTPUT);
	pinMode(G2, OUTPUT);
	pinMode(B2, OUTPUT);
	pinMode(Lock2, OUTPUT);
	
	pinMode(R3, OUTPUT);
	pinMode(G3, OUTPUT);
	pinMode(B3, OUTPUT);
	pinMode(Lock3, OUTPUT);

	// pinMode(FeedBack, INPUT);

	// digitalWrite(R1, LOW);
	// digitalWrite(B1, 1);
	digitalWrite(G1, 1);
	digitalWrite(B1, 1);
	digitalWrite(Lock1, 1);
	delay(1500);
	digitalWrite(Lock1, 0);

	// digitalWrite(R2, 1);
	digitalWrite(G2, 1);
	digitalWrite(B2, 1);
	digitalWrite(Lock2, LOW);

	digitalWrite(B3, 1);
	digitalWrite(G3, 1);
	digitalWrite(Lock3, LOW);

	Serial.begin(115200);
	Serial.println("video demo");
	
}

void loop(){
}