#define RED 9
#define GREEN 10
#define BLUE 11

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
    digitalWrite(RED,inputValue & 1);
    digitalWrite(GREEN,inputValue & 2);
    digitalWrite(BLUE,inputValue & 4);
    delay(inputValue);
    digitalWrite(RED,LOW);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,LOW);
  }
  digitalWrite(13,! digitalRead(13));
}
