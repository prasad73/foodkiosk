void setup() {
  pinMode(23, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("22 = ");Serial.print(digitalRead(22));
  Serial.print("  23 = ");Serial.print(digitalRead(23));
  Serial.print("  18 = ");Serial.println(digitalRead(18));
  delay(2000);
}
