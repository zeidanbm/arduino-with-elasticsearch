/*
  ultrasonic sensor example
*/
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <WiFiNINA.h>
#include "ArduinoHttpClient.h"
#include "arduino_secrets.h"

/////// NTP Settings ///////
#define NTP_OFFSET   0      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "ca.pool.ntp.org"

/////// WiFi Settings ///////
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

// Replace with you server address and port
char serverAddress[] = "0331-76-66-96-209.ngrok.io";
int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS; // the Wifi radio's status

// Sensor pins //
#define trigPin 1
#define echoPin 2
  
long timestamp;
float distance;
float duration;

void initWifi() {
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  Serial.println("You're connected to the network");
  Serial.println("----------------------------------------");
}

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  initWifi();
  timeClient.begin();
}

void loop() 
{
  timeClient.update();
  // clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // send the ultrasound wave
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // read the travel time from high to low
  duration = pulseIn(echoPin, HIGH);
  timestamp = timeClient.getEpochTime();
  // calculate the distance in cm using 0.034 cm/us
  // we devide by 2 as this is the travel forward and back time of the wave
  distance = duration*0.034/2;

  Serial.print("distance: ");
  Serial.println(distance);
  Serial.print("timestamp: ");
  Serial.println(timestamp);

  Serial.println("making POST request");
  String contentType = "application/json";
  String postData = "{\"distance\":"; 
  postData += distance;
  postData += ",\"@timestamp\":\"";
  postData += timestamp;
  postData += "\"}";

  client.post("/sep769_lab4_index/_doc", contentType, postData);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  Serial.println('-------------');

  delay(5000);
}