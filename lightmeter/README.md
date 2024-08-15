# Arduino lightmeter

We all know the *sunny 16* rule. At full sunlight with sharp shadows, for film speed e.g. `100 ISO` one sets `f/16` aperture, and exposure time (shutter speed) reciprocal to ISO, i.e. `1/100 s`. But what if the situation is not so straightforward. How much light do you have at home?

The quantity to watch here is the **exposure value** https://en.wikipedia.org/wiki/Exposure_value. The *sunny 16* settings `N = 16` and `t = 1/100 s` yield required exposure value at 100 ISO of 
```math
EV_{100} = \log_2(N^2/t) = \log_2(16\cdot16\cdot100) \approx 14.64
```
which is close enough to `EV = 15`. Since the *sunny 16* rule holds, such is indeed roughly the EV on a sunny day. If e.g. `EV = 6` is measured, it means that we need to adjust the aperture and/or shutter speed by the total of 9 stops, compared to the *sunny 16* situation.

Our Arduino lightmeter will take care of the EV measurement. While automatic cameras read the **luminance** `L [cd/m^2]`: the amount of light reflected by the scene directly into the camera, our lightmeter measures the **illuminance** `E [lx]`: the amount of light *illuminating* the object or scene. This is actually closer to the original application of the *sunny 16* rule. The exposure value is then calculated:
```math
EV_{100} = \log_2(L/2.5)
```

### Operation
Upon button release, the exposure value is measured and shown on the display.

### Components
Hardware:
- Arduiono Uno board
- Light-Sensor BH1750
- TM1637 4-digit 7-segment display
- button (internal *pull-up* resistors available on digital input pins)

The project depends on libraries:
- https://github.com/avishorp/TM1637 for the control of TM1637 display
- https://github.com/Starmbi/hp_BH1750 for the operation of Light-Sensor BH1750