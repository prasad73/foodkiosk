// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define EN A0
#define S0 A1
#define S1 A2
#define S2 A3
#define S3 A4

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

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
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
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  if(Serial.available()){
    char data = Serial.read();

    if(data == '1'){
      digitalWrite(S0 , LOW);
      digitalWrite(S1 , LOW);
      digitalWrite(S2 , LOW);
      digitalWrite(S3 , LOW);
      Serial.println("Sensor-1  Selected");  
    }
    else if(data == '2'){
      digitalWrite(S0 , HIGH);
      digitalWrite(S1 , LOW);
      digitalWrite(S2 , LOW);
      digitalWrite(S3 , LOW);
      Serial.println("Sensor-2  Selected");  
    }
    else if(data == '3'){
      digitalWrite(S0 , LOW);
      digitalWrite(S1 , LOW);
      digitalWrite(S2 , LOW);
      digitalWrite(S3 , HIGH);
      Serial.println("Sensor-3  Selected");  
    }
  }
}
