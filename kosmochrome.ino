#define FET_A A1
#define FET_B 11
#define FET_C 12

void setup() {
  Serial.begin(57600);
  Serial.println('kosmochrome');
  pinMode(FET_A,OUTPUT);
  pinMode(FET_B,OUTPUT);
  pinMode(FET_C,OUTPUT);
  Serial.setTimeout(50);
}

void loop() {
  while (Serial.available() > 0) {
    int inputValue = Serial.parseInt();
    Serial.println(inputValue);
    digitalWrite(FET_A,inputValue & 1);
    digitalWrite(FET_B,inputValue & 2);
    digitalWrite(FET_C,inputValue & 4);
    delay(inputValue);
    digitalWrite(FET_A,LOW);
    digitalWrite(FET_B,LOW);
    digitalWrite(FET_C,LOW);
  }
  digitalWrite(13,! digitalRead(13));
}
