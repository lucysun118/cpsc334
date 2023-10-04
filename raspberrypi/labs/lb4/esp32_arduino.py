import serial

ser = serial.Serial('/dev/ttyUSB0')  # open serial port

while True:
	receivedString = ser.readline()[:-2]
	receivedString = str(receivedString,'utf-8')
	print(receivedString)
