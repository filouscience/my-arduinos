#include <Arduino.h>
#include <TM1637Display.h>
#include <hp_BH1750.h>

#define BUTTON_PIN 2
// display pins:
#define CLK 7
#define DIO 6
// sensor (standard Arduino I2C bus) pins:
//  A4 --> SDA
//  A5 --> SCL

bool button_down;
bool button_down_old;

TM1637Display myDisplay(CLK,DIO);
hp_BH1750 mySensor;

void setup() {
  button_down = false;
  button_down_old = false;
  Serial.begin(9600);

  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(LED_BUILTIN,OUTPUT);

  myDisplay.setBrightness(4); // from 0 to 7
  myDisplay.clear();

  if (!mySensor.begin(BH1750_TO_GROUND)) // ADDR pin not connected (or to GND)
  {
    Serial.println("No sensor!");
    uint8_t data[] = {64, 121, 80, 80}; // -Err       //     A          A = 1
    myDisplay.setSegments(data);                      //    ---         B = 2
    while (true) {};                                  // F |   | B      C = 4
  } else {                                            //   - G -        D = 8
    Serial.println("Ready");                          // E |   | C      E = 16
    uint8_t data[] = {64, 64, 64, 64}; // ----        //    ---         F = 32
    myDisplay.setSegments(data);                      //     D          G = 64
  }
}

void loop() {
  button_down = (!digitalRead(BUTTON_PIN));
  if (button_down != button_down_old)
  {
    if (button_down == true) {
      digitalWrite(LED_BUILTIN,HIGH);
    } else {
      digitalWrite(LED_BUILTIN,LOW);
      mySensor.adjustSettings(90, true);  // force pre-shot
      mySensor.start();                   // starts an actual measurement
      float lux = mySensor.getLux();      // blocking readout (waiting for the measurement to finish)

      float ev;
      if (lux > 0) {
        ev = log(lux/2.5) / log(2);       // illuminance: E[lx] = 2^ev * 2.5
        //ev = log(lux) / log(2) + 3;       // luminance: L[cd/m^2] = 2^(ev - 3)
        int ev_times_10 = round(ev*10);
        myDisplay.showNumberDecEx(ev_times_10, 32, false); // dots bitmask: 128 64 32 16
      } else {
        ev = -999;
        myDisplay.showNumberDecEx(ev, 0, false);
      }
      Serial.println(ev);
    }
    button_down_old = button_down;
  }

}
