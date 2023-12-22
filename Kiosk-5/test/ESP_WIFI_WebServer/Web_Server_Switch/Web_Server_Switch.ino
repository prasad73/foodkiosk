#include "WiFi.h"
#define LED0 23
#define LED1 22
const char* ssid = "Kiosk5";
const char* password = "";
WiFiServer server(80);
String html ="<!DOCTYPE html> \
<html> \
<body> \
<center><h1>ESP32 Soft access point</h1></center> \
<center><h2>Web Server</h2></center> \
<form> \
<button name=\"LED0\" button style=\"color:green\" value=\"ON\" type=\"submit\">LED0 ON</button> \
<button name=\"LED0\" button style=\"color=red\" value=\"OFF\" type=\"submit\">LED0 OFF</button><br><br> \
<button name=\"LED1\" button style=\"color:green\" value=\"ON\" type=\"submit\">LED1 ON</button> \
<button name=\"LED1\" button style=\"color:red\" value=\"OFF\" type=\"submit\">LED1 OFF</button> \
</form> \
</body> \
</html>";


void Connect_WiFi()
{
WiFi.begin(ssid, password);
if(WiFi.status() != WL_CONNECTED)
{
// delay(100);
}
}

void setup()
{
Serial.begin(115200);
pinMode(LED0, OUTPUT);
pinMode(LED1, OUTPUT);
digitalWrite(LED0, LOW);
digitalWrite(LED1, LOW);

Connect_WiFi();

server.begin();

delay(1000);
Serial.print("Setting soft access point mode");

// WiFi.mode(WIFI_AP);
// WiFi.disconnect();
// delay(100);

IPAddress IP = WiFi.softAPIP();
Serial.print("AP IP address: ");
Serial.println(IP);
// WiFi.softAP(ssid, password);
WiFi.softAP("Kiosk5", "");
delay(1000);
Serial.println("Scan Network......");
}


void loop()
{
WiFiClient client=server.available();
if(client)
{
String request = client.readStringUntil('\r');
if(request.indexOf("LED0=ON") != -1){digitalWrite(LED0, HIGH);Serial.println("LED0 HIGH");}
if(request.indexOf("LED0=OFF") != -1){digitalWrite(LED0, LOW);Serial.println("LED0 LOW");}
if(request.indexOf("LED1=ON") != -1){digitalWrite(LED1, HIGH);Serial.println("LED1 HIGH");}
if(request.indexOf("LED1=OFF") != -1){digitalWrite(LED1, LOW);Serial.println("LED1 LOW");}
client.print(html);
request="";
}
}