#include <WebSocketsServer.h>

WebSocketsServer webSocket(80);

#define VRX_PIN  36 // ESP32 pin GPIO36 (ADC0) connected to VRX pin
#define VRY_PIN  39 // ESP32 pin GPIO39 (ADC0) connected to VRY pin

#define LEFT_THRESHOLD  1000
#define RIGHT_THRESHOLD 3000
#define UP_THRESHOLD    1000
#define DOWN_THRESHOLD  3000

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

// BUTTON 
#define BUTTON_PIN 21 // GIOP21 pin connected to button

// SWITCH
#include <ezButton.h>

ezButton mySwitch(16);  // create ezButton object that attaches to ESP32 pin GPIO16

int valueX = 0; // to store the X-axis value
int valueY = 0; // to store the Y-axis value
int command = COMMAND_NO;

void setup() {
  Serial.begin(9600);

  // Start WebSocket server on port 80
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);

  mySwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  // JOYSTICK
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);

  // Determine joystick direction based on analog values
  int newCommand = COMMAND_NO;

  if (valueX < LEFT_THRESHOLD)
    newCommand = COMMAND_LEFT;
  else if (valueX > RIGHT_THRESHOLD)
    newCommand = COMMAND_RIGHT;

  if (valueY < UP_THRESHOLD)
    newCommand |= COMMAND_UP;
  else if (valueY > DOWN_THRESHOLD)
    newCommand |= COMMAND_DOWN;

  // Send joystick direction command to WebSocket clients only if the command has changed
  if (newCommand != command) {
    command = newCommand;
    sendCommandToClients(command);
  }

  // BUTTON
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW) {
    // Button is pressed, send a button press command to WebSocket clients
    sendCommandToClients(COMMAND_BUTTON_PRESS);
  } else {
    // Button is released, send a button release command to WebSocket clients
    sendCommandToClients(COMMAND_BUTTON_RELEASE);
  }

  // SWITCH
  mySwitch.loop();

  if (mySwitch.isPressed()) {
    // Switch is pressed, send a switch press command to WebSocket clients
    sendCommandToClients(COMMAND_SWITCH_PRESS);
  }

  if (mySwitch.isReleased()) {
    // Switch is released, send a switch release command to WebSocket clients
    sendCommandToClients(COMMAND_SWITCH_RELEASE);
  }

  // Handle WebSocket events
  webSocket.loop();
}

void sendCommandToClients(int command) {
  String message;

  // Determine the command and create a message to send to clients
  switch (command) {
    case COMMAND_LEFT:
      message = "LEFT";
      break;
    case COMMAND_RIGHT:
      message = "RIGHT";
      break;
    case COMMAND_UP:
      message = "UP";
      break;
    case COMMAND_DOWN:
      message = "DOWN";
      break;
    case COMMAND_BUTTON_PRESS:
      message = "BUTTON_PRESS";
      break;
    case COMMAND_BUTTON_RELEASE:
      message = "BUTTON_RELEASE";
      break;
    case COMMAND_SWITCH_PRESS:
      message = "SWITCH_PRESS";
      break;
    case COMMAND_SWITCH_RELEASE:
      message = "SWITCH_RELEASE";
      break;
    default:
      message = "STOP"; // You can define this message as needed
      break;
  }

  // Send the message to all connected WebSocket clients
  webSocket.broadcastTXT(message);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_TEXT:
      // Handle text messages received from WebSocket clients if needed...
      break;
    // Handle other WebSocket event types if needed...
  }
}