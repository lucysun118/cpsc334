import tkinter as tk
from tkinter import Canvas, Scale
import random

# Constants
MAX_HEIGHT = 100

# Function to update the plant based on the water level
def update_plant(event):
    water_level = water_scale.get()
    plant_height = water_level if water_level > 50 else 0

    # Clear the canvas
    canvas.delete("leaves")

    # Generate random green ovals as plant leaves
    for _ in range(plant_height):
        x = random.randint(0, 400)
        y = random.randint(10, 150)
        width = random.randint(5, 15)
        height = random.randint(10, 30)
        canvas.create_oval(x, y, x + width, y + height, fill="green", tags="leaves")


# Create the main window
root = tk.Tk()
root.title("Generative Leaf Art")

# Create a canvas for the plant and ground
canvas = Canvas(root, width=400, height=200, bg="light blue")
canvas.pack()

# Create the ground
canvas.create_rectangle(0, 150, 400, 200, fill="brown")

# Create a water level slider
water_scale = Scale(root, from_=0, to=MAX_HEIGHT, orient="horizontal", label="Water Level")
water_scale.pack()

# Bind the update_plant function to the button release event of the scale
water_scale.bind("<ButtonRelease-1>", update_plant)

# Main loop
root.mainloop()


