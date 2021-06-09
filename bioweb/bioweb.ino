//#include "DHT.h"
//#include <DHT_U.h>

//#include <idDHT11.h>

//#include <dht.h>

#include <Adafruit_Sensor.h>



//#include <DHT.h>


//#include <IoTtweet.h>

// Libraries
#include <ESP8266WiFi.h>
#include <DHT.h>
//4. ssid and password is set in this section:
// Wi-Fi network SSID and password
const char* ssid = "APTDAC01";
const char* password = "FatecSJC146";
//5. Store the host name of the cloud server:
// Host
const char* host = "dweet.io";
//6. Define the pin that is connected to the DHT11 signal pin and the type of DHT sensor
//that we are using:
#define DHTPIN D2 // what digital pin DHT11 is connected to
#define DHTTYPE DHT11 // DHT 11 sensor
//7. Create a dht object:
DHT dht(DHTPIN, DHTTYPE);
//8. Declare a variable that will hold the moistureReading:
int moistureReading = 0; // holds value soil moisture sensor
//reading
//9. Initialize the serial interface and the DHT object. Configure the ssid and password
//of the Wi-Fi network and connect the ESP8266 to it:
void setup() {
 Serial.begin(115200); // initialize serial interface
 dht.begin(); // initialize DHT11 sensor
 delay(10);
 // We start by connecting to a WiFi network
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);

 WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
//Cloud Data Monitoring
//114
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
}
//10. Delay for five seconds, then print the name of the host we are connecting to on the
//serial monitor:
void loop() {
 delay(5000);
 Serial.print("connecting to ");
 Serial.println(host);
//11. Connect to the host server. Retry if not successful:
 // Use WiFiClient class to create TCP connections
 WiFiClient client;
 const int httpPort = 80;
 if (!client.connect(host, httpPort)) {
 Serial.println("connection failed");
 return;
 }
//12. Get readings from the DHT11 sensor and soil moisture sensor:
 // Read sensor inputs
 // get humidity reading
 float h = dht.readHumidity();
 // get temperature reading in Celsius
 float t = dht.readTemperature();
 // Check if any reads failed and exit early (to try again).
 while (isnan(h) || isnan(t)) {
 Serial.println("Failed to read from DHT sensor!");
 delay(2000); // delay before next measurements
 //get the measurements once more
 h = dht.readHumidity();
 t = dht.readTemperature();
 }
 //get soil moisture reading
 moistureReading = analogRead(A0);
//Chapter 5
//115
// Generate a URL for the GET request we will send to the host server. The URL
//will include the sensor readings:
 // We now create a URI for the request
  String url = "/dweet/for/biodata?Umidade_Do_Ar=";
 url += String(h);
 url += "&Temperatura=";
 url += String(t);
 url += "&Umidade_Do_Solo=";
 url += String(moistureReading);
//13. Send the GET request to the server and check whether the request has been
//received, or if it has been timed out:
 // Send request
 Serial.print("Requesting URL: ");
 Serial.println(url);

 client.print(String("GET ") + url + " HTTP/1.1\r\n" +
 "Host: " + host + "\r\n" +
 "Connection: close\r\n\r\n");
 unsigned long timeout = millis();
 while (client.available() == 0) {
 if (millis() - timeout > 5000) {
 Serial.println(">>> Client Timeout !");
 client.stop();
 return;
 }
 }
// Read incoming data from the host server line by line and display the data
//on the serial monitor. Close the connection after all the data has been
//received from the server:
 // Read all the lines from the answer
 while(client.available()){
 String line = client.readStringUntil('\r');
 Serial.print(line);
 }
 // Close connecting
 Serial.println();
 Serial.println("closing connection");
}
//Cloud Data Monit
