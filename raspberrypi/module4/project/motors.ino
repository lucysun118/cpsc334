// pressing the button toggles between states 1 and 2
// state 1: pressing touch sensor 1 - the hands are both moving left
// state 2: pressing touch sensor 1 - the hands are both moving right

// shining the flashlight makes the hands continuously move outwards (servo)
// pressing the touch sensor 2 makes hands clap once
#include <Servo.h>
#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// so if 360 degrees takes 2048 steps, 1 step is 360/2048 = 0.029296875 degrees
// if 1/4 radius, circum = 0.785 inch
// 1 step = 0.785 inch

// ULN2003 Motor Driver Pins - STEPPER MOTOR 1
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

// ULN2003 Motor Driver Pins - STEPPER MOTOR 2
#define IN1_2 27
#define IN2_2 14
#define IN3_2 12
#define IN4_2 15

// Button pin
#define BUTTON_PIN 23

// Light pin
#define LIGHT_SENSOR_PIN 26

// TOUCH 1 pin
#define TOUCH_SENSOR1_PIN 33

// TOUCH 2 pin
#define TOUCH_SENSOR2_PIN 32

// Vibration pin
#define VIBRATION_PIN 21

// Button and State Handling Constants
#define DOUBLE_CLICK_DELAY 1000  // Adjust this value based on your requirements (in milliseconds)
//#define HOLD_THRESHOLD 3000    // Adjust this value based on your requirements (in milliseconds)
#define TOUCH_SENSOR_TOUCH_THRESHOLD 30
#define TOUCH_SENSOR_HOLD_THRESHOLD 1000

#define SHORT_PRESS_TIME 500  // 500 milliseconds
#define REFERENCE_ANGLE 90
int touched = 0;              // 0 = not touched, 1 = touched
bool button_pressed_state;
bool touch1_held_state;
bool touch2_held_state;
bool light_sensor_bright;
int stepCount = 0;

// Initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);
Stepper myStepper_2(stepsPerRevolution, IN1_2, IN3_2, IN2_2, IN4_2);
Servo myservo1;  // create a servo object to control a servo
Servo myservo2;  // create a servo object to control a servo

int pos1;  // variable to store the servo position
int pos2;  // variable to store the servo position
int count = 0;

unsigned long lastButtonClickTime = 0;
int currentState = 2;
//bool buttonHeld = false;
unsigned long buttonHoldStartTime = 0;

bool touched_sensor1_state;
bool touched_sensor2_state;

void setup() {
  // Set the speed at 10 rpm
  myStepper.setSpeed(10);
  myStepper_2.setSpeed(10);
  // Initialize the serial port
  Serial.begin(9600);

  // 1st servo
  myservo1.attach(4);  // Attaches the servo on pin 4

  // 2nd servo
  myservo2.attach(2);  // Attaches the servo on pin 2

  // BUTTON
  // Initialize the pushbutton pin as a pull-up input
  // The pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TOUCH_SENSOR1_PIN, INPUT);
  pinMode(TOUCH_SENSOR2_PIN, INPUT);

  pinMode(VIBRATION_PIN, OUTPUT);

  pos1 = 0;
  pos2 = 0;
  myservo1.write(REFERENCE_ANGLE);
  myservo2.write(REFERENCE_ANGLE);
}

