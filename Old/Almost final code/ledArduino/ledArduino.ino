
//$pin4123456

#define ASCII_DOLLAR 36

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

const int headerSize = 4;

String inputString = "";
unsigned char cPinScore = 4;
int score = 0;

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
 //score = Serial.read();
 LedLightControl();
 LedStateControl();
 delay(600);
 //LedStuff();
}

void serialEvent (){
  while (Serial.available()) {
    //Serial.println("Serial is available");
    int stringLenght = inputString.length();
    char inChar = (char)Serial.read();
    inputString += inChar;

    if (inChar == '\n'){
      
      int inputLength = inputString.length();
      if (inputString[0] == ASCII_DOLLAR) {
        
        cPinScore = inputString[4]; // PinScore id held here
        if (cPinScore == '4') {
          
          inputToScore(inputString);
        }
        stringComplete = true;
        inputString = "";
      }
    }
    if (stringLenght > 20) {
      inputString = "";
    }
  }
}
void inputToScore(String _myString){
  int myStringLenght = _myString.length();
  int numbersA[myStringLenght];
  char read = 'null';
  for (int i = myStringLenght - 3; i > headerSize; i--) {
    read = _myString[i];

    if(read == '0'){
      numbersA[i] =  0;
    } else if(read == '1'){
        numbersA[i] =  1;
    }else if(read == '2'){
        numbersA[i] =  2;
    }else if(read == '3'){
        numbersA[i] =  3;
    }else if(read == '4'){
        numbersA[i] =  4;
    }else if(read == '5'){
        numbersA[i] =  5;
    }else if(read == '6'){
        numbersA[i] =  6;
    }else if(read == '7'){
        numbersA[i] =  7;
    }else if(read == '8'){
        numbersA[i] =  8;
    }else if(read == '9'){
        numbersA[i] =  9;
    }
    
    Serial.println(numbersA[i]);
  }
}




void LedStuff(){
  //LedStateControl();
  LedLightControl();
}
void getScore(){
}



void LedStateControl(){
  int lightsOn = 0;
  int nextLed = pointsPerLed;

  if (ledsByScore == true){

    while (nextLed <= score) {
      lightsOn++;
      nextLed = nextLed + pointsPerLed;
    }
  } else {lightsOn = myLedsSize;}
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
  lightsOn = 0;
}

void LedLightControl(){
  for(int i = 0; i <= myLedsSize - 1; i++){
    if (myLeds[1][i] == 1){digitalWrite(myLeds[0][i], HIGH);}
    else if (myLeds[1][i] == 0) { digitalWrite(myLeds[0][i], LOW);}
    else {Serial.println("ERROR: I did soming wrong with arrays in LedGridLightUP");}
  }
}
