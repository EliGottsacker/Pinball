const int detectPin = A0;
const int detectedPin = 13;

int detect;

void setup() {
  pinMode(detectPin, INPUT);
  pinMode(detectedPin, OUTPUT);

}

void loop() {
  detect = digitalRead(detectPin);

  if (detect == HIGH){
    digitalWrite(detectedPin, HIGH);
  } else {
    digitalWrite(detectedPin, LOW);
  }

}
