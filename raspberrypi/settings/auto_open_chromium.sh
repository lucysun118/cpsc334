#!/bin/bash
#update git
git pull

# Your HTML file path
DIR="/home/student334/cpsc334/raspberrypi/dev/module1/task2"
FILENAME="genart.html"

# Command to start Chromium in incognito mode and full-screen
chromium_command="/usr/bin/chromium-browser --incognito --start-fullscreen file://$DIR/$FILENAME"

# Check if Chromium is already running and kill it
pkill chromium-browser

# Start Chromium
$chromium_command
