# Fluid Simulation Black Box

## Overview

The Fluid Simulation Black Box project is a creative exploration in generative art, combining fluid simulation with user interaction through sensors. The program, built on Processing, incorporates input from a photosensor (light sensor) and a capacitive touch sensor connected to an ESP32 board. The system generates visually appealing fluid simulations influenced by user actions, creating a dynamic and artistic experience.

## Creative Exploration: From Inspiration to Implementation

### Inspiration

The project draws inspiration from the desire to explore generative art and computational aspects of programming. The artistic focus involves intentional choices in color and visual effects based on user input from sensors. The fluid simulation, influenced by physics principles, is a creative learning experience built upon a reference material on fluid simulation for beginners.

### Implementation

The system consists of a hardware component powered by a 5V battery, featuring an ESP32 and sensor circuitry. This hardware communicates wirelessly over UDP to a remote laptop running the Processing program. The "unseen effect" is incorporated in two ways: built-in timed events affecting visual effects and hiding the hardware within a "black box."

## The Enclosure

The design of the enclosure enhances the "unseen effect" concept. Users interact with the system by placing their finger into the wireless box, manipulating light values for the photosensor and unknowingly changing capacitive touch sensor values. The hidden touch sensor contributes to the fluid simulation's speed, creating a connection between user actions and on-screen effects.

## The Code

The unseen effect is further implemented in the code through visual effects not directly correlated with user inputs. The program's background changes to blue when the touch sensor is held for at least 5 seconds, and the light value is at least 100. This hidden effect encourages user exploration and self-discovery, adding an element of surprise to the interaction.

# Challenges / Resolutions

## Challenges

1. **Hidden Effect Implementation:** Deciding how to implement the "hidden effect" was an initial challenge. The solution involved a "black box" approach, concealing both hardware and code aspects to create an engaging user experience.

2. **Wireless Communication:** Implementing wireless communication for sensor data over UDP in Processing posed challenges. Guidance from peers (Richard and Malia) and utilizing the UDP module in Processing resolved this issue.

## Resolutions

1. **Enclosure Design:** The enclosure design became a key element in realizing the hidden effect. The user's exploration within the box adds an extra layer of interaction and curiosity.

2. **Code Implementation:** The interpretation of a hidden effect as not immediately obvious to the user led to creative coding solutions. Encouraging exploration and interaction became a central theme in resolving this challenge.

# Getting Started

To experience the Fluid Simulation Black Box, follow these steps:

1. Clone the repository.
2. Set up the hardware components according to the provided specifications.
3. Run the Processing program on your laptop.
4. Interact with the system by moving your finger within the box, exploring the impact on the fluid simulation.

# Acknowledgments

Special thanks to Richard and Malia for their invaluable assistance and inspiration in navigating the challenges associated with wireless communication and the UDP module in Processing.