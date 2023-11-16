Fluid fluid;
import hypermedia.net.*;

UDP udp;

String lightMessage = "";
String touchMessage = "";

int touchThreshold = 30;
int touchTimer = 0;


boolean touchHeld = false;   // Flag to track touch sensor being held
int touchStartMillis = 0;   // Time when touch sensor was first held
int requiredTouchHoldTime = 5000; // 5 seconds (in milliseconds)

void settings() {
  size(N*SCALE,N*SCALE);
}

void setup() {
  // Initialize fluid with different parameters based on touch value
  int touchValue = extractTouchValue(touchMessage);

  //if (touchValue <= 70) {
    // Low touch value, initialize with fluid
  fluid = new Fluid(0.2, 0, 0.00000000001);
  //} else {
  //  // High touch value, initialize with no fluid
  //  fluid = new Fluid(0.0, 0, 0.0);
  //}

  size(N*SCALE, N*SCALE);
  color bg;

  udp = new UDP(this, 4200);
  udp.log(true);
  udp.listen(true);
}

void mouseDragged() {
  fluid.addDensity(mouseX/SCALE, mouseY/SCALE, 100);
  float amtX = mouseX - pmouseX;
  float amtY = mouseY - pmouseY;
  fluid.addVelocity(mouseX/SCALE, mouseY/SCALE, amtX, amtY);
}
boolean isSimulationPaused = false;

void draw() {
  int lightValue = extractLightValue(lightMessage);
  int touchValue = extractTouchValue(touchMessage);
  

  // Check the message type and assign it to the appropriate variable
  if (touchMessage.startsWith("Touch: ")) {
    // If the message starts with "Touch: ", extract the value
    touchValue = int(touchMessage.substring(7).trim());
  }

  if (touchValue == 0 || touchValue >= 50) {
  //  // High touch value, pause the fluid simulation
  // Simulate the behavior of mouseDragged using light and touch values
    float densityChange = map(lightValue, 0, 255, 0, 300);
    int cx = int(0.5 * width / SCALE);
    int cy = int(0.5 * height / SCALE);

    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        fluid.addDensity(cx + i, cy + j, densityChange);
      }
    }

    float velocityScale = map(touchValue, 0, 255, 2.0, 10.0);

    float angle = noise(t) * TWO_PI * 2;
    PVector v = PVector.fromAngle(angle);
    v.mult(0.1 * velocityScale);
    t += 0.05 / velocityScale;

    fluid.addVelocity(cx, cy, v.x, v.y);

    fluid.step();
    fluid.renderD();
    fluid.fadeD();
  } else {
  //  //isSimulationPaused = false;
    fluid.decreaseVelocityGeneration();
    
    // Simulate the behavior of mouseDragged using light and touch values
    float densityChange = map(lightValue, 0, 255, 0, 300);
    int cx = int(0.5 * width / SCALE);
    int cy = int(0.5 * height / SCALE);

    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        fluid.addDensity(cx + i, cy + j, densityChange);
      }
    }

    float velocityScale = map(touchValue, 0, 255, 2.0, 10.0);

    float angle = noise(t) * TWO_PI * 2;
    PVector v = PVector.fromAngle(angle);
    v.mult(0.1 * velocityScale);
    t += 0.05 / velocityScale;

    fluid.addVelocity(cx, cy, v.x, v.y);

    fluid.step();
    fluid.renderD();
    fluid.fadeD();
  }}

//  if (isSimulationPaused) {
//    // Display a paused message or perform other actions
//  }
//}


//void draw() {
//  int lightValue = extractLightValue(lightMessage);
//  int touchValue = extractTouchValue(touchMessage);


//  // Check if the touch value is less than 30
//  if (touchValue < 40) {
//    // Check if the touch sensor is being held
//    if (!touchHeld) {
//      touchHeld = true;
//      touchStartMillis = millis();
//    } else {
//      // Calculate the duration the touch sensor has been held
//      int touchHoldDuration = millis() - touchStartMillis;

//      // Check if the touch sensor has been held for at least 5 seconds
//      if (touchHoldDuration >= requiredTouchHoldTime ) {
//        // Background color becomes blue
//        background(0, 0, 255);
//      }
//    }
//  } else {
//    // Reset touchHeld flag when touch value is not less than 30
//    touchHeld = false;
//  }


//  //if (touchValue >= 75) {
//  //  // High touch value, decrease fluid velocity generation
    
//  //  //background(0); // Set any background color you prefer
//  //} else {
//    // Reset fluid velocity generation to its default state
//    //fluid.resetVelocityGeneration();
//    fluid.decreaseVelocityGeneration();

//    // Simulate the behavior of mouseDragged using light and touch values
//    float densityChange = map(lightValue, 0, 255, 10, 10);
//    int cx = int(0.5 * width / SCALE);
//    int cy = int(0.5 * height / SCALE);

//    for (int i = -1; i <= 1; i++) {
//      for (int j = -1; j <= 1; j++) {
//        fluid.addDensity(cx + i, cy + j, densityChange);
//      }
//    }

//    float velocityScale = map(touchValue, 0, 255, 2.0, 10.0);

//    float angle = noise(t) * TWO_PI * 2;
//    PVector v = PVector.fromAngle(angle);
//    v.mult(0.1 * velocityScale);
//    t += 0.05 / velocityScale;

//    fluid.addVelocity(cx, cy, v.x, v.y);

//    fluid.step();
//    fluid.renderD();
//    fluid.fadeD();
//  }

void receive(byte[] data, String ip, int port) {
  String message = new String(data);
  println("receive: \"" + message + "\" from " + ip + " on port " + port);

  if (message.startsWith("Light: ")) {
    lightMessage = message;
  } else if (message.startsWith("Touch: ")) {
    touchMessage = message;
    int touchValue = extractTouchValue(message);

    if (touchValue > 75) {
      // High touch value, set velocity to zero for incoming fluid
      fluid.setVelocityToZero();
    }
  }
}

// Function to extract the light value from the message
int extractLightValue(String message) {
  String[] parts = splitTokens(message);
  if (parts.length >= 2) {
    return int(parts[1]);
  } else {
    return 0; // Handle the case when the message doesn't contain a value
  }
}

// Function to extract the touch value from the message
int extractTouchValue(String message) {
  String[] parts = splitTokens(message);
  if (parts.length >= 3) {
    return int(parts[2]);
  } else {
    return 0; // Handle the case when the message doesn't contain a value
  }
}