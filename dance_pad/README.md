# Dance Pad
An Arduino-based DIY dance pad to play StepMania (DDR).
The Arduino part is very simple: just 8 pins for "buttons", with external *pull-down* resistors.
In fact only 4 buttons (for the main directions arrows) are necessary, while the diagonal ones can be mapped to anything else (like Select) so that you can control the game entirely without keyboard/mouse.
The mechanical part proved to be the challenging one.

### Arduino code
`dance_pad.ino`
- Initiate pins.
- Start serial connection.
- Send code over the serial connection whenever a button is pressed or released. As the "buttons" are not perfect, set a delay `MSDELAY` of 100 ms to check again, whether the button status has changed.

Alternatively, instead of the external *pull-down* resistors, one can exploit the internal *pull-up* resistors. In that case change the `pinMode` and invert the `HIGH`/`LOW` logic
```
-pinMode(ARROW_UP,INPUT);
+pinMode(ARROW_UP,INPUT_PULLUP);

-up_pressed = digitalRead(ARROW_UP);
+up_pressed = !digitalRead(ARROW_UP);
```
for all buttons.

### Keyboard Emulator code
`dpad_kbd_emu.cpp`
A Windows console application that listens to the specified serial port and sends keyboard input corresponding to the received code.

I read somewhere that the Arduino board's firmware can be updated (or hacked) so that it can send keyboard inputs over the USB cable itself.
That would eliminate the need for the emulator. I didn't go down that path.

### The pad
- two hard cardboards 95x85 cm
- foam polyethylen isolation mat, 3 mm thick
- tinfoil (button contacts)
- copper strip (flat wires), 5 m
- duct tape
- velcro tape (holds the two boards together, can be opened)

Sadly, after some time, the buttons degraded due to wear. The most common issue was that he buttons released slowly or didn't release at all, which made the game unplayable.
I ended up quitting this design and buying a commercial dance pad. :sweat_smile: