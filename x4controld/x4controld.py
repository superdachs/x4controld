import serial
import time

ser = serial.Serial('/dev/ttyUSB1', 9600)

# main loop
terminate = False
while not terminate:
    print('running...')
    ser.write(b"000000Hello from docker!\n")
    time.sleep(1)
