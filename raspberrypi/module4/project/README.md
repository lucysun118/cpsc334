# ‘The Toonish Dauber’: ESP32-Processing Powered Interactive Kinetic Art

## Overview

- An ESP32-Processing powered piece of interactive kinetic art relying on user interaction with a multi-state button, a photoresistor, and 2 touch sensors.
- Interacting with these will cause the ‘Toonish Dauber’ to react in some way.
- The ‘Toonish Dauber’ itself consists of two servo motors, a stepper motor, and a vibration motor.

## Description

- Upon running, a blank canvas appears on the screen.

### Servo Motors

- Attached to each servo motor is a chopstick with a stuffed latex glove (the toon hand).
    - The hands will rotate into each other relatively quickly, simulating a clapping motion.
    - When the hands collide, some combination of colors of paint will appear on the canvas.
        - The colors are determined by the amount of light recorded by the **photoresistor**.
            - The larger the value = the warmer the colors
            - The smaller the value = the colder the colors

### Stepper Motor

- Between the servo motors is a circle with a smiley face on it.
    - A **stepper motor** beneath the circle rotates it.

### Paint Splatter

- The x-and-y positioning of a paint splatter is determined by 2 features:
    - The positioning of the **stepper motor** in rotation determines the x-position of a splatter
    - The y-position is determined by Perlin noise
- The user can clear the canvas by holding one of the **touch sensors**
    - After a brief delay, a **vibration motor** in the center of the toon eyes will activate

## Creative Process

### Why?

- We wanted something on the more ‘artsy’ side while still being thoroughly interactive.
- We settled on the ‘Toonish Dauber’ after deliberating over the idea of illustrating paint splatter and immersing the user in the act of creating paint splatter.
    - The ‘Toonish’ theme derived from a video game published in 2010, called ‘Epic Mickey.’ In this game, you play as Mickey Mouse wielding a paintbrush in an action-adventure platformer.

### Feature Richness

- Emphasizing the user experience by implementing many different ways (photoresistor, touch sensor, multi-state button) the user has to interact with the ‘Toonish Dauber.’
- The 3 aforementioned methods of interaction also include more depth in terms of features.
    - This is based on:
        - Time, as in how long the user interacts with a given part.
        - When the user interacts with a given part, as in what particular state according to the button.

### Challenges

#### Implementing the Stepper Motor:

- Struggled in deriving a reason for including a stepper motor. Wanted a practical application, but one that would be exciting to experience for the user. After deliberating over how we wanted the paint splatter to appear on the canvas, we determined that the stepper motor could manipulate the positions of the splats.

#### Implementing the Servo Motors:

- The clapping motion itself was quite straightforward. Our struggle with the server motors was due to an attempt to demonstrate ‘wider claps’ and ‘narrow claps.’ The 2nd servo motor seemingly never wanted to move in the opposite direction of the 1st servo motor.
- Struggled with building a solid base for the toon hands to move on. Lots of different types of glue and methods of adhesive were used.

## Repository Link

[Link to GitHub Repository](<https://github.com/lucysun118/cpsc334/tree/master/raspberrypi/module4/project>)
