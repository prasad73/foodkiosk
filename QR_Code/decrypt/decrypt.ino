#include <AESLib.h>

AESLib aesLib;

void setup() {
    
    Serial.begin(115200);
    delay(5000);
    Serial.println("\nBooting...");  

  
  // byte key[] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };
    byte key[] = { 0x79, 0x72, 0x78, 0x38, 0x55, 0x49, 0x42, 0x6d, 0x4e, 0x55, 0x33, 0x67, 0x48, 0x32, 0x56, 0x48 , 0x51, 0x70, 0x62, 0x4f };
    
  // put your setup code here, to run once:
  byte my_iv[N_BLOCK] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  aesLib.gen_iv(my_iv);

  Serial.println("AES Key: ");
  int i;
  for (i = 0; i < sizeof(my_iv); i++)
  {
     Serial.print(my_iv[i], DEC); 
     Serial.print(",");
  }

  Serial.println("");

  // String msg = "i like dogs";
  String enc_msg = "U2FsdGVkX1+FxdMWsOm1umKeCwXDrInNlKTsMiOGzWLbGOrAIF+GrmjKm30XQDb4LKZz+3bUQ1FrPf88aaj9LlGOaN/GPUkgQPKK1Q87uyamSmHrZu8mwCRi6SyDWzSa";
  
  unsigned long ms = micros ();

  // String encMsg = aesLib.encrypt(msg, key, my_iv);
  // Serial.print("Encryption took: ");
  // Serial.println(micros() - ms);  
  // Serial.println("encMsg: " + encMsg);  

  String decMsg = aesLib.decrypt(enc_msg, key, my_iv);
  Serial.print("Decryption took: ");
  Serial.println(micros() - ms);  
  Serial.println("Decoded_Msg: " + decMsg);  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}