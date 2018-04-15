import serial 
import syslog
import time
import serial
import argparse
#import numpy as np




#The following line is for serial over GPIO
port = '/dev/ttyACM0' # note I'm using Mac OS-X
ard = serial.Serial(port,9600,timeout=5)
time.sleep(2) # wait for Arduino
f=open('calibration', 'a')
def sendtoard():
    for i in range(2):
    # Serial write section
        #name = input("What's your name? ")
        time.sleep(2)
        for j in range(100, 712, 1):
            ard.flush()            
            val1 = int(j)
            val2 = int(j)
            formatted_send=str(format(int(val1), '03d')+format(int(val2), '03d')+format(','));                   
            ard.write((str(val1)+str(val2)).encode('utf-8'))        
            time.sleep(1) # I shortened this to match the new value in your Arduino code
            # Serial read section
            msg = ard.read(ard.inWaiting()) # read all characters in buffer        
            msg=msg.decode("utf-8") 
            if not msg.isspace():
                print(j)
                print (msg)
                f=open('calibration', 'a')
                f.write('\n')
                f.write(msg)
                f.close()
            time.sleep(0.2)

        
    else:
        print ("Exiting")
    exit()


if __name__ == "__main__":
    sendtoard()

