# HeroJR-BluetoothAdapter
Heathkit Hero Jr Robot ESP32 Based Bluetooth serial bridge.

Using Arduino IDE 1.8.14 with ESP 1.0.4 Library.

Parts needed.

Qty 1 ESP32 breakout module. I'm using a ESP32 Devkitv1.

Qty 1 TTL to RS232 adapter. Any module that has rx/tx should work.

These parts were chosen because I had them laying around already.

If powering off the +12 from the robot, you will need to step it down to +5 for the esp32 module.
I'm using a LM2596 based buck converter.

Sketch defaults to powering down the module if no connection is made within 5 minutes of powering on.

This and the Bluetooth name can be changed in the sketch.

I used the ESP32 1.0.4 arduino library, because 1.0.5 is broken for bluetooth serial.


My robot came without the remote board so I took this opportunity to add a generic remote and bluetooth serial in the same place the remote control board would go.

I also wanted this to be a non destructive and reversable mod, so I printed up a little box for my boards.

![alt text](https://github.com/dabonetn/HeroJR-BluetoothAdapter/blob/main/photos/Remote-BT.jpg?raw=true)


The remote board plugs into the remote header on the Jr's motherboard, and powers the relays straight from the +12.
I also send the +12 to the buck converter and get +5 to power the esp32 and also to send the +5 remote control signals back to the robot.

The serial port is removable for the esp32 and from the rs232 converter board to be able to reprogram the esp32. If the serial converter is connected, the esp32 won't program, since the usb port also shares rx0/tx0. You also cannot use the Hero Jr serial port if the rs232 converter board is connected and 
powered. Eventually I'll add a relay or something to disconnect the circuit from the robot when not in use.

To attach to the serial port wires, I ended up just using a long pinned female header that comes with my esp8266 units I buy, and just wedged it into the connector.
I then have 2 male pin headers with tx/rx on them that I plug into the female side. Green and red wires are the serial pins.

![alt text](https://github.com/dabonetn/HeroJR-BluetoothAdapter/blob/main/photos/FemaleHeader.JPG?raw=true)

Here's what it looks like plugged in.

![alt text](https://github.com/dabonetn/HeroJR-BluetoothAdapter/blob/main/photos/SerialPiggyback.JPG?raw=true)


So not a wire is touched or modified. These things are so old and rare, I didn't want to change a thing.

