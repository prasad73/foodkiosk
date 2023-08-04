void setup() {
  pinMode(23, INPUT_PULLUP);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(23));
}
