#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;



char packetBuffer[255];
unsigned int localPort = 4200;
char *serverip = "172.29.134.136";
//unsigned int serverport = 8888;

const char *ssid = "yale wireless";
const char *pass = "";

//const char* ssid = "MOTO15A6";
//const char* pass = "9sfrtpp7zw";

// PINS

#define TOUCH_SENSOR_PIN 4 // ESP32 pin GIOP36 (ADC0)
#define LIGHT_SENSOR_PIN 36 // ESP32 pin GIOP36 (ADC0)
//#define FLEX_SENSOR_PIN 39 // ESP32 pin GIOP36 (ADC0)


void setup() {
  Serial.begin(115200);

  // Connect to Wifi network.
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500); Serial.print(F("."));
  }

  udp.begin(localPort);
  Serial.printf("UDP Client : %s:%i \n", WiFi.localIP().toString().c_str(), localPort);

}

void loop() {
  // TOUCH
  int touch_value = touchRead(TOUCH_SENSOR_PIN);

  Serial.print("Touch: ");
  Serial.println(touch_value); // the raw analog reading
  // if (touchRead(TOUCH_SENSOR_PIN) < 30) { // get value of Touch 0 pin = GPIO 4
  //   Serial.print(touchRead(TOUCH_SENSOR_PIN));
  //   //Serial.println("-> touched"); 
  // } else {
  //   Serial.print(touchRead(TOUCH_SENSOR_PIN));
  //   //Serial.println("-> not touched");
  // }

  // LIGHT
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Light: ");
  Serial.println(analogValue); // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  // if (analogValue < 40) {
  // Serial.println(" => Dark");
  // } else if (analogValue < 800) {
  // Serial.println(" => Dim");
  // } else if (analogValue < 2000) {
  // Serial.println(" => Light");
  // } else if (analogValue < 3200) {
  // Serial.println(" => Bright");
  // } else {
  // Serial.println(" => Very bright");
  // }

  // FLEX SENSOR
  // int flexValue = analogRead(FLEX_SENSOR_PIN);   // Read flex sensor value
  // Serial.print("Flex Sensor Value: ");
  // Serial.println(flexValue);

  // WIRELESS
  //Serial.print("[Client Connected] "); Serial.println(WiFi.localIP());
  udp.beginPacket(serverip, localPort);
  char buf[30];
  sprintf(buf, "Light: %lu", analogValue);
  udp.printf(buf);
  udp.endPacket();
  
  udp.beginPacket(serverip, localPort);
  sprintf(buf, "Touch: %lu", touch_value);
  udp.printf(buf);
  udp.endPacket();

  delay(1000);
}