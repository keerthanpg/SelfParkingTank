import serial
import time

ser = serial.Serial(
	port='/dev/ttyACM0',
	baudrate=115200,
	timeout=0.1
)

ser.write(b'\r\r')

def getpos():
	time.sleep(0.5)
	ser.write(b'\r')	
	res=ser.read(25)	
	print(res)
	

while True:
	getpos()
	ser.flushInput()
	ser.flushOutput()

	