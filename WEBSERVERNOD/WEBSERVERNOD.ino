
#include <ESP8266WiFi.h>

const char* ssid     = ""; //your ssid
const char* password = "";//your password

WiFiServer server(80);

String header;

// Auxiliar variables to store the current output state
String LED2= "off";


// Assign output variables to GPIO pins
const int Led2 = 2;


void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(Led2, OUTPUT);
  
  // Set outputs to LOW
  digitalWrite(Led2, LOW);
  

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
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
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
            if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("Led on");
              LED2= "on";
              digitalWrite(Led2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("Led off");
              LED2= "off";
              digitalWrite(Led2, LOW);
            } 
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color:#3BEC79 ; border: none; color: white; padding: 16px 40px;"); //#195B6A
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color:#DE3F47 ;}</style></head>");//#77878A
            
            // Web Page Heading
            client.println("<body><h1>ESP8266 Web Server Interno</h1>");
             
            client.println("<p>Led 2 " + LED2+ "</p>");
                
            if (LED2=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
           
            client.println("</body></html>");
            
            client.println();
           
            break;
          } else { // 
            currentLine = "";
          }
        } else if (c != '\r') {  //
          currentLine += c;      
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Cliente OFF.");
    Serial.println("");
  }
}
