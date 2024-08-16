// dance pad
// 28 JAN 2018

// define pins
#define ARROW_UP 14
#define ARROW_DOWN 12
#define ARROW_LEFT 10
#define ARROW_RIGHT 16
#define ARROW_UR 17
#define ARROW_UL 9
#define ARROW_DL 11
#define ARROW_DR 15

#define MSDELAY 100

bool up_pressed = 0;
bool up_pressed_old = 0;
bool down_pressed = 0;
bool down_pressed_old = 0;
bool left_pressed = 0;
bool left_pressed_old = 0;
bool right_pressed = 0;
bool right_pressed_old = 0;
bool ur_pressed = 0;
bool ur_pressed_old = 0;
bool ul_pressed = 0;
bool ul_pressed_old = 0;
bool dl_pressed = 0;
bool dl_pressed_old = 0;
bool dr_pressed = 0;
bool dr_pressed_old = 0;

unsigned long int up_next = 0;
unsigned long int down_next = 0;
unsigned long int left_next = 0;
unsigned long int right_next = 0;
unsigned long int ur_next = 0;
unsigned long int ul_next = 0;
unsigned long int dl_next = 0;
unsigned long int dr_next = 0;
unsigned long int mstime = 0;

void setup()
{
  pinMode(ARROW_UP,INPUT);
  pinMode(ARROW_DOWN,INPUT);
  pinMode(ARROW_LEFT,INPUT);
  pinMode(ARROW_RIGHT,INPUT);
  pinMode(ARROW_UR,INPUT);
  pinMode(ARROW_UL,INPUT);
  pinMode(ARROW_DL,INPUT);
  pinMode(ARROW_DR,INPUT);
  Serial.begin(9600);
}

void loop()
{
  mstime = millis();

  if (mstime > up_next)
  {
    up_pressed = digitalRead(ARROW_UP);
    if (up_pressed != up_pressed_old)
    {
      if (up_pressed == HIGH) {
        Serial.write('w'); // pressed
      } else {
        Serial.write('W'); // released
      }
      up_pressed_old = up_pressed;
      up_next = mstime + MSDELAY;
    }
  }

  if (mstime > down_next)
  {
    down_pressed = digitalRead(ARROW_DOWN);
    if (down_pressed != down_pressed_old)
    {
      if (down_pressed == HIGH) {
        Serial.write('s');
      } else {
        Serial.write('S');
      }
      down_pressed_old = down_pressed;
      down_next = mstime + MSDELAY;
    }
  }

  if (mstime > left_next)
  {
    left_pressed = digitalRead(ARROW_LEFT);
    if (left_pressed != left_pressed_old)
    {
      if (left_pressed == HIGH) {
        Serial.write('a');
      } else {
        Serial.write('A');
      }
      left_pressed_old = left_pressed;
      left_next = mstime + MSDELAY;
    }
  }

  if (mstime > right_next)
  {
    right_pressed = digitalRead(ARROW_RIGHT);
    if (right_pressed != right_pressed_old)
    {
      if (right_pressed == HIGH) {
        Serial.write('d');
      } else {
        Serial.write('D');
      }
      right_pressed_old = right_pressed;
      right_next = mstime + MSDELAY;
    }
  }

  if (mstime > ur_next)
  {
    ur_pressed = digitalRead(ARROW_UR);
    if (ur_pressed != ur_pressed_old)
    {
      if (ur_pressed == HIGH) {
        Serial.write('e');
      } else {
        Serial.write('E');
      }
      ur_pressed_old = ur_pressed;
      ur_next = mstime + MSDELAY;
    }
  }

  if (mstime > ul_next)
  {
    ul_pressed = digitalRead(ARROW_UL);
    if (ul_pressed != ul_pressed_old)
    {
      if (ul_pressed == HIGH) {
        Serial.write('q');
      } else {
        Serial.write('Q');
      }
      ul_pressed_old = ul_pressed;
      ul_next = mstime + MSDELAY;
    }
  }

  if (mstime > dl_next)
  {
    dl_pressed = digitalRead(ARROW_DL);
    if (dl_pressed != dl_pressed_old)
    {
      if (dl_pressed == HIGH) {
        Serial.write('z');
      } else {
        Serial.write('Z');
      }
      dl_pressed_old = dl_pressed;
      dl_next = mstime + MSDELAY;
    }
  }

  if (mstime > dr_next)
  {
    dr_pressed = digitalRead(ARROW_DR);
    if (dr_pressed != dr_pressed_old)
    {
      if (dr_pressed == HIGH) {
        Serial.write('r');
      } else {
        Serial.write('R');
      }
      dr_pressed_old = dr_pressed;
      dr_next = mstime + MSDELAY;
    }
  }

}
