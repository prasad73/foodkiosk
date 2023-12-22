void setup() {
  pinMode(23, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("22 = ");Serial.println(digitalRead(22));
  Serial.print("23 = ");Serial.println(digitalRead(23));
  delay(2000);
}
