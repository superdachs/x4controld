import serial
import time
import os
import logging

log = logging.getLogger(__name__)

port = os.getenv('SERIAL_PORT')

ser = serial.Serial(port, 9600)

displays = {
    0: {
        0: {
            0: "1234",
            8: "test",
        },
    },
    1: {
        2: {
            3: "Hello World!",
        },
    },
}

def update_displays():
    for display, lines in displays.items():
        for line, positions in lines.items():
            for pos, text in positions.items():
                t = f"{display:02d}{line:02d}{pos:02d}{text}\n"
                log.debug(t)
                ser.write(t.encode('UTF-8'))
                time.sleep(1)

# main loop
terminate = False
while not terminate:
    update_displays()