void loop() {

  // REGISTER

  // BUTTON
  if (isButtonClicked(BUTTON_PIN)) {
    button_pressed_state = true;
  } else {
    button_pressed_state = false;
  }

  // TOUCH 1
  if (touchRead(TOUCH_SENSOR1_PIN) < TOUCH_SENSOR_TOUCH_THRESHOLD) {  // get value of Touch 0 pin = GPIO 4
    touched_sensor1_state = true;
  } else {
    touched_sensor1_state = false;
  }

  // TOUCH 2
  if (touchRead(TOUCH_SENSOR2_PIN) < TOUCH_SENSOR_TOUCH_THRESHOLD) {  // get value of Touch 0 pin = GPIO 4
    touched_sensor2_state = true;
  } else {
    touched_sensor2_state = false;
  }

  // STEPPER
  touch1_held_state = isTouchHeld(TOUCH_SENSOR1_PIN);
  int touchState1 = touchRead(TOUCH_SENSOR1_PIN);
  if (currentState == 1) {
    if (touch1_held_state) {
      //Serial.println("clockwise");

      while (touchState1 <= 30) {
        touchState1 = touchRead(TOUCH_SENSOR1_PIN);
        stepCount = stepCount % stepsPerRevolution;
        myStepper.step(1);    // Rotate only 180 degrees
        myStepper_2.step(1);  // Rotate only 180 degrees
        stepCount++;
        delay(2);
      }
    }
  } else if (currentState == 2) {
    if (touch1_held_state) {
      while (touchState1 <= 30) {
        touchState1 = touchRead(TOUCH_SENSOR1_PIN);
        stepCount = stepCount % stepsPerRevolution;
        myStepper.step(-1);    // Rotate only 180 degrees
        myStepper_2.step(-1);  // Rotate only 180 degrees
        stepCount--;
        delay(2);
    }
  }}


  // register touch hold
  else if (currentState == 3) {
    //look for light data
    //light_sensor_bright = isLightOn(LIGHT_SENSOR_PIN);
    int touchState = touchRead(TOUCH_SENSOR1_PIN);

    if (touchState <= 30) {
      if (REFERENCE_ANGLE + pos1 <= 350) {
        //Serial.println(" moving hands wider ");
        //Serial.println("Touch held for at least 1 second");

        // while touch 1 sensor is held, rotate servo motor in one direction
        // in steps of 1 degree
        myservo1.write(REFERENCE_ANGLE + pos1);  // tell servo to go to position in variable 'pos'
        myservo2.write(REFERENCE_ANGLE + pos2);
        pos1 = pos1 + 10;
        pos2 = pos2 - 10;
        delay(300);  // waits 15ms for the servo to reach the position
      }
    } else {
      if (REFERENCE_ANGLE + pos1 > REFERENCE_ANGLE) {
        // steps: ranges from -2048 to +2048
        // light: ranges from 0 to 3000
        Serial.print("clap,");
        //Serial.print("Steps: ");
        Serial.print(stepCount);

        int analogValue = analogRead(LIGHT_SENSOR_PIN);
        //Serial.print(", Light: ");
        Serial.print(",");
        Serial.print(analogValue);
        Serial.println();

        pos1 = -45;
        pos2 = -45;
        myservo1.write(REFERENCE_ANGLE + pos1);  // tell servo to go to position in variable 'pos'
        myservo2.write(REFERENCE_ANGLE - pos2);
        delay(300);

        pos1 = 0;
        pos2 = 0;
        myservo1.write(REFERENCE_ANGLE + pos1);  // tell servo to go to position in variable 'pos'
        myservo2.write(REFERENCE_ANGLE - pos2);
      }
    }
  }

  // VIBRATION - TOUCH SENSOR 2
int touchState2 = touchRead(TOUCH_SENSOR2_PIN);

if (touchState2 <= 30) {
  if (!touch2_held_state) {
    // Triggered when the touch state is less than or equal to 30 and was not held previously
    Serial.println("SHAKE,DETECTED");
    digitalWrite(VIBRATION_PIN, HIGH);
    touch2_held_state = true;
  }
} else {
  // Reset the held state when the touch state is greater than 30
  touch2_held_state = false;
  digitalWrite(VIBRATION_PIN, LOW);
}


  // LIGHT SENSOR - WARMNESS OF COLORS
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  //Serial.println(analogValue);


  // RESET STATES
  //button_pressed_state = false;
  //touched_sensor1_state = false;
  //touch1_held_state = false;
  delay(100);
}

bool isLightOn(int lightPin) {
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  if (analogValue >= 1500) {
    return true;
  }
  return false;
  //return true if analogValue >= 1500 else false;
}
bool isButtonClicked(int buttonPin) {
  int buttonState = !digitalRead(BUTTON_PIN);  // 0 is unpressed, 1 is pressed

  if (buttonState == 1) {
    //Serial.print("button-click, state ");
    if (currentState == 1) {
      currentState = 2;
    } else if (currentState == 2) {
      currentState = 3;
    } else {
      currentState = 1;
    }
    Serial.println(currentState);
    delay(200);
    return true;
  }
  delay(200);
  return false;
}

bool isTouchHeld(int touchPin) {
  static unsigned long touchStartTime = 0;

  int touchState = touchRead(touchPin);
  // if (touchPin == 32) {
  // Serial.println(touchState);}

  if (touchState <= 30) {
    if (touchStartTime == 0) {
      // Touch has just been detected, record the start time
      touchStartTime = millis();
    } else {
      if (touchPin == 32) {
        //Serial.println(touchStartTime);
      }
      // Touch is still detected, check if it has been held for the threshold
      if (millis() - touchStartTime >= TOUCH_SENSOR_HOLD_THRESHOLD) {
        touchStartTime = 0;  // Reset the start time for the next detection
        //Serial.print("touch sensor held");
        //Serial.println(touchPin);
        return true;  // Touch has been held for at least 1 second
      }
    }
  } else {
    // Touch is not detected, reset the start time
    touchStartTime = 0;
  }

  return false;  // Touch is not held for the threshold
}

void moveServos(int angle) {
  myservo1.write(angle);
  myservo2.write(-angle);
}