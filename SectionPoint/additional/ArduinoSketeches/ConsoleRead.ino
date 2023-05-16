#define ledPin 13

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if(Serial.available() > 0)
  {
    String info;
    info = Serial.readStringUntil('\n');

    if(info.equals("ON")) {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED ON");
    }
    else if(info.equals("OFF")) {
      digitalWrite(ledPin, LOW);  
    }

  }

}