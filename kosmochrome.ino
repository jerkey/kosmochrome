#define MIN_BRIGHT      20
#define MAX_BRIGHT      255
#define RED 9
#define GREEN 10
#define BLUE 11

int ibright = 0;;          //-BRIGHTNESS (0-255)
int idex;             //-LED INDEX (0 to num_leds-1
int thisColor[3];

void setup() {
  Serial.begin(57600);
  setPwmFrequency(9,1); // 9 and 10 are on the same timer
  setPwmFrequency(11,1);
  Serial.println('kosmochrome');
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  Serial.setTimeout(50);
}

void loop() {
  while (Serial.available() > 0) {
    int inputValue = Serial.parseInt();
    Serial.println(inputValue);
  }
  rgb_fade(10);
  digitalWrite(13,! digitalRead(13));
}

void rgb_fade(int idelay) { //-FADE LEDS THROUGH HSV RAINBOW
  ibright++;
  if (ibright >= MAX_BRIGHT) {
    ibright = MIN_BRIGHT;
    idex--;
    if (idex < 0) {
      idex = 2;
    }
  }
  thisColor[idex] = ibright;
  thisColor[(idex + 1) % 3] = MAX_BRIGHT - ibright + MIN_BRIGHT;
  one_color_all(thisColor[0],thisColor[1],thisColor[2]);
  delay(idelay);
}

void one_color_all(int red, int grn, int blu) {
  Serial.print(red);
  Serial.print(", ");
  Serial.print(grn);
  Serial.print(", ");
  Serial.println(blu);
  analogWrite(RED,red);
  analogWrite(GREEN,grn);
  analogWrite(BLUE,blu);
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
