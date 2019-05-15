# Type 6 Sun-to-USB Adapter using Arduino Micro Compatible

I am totally a UNIX nerd and one day I decided to get myself an old Sun keybard. Being from Sweden I needed one with a Swedish layout. I was initially looking for a Type 5, but the only one I could find was a Type 6. They do come in a variant with a USB connection, but this one had the old-style proprietary Mini-DIN connection similar to the Type 5.

I didn't want to pass the opportunity up though. Who knows when I would find a Swedish layout Type 5, right? So I bought it and started building myself a Mini-DIN to USB adapter. It is based on the work of [Ben Rockwood][benr] and [Sven Guenther][sven] by forking from the latter. Check those repos out, I owe it all to them.

# Building the hardware

You will require:

* Board based on the Atmel 32u4 chip, thus being to act as a HID device (I use an Adafruit ItsyBitsy 32u4 5V 16MHz)
* A USB Type A to USB Micro B cable to attach the board to your computer
* A Mini-DIN 8a female connector, the kind built for PCB attachment
* A Sun Mini-DIN variant Type 6 Keyboard, duh!

The Sun keyboard uses a Mini-DIN 8a connector.  Thanks to Alexander Kurz you can find the [Sun Type 4/5/6 Pinout][keyboard pin-outs] on kbdbabel.org:

![Keyboard Pinout][sun 456 din]

You'll notice that they keyboard has its own Vcc +5V & Ground as well as a "from keyboard" and "to keyboard".  You also have 3 more wires providing Vcc +5V & Ground plus a single read line for the mouse! We'll ignore the mouse for now.

Lets connect to our board! I use the following pin mapping:  

| Mini-DIN       | Itsybitsy 32u4  |
|----------------|-----------------|
| Pin 2 (White)  | GND             |
| Pin 8 (Red)    | +5V             |
| Pin 6 (Yellow) | D10 (Serial RX) |
| Pin 5 (Green)  | D11 (Serial TX) |

