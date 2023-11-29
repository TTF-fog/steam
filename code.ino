int seconds = 0;

int moisture = 0;

#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "off";
String output27State = "off";

// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;

void setup()
{
  // this needs changed pinMode(11, OUTPUT);
  pinMode(15, INPUT);
  pinMode(2, OUTPUT);
  
}

void loop()
{
  
  //code for the pump
  
  String moisture = analogRead(15);
  
  
  if (moisture < 201) 
  {
    digitalWrite(2, HIGH);
    delay(4000); // Wait for 4000 millisecond(s)
  } 
  else if (moisture < 400) 
  {
      digitalWrite(2, HIGH);
      delay(2000); // Wait for 1000 millisecond(s)    
    } 
  else if (moisture < 600) 
    
  {
        digitalWrite(2, HIGH);
        delay(1000); // Wait for 1000 millisecond(s)
   } 
  
  else if (moisture < 800) 
    
  {
    
          digitalWrite(2, HIGH);
          delay(500); // Wait for 1000 millisecond(s)
    
  } 
  
  else 
    
  {
          digitalWrite(2, LOW);
          
   };
  

    
  
   // code to relay to computer
   WiFiClient client = server.available()

  ;if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
                   
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>Current Moisture: s " + moisture.str() + "</p>");
            // If the output26State is off, it displays the ON button       
            
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            
            // If the output27State is off, it displays the ON button       
           
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
    
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
      
    
  
}}
