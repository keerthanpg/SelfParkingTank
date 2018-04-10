import serial 
import syslog
import time
import serial
import argparse
import cv2
import numpy as np




#The following line is for serial over GPIO
port = '/dev/ttyACM0' # note I'm using Mac OS-X

ard = serial.Serial(port,9600,timeout=5)
time.sleep(2) # wait for Arduino

def sendtoard():
    while (1):
    # Serial write section
        #name = input("What's your name? ")
        ard.flush()
        #print("Sending1")

        val1 = int(500)
        val2 = int(500)
        formatted_send=str(format(int(val1), '03d')+format(int(val2), '03d'));
        #print ("Python value sent: " + format(int(val1), '03d')+format(int(val2), '03d'))
        
        #print(formatted_send)
        #print(type(formatted_send))
        #val2x=val2x.encode('utf-8')
        #val2y=val2y.encode('utf-8')
        #print("Sending")
        #ard.write(formatted_send.encode('utf-8'))
        ard.write((str(val1)+str(val2)).encode('utf-8'))
        #ard.write(','.encode('utf-8'))
        #ard.write(val2y)
        #ard.write('_'.encode('utf-8'))
        time.sleep(1.5) # I shortened this to match the new value in your Arduino code

        # Serial read section
        msg = ard.read(ard.inWaiting()) # read all characters in buffer
        
        #print ("Message from arduino: ")
        msg=msg.decode("utf-8") 
        print (msg)
        
    else:
        print ("Exiting")
    exit()


if __name__ == "__main__":
    sendtoard()

