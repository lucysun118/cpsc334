import pygame
import random

import serial

ser = serial.Serial('/dev/ttyUSB0')  # open serial port


#baud_rate = 115200  # Match with the ESP32's baud rate

# Initialize Pygame
pygame.init()
screen = pygame.display.set_mode((800, 600))

# Define initial cloud position and other variables
cloud_x = 400
cloud_y = 200
cloud_speed = 2

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False


    receivedString = ser.readline()[:-2]
    receivedString = str(receivedString,'utf-8')

    # Adjust the cloud animation based on input
    cloud_x += esp32_input  # Adjust cloud's x-position based on ESP32 input

    # Generate the cloud animation
    # In this example, we'll just create a simple cloud shape
    screen.fill((135, 206, 235))  # Set the background color to light blue

    # Draw the cloud
    pygame.draw.circle(screen, (255, 255, 255), (cloud_x, cloud_y), 30)
    pygame.draw.circle(screen, (255, 255, 255), (cloud_x + 20, cloud_y), 30)
    pygame.draw.circle(screen, (255, 255, 255), (cloud_x + 40, cloud_y), 30)

    pygame.display.flip()