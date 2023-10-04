import serial

ser = serial.Serial('/dev/ttyUSB0')  # open serial port

while True:
	receivedString = ser.readline()
	print(receivedString)