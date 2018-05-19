

const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;
const int led5 = 6;
const int led6 = 7;

const bool ledsByScore = true;//will cause score to set how many leds

int myLedsSize = 6;
int myLeds[2][6] = {
  {led1,led2,led3,led4,led5,led6},//
  {1,1,1,1,1,1}//led states
};

//int lightsOn = 0;
int pointsPerLed = 20;

int score = 76;


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
 //score = Serial.read();
 LedLightControl();
 LedStateControl();
 delay(600);
 //LedStuff();
}

void LedStuff(){
  //LedStateControl();
  LedLightControl();
}



void LedStateControl(){
  int lightsOn = 0;
  int nextLed = pointsPerLed;

  if (ledsByScore == true){
  
    while (nextLed <= score) {
      lightsOn++;
      Serial.println("while");
      nextLed = nextLed + pointsPerLed;
      delay(2);
    }
  
    Serial.print("Socre is ");
    Serial.print(score);
    Serial.print(" nextLed is ");
    Serial.println(nextLed);
  } else {lightsOn = myLedsSize;}
  if (lightsOn > myLedsSize) {
    lightsOn = 0;
    Serial.println("Trying to light up too many leds!");
  }
  for(int i = 1; i <= lightsOn; i++){
    myLeds[1][i] = 1;
    Serial.print("on");
    Serial.println(i);
  }
  for(int i = lightsOn; i <= myLedsSize; i++){
    myLeds[1][i] = 0;
    Serial.print("off");
    Serial.println(i);
  }
  Serial.println(lightsOn);
  lightsOn = 0;
}

void LedLightControl(){
  for(int i = 0; i <= myLedsSize - 1; i++){
    if (myLeds[1][i] == 1){digitalWrite(myLeds[0][i], HIGH);}
    else if (myLeds[1][i] == 0) { digitalWrite(myLeds[0][i], LOW);}
    else {Serial.println("ERROR: I did soming wrong with arrays in LedGridLightUP");}
  }
}
