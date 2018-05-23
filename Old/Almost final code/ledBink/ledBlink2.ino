//$pin4123456

#define ASCII_DOLLAR 36

const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;
const int led5 = 6;
const int led6 = 7;

const bool ledsBink = true;//will cause score to set how many leds
const int cycles = 1;
const int ledDelay = 300;

int myLedsSize = 6;
int myLeds[2][6] = {
  {led1,led2,led3,led4,led5,led6},//
  {1,1,1,1,1,1}//led states
};

//int lightsOn = 0;
int pointsPerLed = 20;

const int headerSize = 4;

String inputString = "";
unsigned char cPinScore = 4;
int score = 0;
int lightsOn = 0;

bool stringComplete = false;


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  Serial.begin(9600); // start serial communication at 9600bps with USB port
  Serial.flush(); // flush communication

}

void loop() {
  BadLedBink(100);
  delay(10);
 //LedStuff();
}



void LedStateControl(){



  if (ledsBink == true){
    for(int i = 0; i < myLedsSize - 1; i++){
      lightsOn++;
      LedOther();
      LedLightControl();
      delay(ledDelay);
    }
    for (int i = 0; i < cycles; i++) {
      lightsOn = myLedsSize;
      LedOther();
      LedLightControl();
      delay(ledDelay);
      lightsOn = 0;
      LedOther();
      LedLightControl();
      delay(ledDelay);
    }
  } else {lightsOn = myLedsSize;}


}
void LedOther() {
  if (lightsOn > myLedsSize) {
    lightsOn = 0;
    Serial.println("Trying to light up too many leds!");
  }
  for(int i = 1; i <= lightsOn; i++){
    myLeds[1][i] = 1;
  }
  for(int i = lightsOn; i <= myLedsSize; i++){
    myLeds[1][i] = 0;
  }
}

void LedLightControl(){
  for(int i = 0; i <= myLedsSize - 1; i++){
    if (myLeds[1][i] == 1){digitalWrite(myLeds[0][i], HIGH);}
    else if (myLeds[1][i] == 0) { digitalWrite(myLeds[0][i], LOW);}
    else {Serial.println("ERROR: I did soming wrong with arrays in LedGridLightUP");}
  }
}

void BadLedBink(int partOneDelayTime){

  digitalWrite(led1, HIGH);
  delay(partOneDelayTime);
  digitalWrite(led2, HIGH);
  delay(partOneDelayTime);
  digitalWrite(led3, HIGH);
  delay(partOneDelayTime);
  digitalWrite(led4, HIGH);
  delay(partOneDelayTime);
  digitalWrite(led5, HIGH);
  delay(partOneDelayTime);
  digitalWrite(led6, HIGH);
  delay(partOneDelayTime);
  digitalWrite(led1, LOW);
  delay(partOneDelayTime);
  digitalWrite(led2, LOW);
  delay(partOneDelayTime);
  digitalWrite(led3, LOW);
  delay(partOneDelayTime);
  digitalWrite(led4, LOW);
  delay(partOneDelayTime);
  digitalWrite(led5, LOW);
  delay(partOneDelayTime);
  digitalWrite(led6, LOW);
  delay(partOneDelayTime);
  delay(500);
}
