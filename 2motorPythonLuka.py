import serial 
import syslog
import time
import serial
import argparse
import sys,tty,termios
import signal 

#The following line is for serial over GPIO
port = '/dev/ttyACM0' # note I'm using Mac OS-X
ard = serial.Serial(port,9600,timeout=5)
time.sleep(2) # wait for Arduino
f=open('calibration', 'a')
cond = 0	# Default value is 0


def sendtoard():
    for i in range(2):
        time.sleep(2)
        
	# Every single digit to each motor should be 3 digits long
	# therefore  Keerthana has initialised the 0 as 100, which
	# explains why -355 in arduino code
	for j in range(100, 611, 1):
	    # Was 712 originally, but range is 510 (-255->+255) therefore 100+510+1_index = 611
            ard.flush()            
            val1 = str( format(int(j), '03d') )
            val2 = str( format(int(j), '03d') )
	
            ard.write((val1+val2).encode('utf-8'))        
            time.sleep(1) # I shortened this to match the new value in your Arduino code
            
	    # Serial read section
            msg = ard.read(ard.inWaiting()) # read all characters in buffer        
            msg=msg.decode("utf-8") 
            if not msg.isspace():
                print(j)
                print (msg)
                f.write('\n')
                f.write(msg)
            time.sleep(0.2)


class _Getch:
    def __call__(self):
            fd = sys.stdin.fileno()
            old_settings = termios.tcgetattr(fd)
            try:
                tty.setraw(sys.stdin.fileno())
                ch = sys.stdin.read(3)
            finally:
                termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
            return ch
def get():
        inkey = _Getch()
        while(1):
                k=inkey()
                if k!='':break
        if k=='\x1b[A':
                #print "up"
		update1, update2 = -30,-30
        elif k=='\x1b[B':
                #print "down"
		update1, update2 = 30, 30
        elif k=='\x1b[C':
                #print "right"
		update1, update2 = -15, 15
        elif k=='\x1b[D':
                #print "left"
		update1, update2 = 15, -15
        else:
                print "not an arrow key!"
	return update1, update2

def main():
	# Default values to set to the wheels as soon as manual override has been called
	ard.flush()            
        value1, value2 = 355,355
        format1, format2 = str(value1), str(value2)
        ard.write((format1+format2).encode('utf-8')) 
	# Now proceed to reading the next 10 commands
        for i in range(0,200):
                l,r = get()
		# Same shit as above except with the instruction 
		# to decrement or increment voltage to wheels
		value1 = value1 + l
		value2 = value2 + r
		format1, format2 = str(value1), str(value2)
		ard.write((format1+format2).encode('utf-8')) 
		# Serial read section
            	msg = ard.read(ard.inWaiting()) # read all characters in buffer        
            	msg=msg.decode("utf-8") 
		k = 0
            	if not msg.isspace():
			# So that we who live on -255->255 earth understand
                	print("l:" + str( value2-355) + " r:"+str( value1-355) )
			print (msg)
			f.write('\n')
			f.write(msg)
			#print (msg[0:30])
               		#for j in range(0, 30, 1):
				#if (msg[j] == '\n'):
				#		k = k + 1
				#if (k == 1):
				#	print (msg[0:j])
				#		f.write('\n')
				#	f.write(msg[0:j])
				#if (k > 1):
				#	break


if __name__ == "__main__":

        try:
                sendtoard()
        except KeyboardInterrupt:
                print ('Interrupted')
                main()
        f.close()