I bought my DIN connector from the swedish store [Electrokit](https://www.electrokit.com/). I was unsure of the pinout on the mounting end of the connector, so I put my multimeter in diode mode and came up with the following pinout:

![Mini-DIN PCB Connection Pinout](doc/pinout.png)

Wire it up and, assuming the pins on your board matches my setup, just do

```
cd src/ && make && make upload
```

from the project root.

# How Sun Keyboards Work

It's actually gloriously simple, thanks to the cleverness of the original Sun engineers!

The Sun keyboard is actually a 1200 baud serial device.  Seriuosly.  That sounds odd but is actually wonderful because the Arduino can easily interface with it using the [Serial Library](https://www.arduino.cc/en/Reference/Serial).

There is a bug in the original code from both [benr] and [sven] regarding the values received from the keyboard on "key relese".

## Original Interpretation

By using the Arduino Serial Monitor and a simple sketch to listen, we can see what the keyboard is sending.  Press "A" on the keyboard and we get the following (decimal) output to the monitor:

```
77
-51
127
```

After some playing around, you'll realize that the 3 values sent by the keyboard have 3 meanings, representing different actions:

1. **77**: 77 is the code representing the "A" key being pressed down
2. **-51**: This indicates the key being released (key up), but which key?  Add this value to 128 to determine the key!  128-51=77, so the "A" key is being released.  _Clever right!?!_
3. **127**: This code is sent when no other key is being pressed, it is the "all clear" message.

You can verify this all by pressing and holding "A", then pressing and holding "B", then "C", and then release each key one at a time.  You'll clearly see the key downs, key ups, and releases.

## Adjusted Serial Protocol

There is however a nasty little bug hiding on line 37 of the [the original implementation][the nasty bug 1] which taints the above interpretation. As part of the loop that reads from the serial line, in the main code and the [test program source][the nasty bug 2], the following line is used to actually read from the keyboard:

```
char c = sunSerial.read();
```

Looks totally innocent, but notice that the serial read method returns an ```int``` which is stored in a ```char```. On the 8-bit AVR the size of a char is 8 bits, but the size of an ```int``` is 16 bits, thus causing an overflow when assigned to the signed char ```c```.

Reading from the official [specification], the example of the 'A' button in the US Scan Set has in fact a "make code" of 0x42 = 77, but the "break code" (what [benr] calls "key release" or "key up") is 0xCD = 205. If you put that in a signed char it will overflow to 205-2^8 = -51.

If we instead use an ```unsigned char```, or perhaps better, an ```int``` the above protocol still basically works. The only adjustment to make is that if the value read on the serial line is > 127 we know that this is a break code. We then _subtract_ 128 to get the corresponding make code of the key released.

## LED Control & Sending Commands to the Keyboard

Commands can be sent on the serial line to the keyboard.  Because they aren't emitted from the keyboard its harder to discover them through trial-and-error. Contained in the official specification however are the pinouts, the scancodes and, most importantly, the serial commands! 

On page 17 of the [specification] you'll find the serial protocol and the commands you can send:

* **0x01**: Reset
* **0x02**: Bell On
* **0x03**: Bell Off
* **0x0A**: Keyboard Click On
* **0x0B**: Keyboard Click Off
* **0x0E**: LED Command
* **0x0F**: Layout Command

The Bell is simply a loud computer speaker sound.  Normally it should only be used in short bursts (like the one your PC makes when it turns on) by sending 0x02, then delay 100ms, then send 0x03 to turn off.  Once turned on it will make a solid tone until you turn it off.

The Keyboard Click is something you may remember from the old WYSE & HP Terminal days.  When enabled you will get a little "chirp" sound every time you press a key.  It brings back nostalgia for about 10 seconds and then is incredibly annoying.

We're not using the Layout command because it seems the scan codes for both PC & UNIX layouts are the same, so currently no need for this.

Reset command is not used right now.

The LED Command is the important one.  You must send 2 bytes, the first is the LED Command 0x0E and the second is a 4-bit bitmask which determines which of the 4 LED's are on or off:

* **0000**: All off
* **0001**: Numlock
* **0010**: Compose
* **0100**: Scroll
* **1000**: Caps Lock

Serial.write() can only pass a single value, so using 2 in sequence is a bit hit or miss. Instead we can create a 2 byte array, the first element is the LED Command 0x0E and the second is the value of the bitmask. Then we can pass that array to Serial.write() as a single unit.

The effect of this is that you must keep the state of the LEDs in your controller, and therefore re-initialize the LEDs on each load in setup() to a known state.

# Modifications to the original source

My version is a bit different, both regarding the fixes to the serial protocol and also in that I want to support a wider range of USB-HID codes. I'm from Sweden and need to have support for the Swedish keyboard layout.

# What doesn't work (yet)

* Scroll Lock and Compose don't function by design; there is no practical use for them and don't see a reason to add the 10 lines of logic
* Pause and Print Screen does not have any function on macos
* Power Button is ignored, but could be easily Implemented
* The passthrough mouse is currenlty not implemenmted and may be added in the future

# Thanks to

* Ben Rockwood for [the original project]
* Sven Guenther for [introducing the HID-Project and complex actions][the later project]
* Alexander Kurz for the [keyboard pin-outs]
* Adafruit for the [itsybitsy 32u4], an awesome board
* [Arduino.cc](https://www.arduino.cc/) for, you know, everything

<!--- references -->
[benr]: https://github.com/benr
[the original project]: https://github.com/benr/SunType5_ArduinoAdapter
[the nasty bug 1]: https://github.com/benr/SunType5_ArduinoAdapter/blob/ce8563530b73615de718b7d3bd865f4cd5b1e1c2/SunKeyboard-to-USB/SunKeyboard-to-USB.ino
[the nasty bug 2]: https://github.com/benr/SunType5_ArduinoAdapter/blob/20bdba3d11223bc0ef12191bc31469b4e79e1b7a/SunKeyboard-Test/SunKeyboard-Test.ino

[sven]: https://github.com/0x6e3078
[the later project]: https://github.com/0x6e3078/SunType5_ArduinoAdapter

[specification]: http://sparc.org/wp-content/uploads/2014/01/KBD.pdf.gz
[keyboard pin-outs]: http://www.kbdbabel.org/conn/index.html
[sun 456 din]: http://www.kbdbabel.org/conn/kbd_connector_sun456.png

[itsybitsy 32u4]: https://www.adafruit.com/product/3677
