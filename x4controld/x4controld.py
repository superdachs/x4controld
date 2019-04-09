import serial
import time
import datetime
import os
import logging

port = os.getenv('SERIAL_PORT')
print(port)

ser = serial.Serial(port, 9600)

# main loop
terminate = False
while not terminate:
    print('running...')
    ser.write(f"000000{str(datetime.datetime.now())}\n".encode('UTF-8'))
    time.sleep(1)
