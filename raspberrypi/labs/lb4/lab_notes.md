<!-- Output copied to clipboard! -->

<!-- Yay, no errors, warnings, or alerts! -->



1. Installed arduino IDE onto laptop
2. Arduino IDE->settings->preferences->additional board manager urls
    1. Copy pasted: <code>[https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json)</code>
3. Tools → boards→ board manager
    2. Esp32 by essif
4. Tools → boards → esp32→ esp32 dev module
5. Tools → port → cu.serial
6. File → examples → esp32 → hall sensor
7. Connecting with PI:
    3. Ssh into via laptop 
    4. Dialout check
    5. Plugged esp32 into pi type A
    6. In terminal: <code>ls /dev/tty*</code>
        1. Found which one was the esp32: <strong>/dev/ttyUSB0</strong>

8. Program w joystick: analog input:
    7. [https://esp32io.com/tutorials/esp32-joystick](https://esp32io.com/tutorials/esp32-joystick) 
    8. Connected joystick via wires to the esp32
    9. Connected esp32 to laptop
    10. Uploaded and compiled the code
    11. Checked out with serial monitor
    12. For the python code, used pyserial to read input from esp32 when it was connected to pi - code in joystick_esp32.py
        2. Very helpful link for reading input from esp32: [https://www.instructables.com/Python-Serial-Port-Communication-Between-PC-and-Ar/](https://www.instructables.com/Python-Serial-Port-Communication-Between-PC-and-Ar/)
            1.   GNU nano 5.4                       esp32_arduino.py                                 
            2. import serial
            3. 
            4. ser = serial.Serial('/dev/ttyUSB0')  # open serial port
            5. 
            6. while True:
            7.         receivedString = ser.readline()[:-2]
            8.         receivedString = str(receivedString,'utf-8')
            9.         print(receivedString)
            10. 
    13. Debugging
        3. [Printing](https://stackoverflow.com/questions/37016946/remove-b-character-do-in-front-of-a-string-literal-in-python-3) out the Serial.println / Serial.write input from the ESP via the input devices without line break and random characters: added the line to the python file before printing it: “receivedString = str(receivedString,'utf-8')”

9. Program with button: digital input
    14. [https://esp32io.com/tutorials/esp32-button](https://esp32io.com/tutorials/esp32-button)
    15. Connected button via wires to esp32
    16. Connected esp32 to laptop
    17. Uploaded and compiled the code
    18. Checked out press and release events with serial monitor
    19. When connected to pi, used the same script as last time - and it worked!
    20. Debugging
        4. Used [wires](https://www.google.com/search?q=gpio21+esp32+devkitc_v4&&tbm=isch&ved=2ahUKEwj1kff_mNuBAxW_OFkFHbZjBaQQ2-cCegQIABAA&oq=gpio21+esp32+devkitc_v4&gs_lcp=CgNpbWcQAzoHCAAQGBCABFCKA1jtPGCzQGgBcAB4AIABVYgB9QaSAQIxM5gBAKABAaoBC2d3cy13aXotaW1nwAEB&sclient=img&ei=qbkcZbWZK7_x5NoPtseVoAo&bih=790&biw=1394&rlz=1C5CHFA_enUS943US943#imgrc=tzEbvxEYgVY9wM) instead of breadboard to connect button to ESP32 using a mapping of pins diagram linked here^
        
10. Program with switch: digital input
    21. [https://esp32io.com/tutorials/esp32-switch](https://esp32io.com/tutorials/esp32-switch) 
    22. Connected switch via wires to esp32
    23. Connected esp32 to laptop
    24. Uploaded and compiled the code
    25. Checked out press and release events with serial monitor
    26. When connected to pi, used the same script as last time - and it worked!
    27. Debugging
        5. Didn’t really run into any problems - just realized that i couldn’t use GPIO17 as suggested by the esp32io.com source because it was already taken up by the joystick
            11. So i just used GPIO16 after consulting the diagram
11. Combining the 3 input devices into one .ino Arduino script:
    28. Just copy and pasted the script into one and flashed to the raspberry pi
        6. Final script combining all 3 inputs is under “final_arduino_joystick_button_switch.ino” in the same directory