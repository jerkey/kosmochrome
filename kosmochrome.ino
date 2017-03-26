#define RED 9
#define GREEN 10
#define BLUE 11

int ibright = 0;;          //-BRIGHTNESS (0-255)
int idex;             //-LED INDEX (0 to num_leds-1
int thisColor[3];

void setup() {
  Serial.begin(57600);
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
  if (ibright >= 255) {
    ibright = 0;
    idex--;
    if (idex < 0) {
      idex = 2;
    }
  }
  thisColor[idex] = ibright;
  thisColor[(idex + 1) % 3] = 255 - ibright;
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
