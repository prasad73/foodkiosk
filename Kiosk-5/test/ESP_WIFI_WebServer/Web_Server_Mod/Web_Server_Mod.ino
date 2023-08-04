// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "BSNL-FTTH-1908";
const char* password = "vtk2361908";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String State_1 = "off";
String State_2 = "off";
String State_3 = "off";
String State_4 = "off";
String State_5 = "off";
String State_6 = "off";

// Assign output variables to GPIO pins
const int output2 = 2;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output2, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output2, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("1 open");
              digitalWrite(output2, HIGH);
              delay(250);
              digitalWrite(output2, LOW);
              State_1 = "on";
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("1 off");
              State_1 = "off";  
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("2 Open");
              digitalWrite(output2, HIGH);
              delay(200);
              digitalWrite(output2, LOW);
              delay(200);
              digitalWrite(output2, HIGH);
              delay(200);
              digitalWrite(output2, LOW);
              State_2 = "on";
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("2 off");
              State_2 = "off";  
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("3 Open");
              digitalWrite(output2, HIGH);
              delay(1000);
              digitalWrite(output2, LOW);
              State_3 = "on";
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("3 off");
              State_3 = "off";  
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("4 Open");
              digitalWrite(output2, HIGH);
              delay(500);
              digitalWrite(output2, LOW);
              delay(500);
              digitalWrite(output2, HIGH);
              delay(500);
              digitalWrite(output2, LOW);
              State_4 = "on";
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("4 off");
              State_4 = "off";  
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("5 Open");
              digitalWrite(output2, HIGH);
              State_5 = "on";
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("5 off");
              State_5 = "off";  
            } else if (header.indexOf("GET /6/on") >= 0) {
              Serial.println("6 Open");
              digitalWrite(output2, LOW);
              State_6 = "on";
            } else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("6 off");
              State_6 = "off";  
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<title>Vendngo Kiosk</title>");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style> body {font-family: Arial, sans-serif; margin: 0; padding: 0; text-align: center; background: #882C88; background-image: url(\"background.jpg\"); background-size: cover; background-repeat: no-repeat; background-position: center; }");
            client.println(".container {max-width: 800px; margin: 0 auto; padding: 20px; text-align: center; }");
            client.println(".container h1 {margin: 15px 5px 5px 5px;}");
            client.println(".logo {background: url(\"https://versicles-strapi-media.s3.ap-south-1.amazonaws.com/vendngo_internallogo_f228223dff.png\") no-repeat; height: 56px; width: 264px; margin: auto;} ");
            client.println(".footer_logo {background: url(\"https://versicles-strapi-media.s3.ap-south-1.amazonaws.com/footer_Logointernal_1422be5a5a.png\") no-repeat; width: 77.04px; height: 77.04px; }");
            client.println(".settings-icon {position: fixed; bottom: 20px; right: 20px; font-size: 30px; cursor: pointer; color: #333; }");
            client.println(".button { background-color: #eee808; border: none; border-radius: 10px; color: #882C88; padding: 1px 3px;");            
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println("table, th, td {border:none;}");
            client.println(".button2 {background-color: #4CAF50;}</style></head>");
            
            client.println("<body> <div class=\"container\"> ");
            client.println("<div class=\"logo\"></div>");
            client.println("<h1 style=\"color: white;\">Locker Box Management</h1>");
            client.println("</div>"); 
            client.println("<div class=\"footer_logo settings-icon\"></div>");
            
            
            // client.println("<p> 1 - " + State_1 + "</p>");
            if (State_1=="off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">1.  OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">1. RESET</button></a></p>");
            } 
               
             
            // client.println("<p> 2 - " + State_2 + "</p>");      
            if (State_2=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">2.  OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">2. RESET</button></a></p>");
            }

            // client.println("<p> 3 - " + State_3 + "</p>");     
            if (State_3=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">3.  OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">3. RESET</button></a></p>");
            } 
               
             
            // client.println("<p> 4 - " + State_4 + "</p>");     
            if (State_4=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">4.  OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">4. RESET</button></a></p>");
            }


            // client.println("<p> 5 - " + State_5 + "</p>");      
            if (State_5=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">5.  OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">5. RESET</button></a></p>");
            } 
               
             
            // client.println("<p> 6 - " + State_6 + "</p>");      
            if (State_6=="off") {
              client.println("<p><a href=\"/6/on\"><button class=\"button\">6.  OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/6/off\"><button class=\"button button2\">6. RESET</button></a></p>");
            }


            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}