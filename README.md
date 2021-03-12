# HeroJR-BluetoothAdapter
Heathkit Hero Jr Robot ESP32 Based Bluetooth serial bridge.




Quick and dirty esp32 bluetooth to serial bridge for the Heathkit Hero Jr Robot.
Arduino IDE 1.8.14 with ESP 1.0.4 Library.

Parts needed.

Qty 1 ESP32 breakout module. I'm using a ESP32 Devkitv1.

Qty 1 TTL to RS232 adapter. Any module that has rx/tx should work.

If powering off the +12 from the robot, you will need to step it down to +5 for the esp32 module.
I'm using a LM2596 based buck converter.

Sketch defaults to powering down the module if no connection is made within 5 minutes of powering on.
This and the Bluetooth name can be changed in the sketch.

I used the ESP32 1.0.4 arduino library, because 1.0.5 is broken for bluetooth serial.
