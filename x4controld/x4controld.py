import serial
import time
import os
import logging

log = logging.getLogger(__name__)

port = os.getenv('SERIAL_PORT')

ser = serial.Serial(port, 9600)

displays_changed = False
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

leds_changed = False
leds = {
    0: {
        0: 1,
        1: 0,
        2: 1,
        3: 1,
    },
}


def update_displays():
    for display, lines in displays.items():
        for line, positions in lines.items():
            for pos, text in positions.items():
                t = f"LCD{display:02d}{line:02d}{pos:02d}{text}\n"
                log.debug(t)
                ser.write(t.encode('UTF-8'))
                time.sleep(1)


def update_leds():
    for dev, dleds in leds.items():
        for led, value in dleds.items():
            t = f"LED{dev:02d}{led:02d}{value:02d}\n"
            log.debug(t)
            ser.write(t.encode('UTF-8'))
            time.sleep(1)


# main loop
terminate = False
while not terminate:
    update_displays()
    update_leds()
