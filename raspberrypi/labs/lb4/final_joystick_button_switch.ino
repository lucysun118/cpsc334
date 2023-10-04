/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-joystick
 */

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
/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-switch
 */

#include <ezButton.h>

ezButton mySwitch(16);  // create ezButton object that attach to ESP32 pin GPIO16

int valueX = 0 ; // to store the X-axis value
int valueY = 0 ; // to store the Y-axis value
int command = COMMAND_NO;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  mySwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  // BUTTON
  // read the state of the switch/button:
  int buttonState = digitalRead(BUTTON_PIN);

  // print out the button's state
  Serial.println(buttonState);


  // JOYSTICK
  // read X and Y analog values
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);

  // converts the analog value to commands
  // reset commands
  command = COMMAND_NO;

  // check left/right commands
  if (valueX < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
  else if (valueX > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;

  // check up/down commands
  if (valueY < UP_THRESHOLD)
    command = command | COMMAND_UP;
  else if (valueY > DOWN_THRESHOLD)
    command = command | COMMAND_DOWN;

  // NOTE: AT A TIME, THERE MAY BE NO COMMAND, ONE COMMAND OR TWO COMMANDS

  // print command to serial and process command
  if (command & COMMAND_LEFT) {
    Serial.println("COMMAND LEFT");
    // TODO: add your task here
  }

  if (command & COMMAND_RIGHT) {
    Serial.println("COMMAND RIGHT");
    // TODO: add your task here
  }

  if (command & COMMAND_UP) {
    Serial.println("COMMAND UP");
    // TODO: add your task here
  }

  if (command & COMMAND_DOWN) {
    Serial.println("COMMAND DOWN");
    // TODO: add your task here
  }

  //SWITCH
    mySwitch.loop(); // MUST call the loop() function first

  if (mySwitch.isPressed())
    Serial.println("The switch: OFF -> ON");

  if (mySwitch.isReleased())
    Serial.println("The switch: ON -> OFF");

  int state = mySwitch.getState();
  if (state == HIGH)
    Serial.println("The switch: OFF");
  else
    Serial.println("The switch: ON");

  //ALL
  delay(500);
}
