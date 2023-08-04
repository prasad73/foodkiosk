#define IR_Data  52  // IR Data


#define EN 50
#define S0 A0
#define S1 A1
#define S2 A2
#define S3 A3

////////////////////////////////////////////////////
/* Channel Selection guide        


S0 S1 S2 S3 E Channel
X  X  X  X  1 None
0  0  0  0  0 0
1  0  0  0  0 1
0  1  0  0  0 2
1  1  0  0  0 3
0  0  1  0  0 4
1  0  1  0  0 5
0  1  1  0  0 6
1  1  1  0  0 7
0  0  0  1  0 8
1  0  0  1  0 9
0  1  0  1  0 10
1  1  0  1  0 11
0  0  1  1  0 12
1  0  1  1  0 13
0  1  1  1  0 14
1  1  1  1  0 15
*///////////////////////////////////////////////////

int sensor = 1;


void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

  pinMode(IR_Data , INPUT);

  pinMode(EN, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  digitalWrite(EN , LOW);
  digitalWrite(S0 , LOW);
  digitalWrite(S1 , LOW);
  digitalWrite(S2 , LOW);
  digitalWrite(S3 , LOW);
}

void loop() {
  delay(30);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  // digitalWrite(EN , LOW);
  int reading = digitalRead(IR_Data);
  Serial.print(sensor);
  Serial.print(". IR_Data: ");
  Serial.println(reading); // Send ping, get distance in cm and print result (0 = outside set distance range)

  

  if(Serial.available()){
    char data = Serial.read();

    if(data == '1'){
      digitalWrite(S0 , LOW);
      digitalWrite(S1 , LOW);
      digitalWrite(S2 , LOW);
      digitalWrite(S3 , LOW);
      sensor = 1;
    }
    else if(data == '2'){
      digitalWrite(S0 , HIGH);
      digitalWrite(S1 , LOW);
      digitalWrite(S2 , LOW);
      digitalWrite(S3 , LOW);
      sensor = 2;
    }
    else if(data == '3'){
      digitalWrite(S0 , LOW);
      digitalWrite(S1 , HIGH);
      digitalWrite(S2 , LOW);
      digitalWrite(S3 , LOW);
      sensor = 3;
    }
    else if(data == '4'){
      digitalWrite(S0 , HIGH);
      digitalWrite(S1 , HIGH);
      digitalWrite(S2 , LOW);
      digitalWrite(S3 , LOW);
      sensor = 4;
    }
    else if(data == '5'){
      digitalWrite(S0 , LOW);
      digitalWrite(S1 , LOW);
      digitalWrite(S2 , HIGH);
      digitalWrite(S3 , LOW);
      sensor = 5;
    }
    else if(data == '6'){
      digitalWrite(S0 , HIGH);
      digitalWrite(S1 , LOW);
      digitalWrite(S2 , HIGH);
      digitalWrite(S3 , LOW);
      sensor = 6;
    }
    else if(data == '7'){
      digitalWrite(S0 , LOW);
      digitalWrite(S1 , HIGH);
      digitalWrite(S2 , HIGH);
      digitalWrite(S3 , LOW);
      sensor = 7;
    }
    else if(data == '8'){
      digitalWrite(S0 , HIGH);
      digitalWrite(S1 , HIGH);
      digitalWrite(S2 , HIGH);
      digitalWrite(S3 , LOW);
      sensor = 8;
    }
    else if(data == '9'){
      digitalWrite(S0 , LOW);
      digitalWrite(S1 , LOW);
      digitalWrite(S2 , LOW);
      digitalWrite(S3 , HIGH);
      sensor = 9;
    }
    else if(data == 'A'){
      digitalWrite(S0 , HIGH);
      digitalWrite(S1 , LOW);
      digitalWrite(S2 , LOW);
      digitalWrite(S3 , HIGH);
      sensor = 10;
    }
    else if(data == 'B'){
      digitalWrite(S0 , LOW);
      digitalWrite(S1 , HIGH);
      digitalWrite(S2 , LOW);
      digitalWrite(S3 , HIGH);
      sensor = 11;
    }
    else if(data == 'C'){
      digitalWrite(S0 , HIGH);
      digitalWrite(S1 , HIGH);
      digitalWrite(S2 , LOW);
      digitalWrite(S3 , HIGH);
      sensor = 12;
    }
    else if(data == 'D'){
      digitalWrite(S0 , LOW);
      digitalWrite(S1 , LOW);
      digitalWrite(S2 , HIGH);
      digitalWrite(S3 , HIGH);
      sensor = 13;
    }
    else if(data == 'E'){
      digitalWrite(S0 , HIGH);
      digitalWrite(S1 , LOW);
      digitalWrite(S2 , HIGH);
      digitalWrite(S3 , HIGH);
      sensor = 14;
    }
    else if(data == 'F'){
      digitalWrite(S0 , LOW);
      digitalWrite(S1 , HIGH);
      digitalWrite(S2 , HIGH);
      digitalWrite(S3 , HIGH);
      sensor = 15;
    }
    else if(data == 'G'){
      digitalWrite(S0 , HIGH);
      digitalWrite(S1 , HIGH);
      digitalWrite(S2 , HIGH);
      digitalWrite(S3 , HIGH);
      sensor = 16;
    }
  }
}