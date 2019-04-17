import machine
import time
from lib import i2cdisplay_2866 as displ
from lib import mcp

terminate = False
i2c = machine.I2C(scl=machine.Pin(5), sda=machine.Pin(4), freq=100000)

display1 = displ.I2cLcd(i2c=i2c, i2c_addr=0x26, num_lines=4, num_columns=20)
display2 = displ.I2cLcd(i2c=i2c, i2c_addr=0x27, num_lines=4, num_columns=20)

io1 = mcp.MCP23017()

display1.putstr("Hallo 1")
display2.putstr("Hallo 2")

ledPin = 0

io1.setup(ledPin, mcp.OUT)
io1vals = {}
io1vals[ledPin] = True

io1.output_pins(io1vals)


def loop():
    oldVals1 = b""
    oldVals2 = b""
    while not terminate:
        # devs = i2c.scan()
        # print("running...")
        # for d in devs:
        #    print('found device: ', d, ' (', hex(d), ')')
        io1vals[ledPin] = not io1vals[ledPin]
        io1.output_pins(io1vals)
        # reads the values from the attinys
        vals1 = i2c.readfrom(50, 9)
        vals2 = i2c.readfrom(51, 9)
        if vals2.decode() != oldVals2.decode():
            oldVals2 = vals2
            print(vals2)


def main():
    loop()


main()
