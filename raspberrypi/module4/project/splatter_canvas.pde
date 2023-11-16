import processing.serial.*;

int splatterSize = 30; // Size of each splatter
Serial myPort;  // Create object from Serial class
String val;
int motor1Position;  // Initialize motor 1 position
String lightVal;
int int_lightval;

boolean drawSplatterFlag = true; // Flag to control whether to draw a splatter

void setup() {
  size(800, 600);
  background(255); // White canvas

  // Replace "COM3" with the port your Arduino is connected to
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  // No need for continuous drawing in this example
  while ( myPort.available() > 0) 
  {  // If data is available,
  String inBuffer = myPort.readStringUntil('\n');
  if (inBuffer != null) {
    //println(inBuffer);
    
    String[] data = split(inBuffer, ',');
    print(data);
    if (data.length == 3) {
    motor1Position = int(data[1]);
    lightVal = (data[2].trim());
    println("lightval:");
    int_lightval = int(lightVal);
    println(int_lightval);
    drawSplatterFlag = true; // Set the flag to true to allow drawing a splatters
    
    } else if (data.length == 2) {
      clearCanvas();
      motor1Position = int(random(width));
      int_lightval = int(random(0, 255));
      
      drawSplatterFlag = false; // Set the flag to false to prevent drawing another splatter
    }
    else {
      motor1Position = int(random(width));
      int_lightval = int(random(0, 255));
      drawSplatterFlag = false; // Set the flag to false to prevent drawing another splatter
    }

    float splatterX = map(motor1Position, -2048, 2048, 0, width);
  //print(splatterX);
  float splatterY = noise(motor1Position * 0.02) * height;
  
  // Generate a random color for the splatter
  //color splatterColor = color(random(255), random(255), random(255), 150);
  
  // Draw a splatter at the calculated x position and mouse y position
  if (drawSplatterFlag) {
        drawSplatter(splatterX, splatterY, splatterSize, int_lightval);
        drawSplatterFlag = false; // Set the flag to false after drawing a splatter
      }
}}}

void drawSplatter(float x, float y, float size, int light) {
  // Map the light value to the color range
  float mappedColorValue = map(light, 400, 3000, 0, 1);
  
  // Interpolate between red and blue based on the mapped value
  float red = 255;
  float blue = 0;
  float interpolationValue = mappedColorValue; // You can adjust this based on your needs

  float interpolatedColor = linearInterpolation(red, blue, interpolationValue);

  // Set the fill color using the interpolated color
  float hue = map(interpolatedColor, 0, 255, 360, 0);
  fill(hue, 100, 100, 150);

  // Draw random circles around the click position
  int numCircles = (int) random(5, 15);
  for (int i = 0; i < numCircles; i++) {
    float offsetX = random(-size, size);
    float offsetY = random(-size, size);
    ellipse(x + offsetX, y + offsetY, size, size);
  }
}

public float linearInterpolation(float start, float end, float normalizedValue) {
    return start + (end - start) * normalizedValue;
}

public float sinInterpolation(float start, float end, float normalizedValue) {
    return start + (end - start) * (1 - (float)Math.cos(normalizedValue * Math.PI)) / 2;
}

void clearCanvas() {
  background(255); // Reset the canvas to white
}