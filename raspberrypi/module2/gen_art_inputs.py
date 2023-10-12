import pygame
import random
import math
import serial

ser = serial.Serial('/dev/ttyUSB0')  # open serial port

# Initialize Pygame
pygame.init()

# Screen dimensions
screen_width = 800
screen_height = 600

# Colors
pastel_colors = [(255, 204, 204), (255, 229, 204), (204, 255, 204), (204, 204, 255), (255, 204, 255)]
white = (255, 255, 255)
black = (0, 0, 0)

# Create a Pygame window
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("Generative Art: Moving Shapes")

# Define a class for shapes (circles and hexagons)
class Shape:
    def __init__(self, x, y, radius, color, shape_type, transparency, fade_speed):
        self.x = x
        self.y = y
        self.radius = radius
        self.color = color
        self.shape_type = shape_type
        self.transparency = transparency
        self.fade_speed = fade_speed

    def draw(self):
        if self.transparency < 0:
            self.transparency = 0
        if self.shape_type == "circle":
            color_with_alpha = self.color + (self.transparency,)
            pygame.draw.circle(screen, color_with_alpha, (self.x, self.y), self.radius)
        elif self.shape_type == "hexagon":
            angle = 0
            hexagon_points = []
            for _ in range(6):
                x = self.x + self.radius * math.cos(angle)
                y = self.y + self.radius * math.sin(angle)
                hexagon_points.append((x, y))
                angle += (2 * math.pi) / 6
            color_with_alpha = self.color + (self.transparency,)
            pygame.draw.polygon(screen, color_with_alpha, hexagon_points)

    def fade_in(self):
        self.transparency += self.fade_speed

    def fade_out(self):
        self.transparency -= self.fade_speed

# Create a list to store shapes
shapes = []

# Initialize shape movement variables
shape_speed = 5
x_velocity = 0
y_velocity = 0

# Initialize the pause flag
paused = False

# Main loop
running = True
clock = pygame.time.Clock()

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    
    receivedString = ser.readline()[:-2]
    receivedString = str(receivedString,'utf-8')

    # Handle user input for shape movement when not paused
    if not paused:
        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT] or receivedString == 'COMMAND_LEFT':
            x_velocity = -shape_speed
        elif keys[pygame.K_RIGHT] or receivedString == 'COMMAND_RIGHT':
            x_velocity = shape_speed
        else:
            x_velocity = 0

        if keys[pygame.K_UP] or receivedString == 'COMMAND_UP':
            y_velocity = -shape_speed
        elif keys[pygame.K_DOWN]  or receivedString == 'COMMAND_DOWN':
            y_velocity = shape_speed
        else:
            y_velocity = 0

    # Toggle pause with the button
    if keys[pygame.K_SPACE] or receivedString == 'BUTTON_PRESSED':
        paused = not paused

    # close program with the switch
    if receivedString == 'SWITCH_OFF':
        pygame.quit()

    # Generate random shapes within the screen dimensions when not paused
    if not paused:
        x = random.randint(0, screen_width)
        y = random.randint(0, screen_height)
        radius = random.randint(10, 50)
        color = random.choice(pastel_colors)
        shape_type = random.choice(["circle", "hexagon"])
        transparency = 0
        fade_speed = random.uniform(0.005, 0.02)
        shape = Shape(x, y, radius, color, shape_type, transparency, fade_speed)
        shapes.append(shape)

    # Update shape positions based on user input when not paused
    if not paused:
        for shape in shapes:
            shape.x += x_velocity
            shape.y += y_velocity

    # Remove shapes that are out of the screen to save memory
    shapes = [shape for shape in shapes if 0 <= shape.x <= screen_width and 0 <= shape.y <= screen_height]

    # Clear the screen
    screen.fill(white)

    # Draw the shapes and apply fade in/fade out effect
    for shape in shapes:
        shape.fade_in()
        shape.fade_out()
        shape.draw()

    # Update the screen
    pygame.display.flip()
    clock.tick(30)

# Quit Pygame
pygame.quit()
