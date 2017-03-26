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
  rgb_fade(100);
  digitalWrite(13,! digitalRead(13));
}

void rgb_fade(int idelay) { //The Hue value will vary from 0 to 360, which represents degrees in the color wheel
  for(int hue=0;hue<360;hue++) {
    setLedColorHSV(hue,1,1); //We are using Saturation and Value constant at 1
    delay(idelay);
  }
}

//Convert a given HSV (Hue Saturation Value) to RGB(Red Green Blue) and set the led to the color
//  h is hue value, integer between 0 and 360
//  s is saturation value, double between 0 and 1
//  v is value, double between 0 and 1
//http://splinter.com.au/blog/?p=29
void setLedColorHSV(int h, double s, double v) { //this is the algorithm to convert from RGB to HSV
  double r=0;
  double g=0;
  double b=0;

  double hf=h/60.0;

  int i=(int)floor(h/60.0);
  double f = h/60.0 - i;
  double pv = v * (1 - s);
  double qv = v * (1 - s*f);
  double tv = v * (1 - s * (1 - f));

  switch (i) {
  case 0: //rojo dominante
    r = v;
    g = tv;
    b = pv;
    break;
  case 1: //verde
    r = qv;
    g = v;
    b = pv;
    break;
  case 2:
    r = pv;
    g = v;
    b = tv;
    break;
  case 3: //azul
    r = pv;
    g = qv;
    b = v;
    break;
  case 4:
    r = tv;
    g = pv;
    b = v;
    break;
  case 5: //rojo
    r = v;
    g = pv;
    b = qv;
    break;
  }

  int red=constrain((int)255*r,0,255);
  int green=constrain((int)255*g,0,255);
  int blue=constrain((int)255*b,0,255);

  one_color_all(red,green,blue);
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
