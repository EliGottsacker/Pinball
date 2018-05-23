/*code for leds on a seprat ardonio
*
*/

//$pin4123456
//$pin404456

#define ASCII_DOLLAR 36

const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;
const int led5 = 6;
const int led6 = 7;


//debugging
const bool ledsByScore = true; //will cause score to set how many leds affected by score.
const bool useWarrings = true;
const bool useMessages = true;
const int indicaterLed = 13;   //use this for debugging.

int myLedsSize = 6;
int myLeds[2][6] = {// myLeds[y][x]. if to add led blinking would be 3 and an other array set wold be add for delta time.
  {led1,led2,led3,led4,led5,led6}, //led pins.
  {1,1,1,1,1,1}//led states.
};

//int lightsOn = 0;
int pointsPerLed = 100;

const int headerSize = 4;
const char channal = '4';

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
        if (cPinScore == channal) {

          digitalWrite(13, HIGH);
          score = inputToScore(inputString);//just to make it easy to read
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
int inputToScore(String _myString){
  int myStringLenght = _myString.length();
  int preScore = 0;
  char read = 'null';
  int x = 0;
  for (int i = myStringLenght - 3; i > headerSize; i--) {//loop for reading data inside string. minus 3 because last to slots were weird and last number is not wanted.
    int preInt = 0;
    int mul = 0;
    read = _myString[i];
    x++;

    //reads the char
    if(read == '0'){
      preInt =  0;
    } else if(read == '1'){
        preInt =  1;
    }else if(read == '2'){
        preInt =  2;
    }else if(read == '3'){
        preInt =  3;
    }else if(read == '4'){
        preInt =  4;
    }else if(read == '5'){
        preInt =  5;
    }else if(read == '6'){
        preInt =  6;
    }else if(read == '7'){
        preInt =  7;
    }else if(read == '8'){
        preInt =  8;
    }else if(read == '9'){
        preInt =  9;
    }else if(read == 'a'){
        preInt =  0;
    }else{
      if (useWarrings == true){
       Serial.println("ERROR: something is very wrong line:115");
      }
    }

    //set a multiblyer
    if(x == 1){
      mul = 1;
    } else if (x == 2){
      mul = 10;
    } else if (x == 3){
      mul = 100;
    } else if (x == 4){
      mul = 1000;
    } else if (x == 5){
      mul = 10000;
    } else if (x > 5){
      if(useWarrings == true){
        Serial.println("ERROR: number to large line:126");
      }
      x = 0;
      mul = 0;
    } else{
      Serial.println("ERROR: something went wrong line:130");
    }
    //mul = pow(10, x);//why will this not work?
    preInt = preInt * mul;
    preScore += preInt;
    preInt = 0;
  }
  return preScore;
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
    Serial.println("Trying to light up too many leds! Check pointsPerLed on line 23. line:169");
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
    if (myLeds[1][i] == 1){
      digitalWrite(myLeds[0][i], HIGH);
    }
    else if (myLeds[1][i] == 0) {
      digitalWrite(myLeds[0][i], LOW);
    }
    else {
      Serial.println("ERROR: I did soming wrong with arrays in LedLightControl start at line 180. line:184");
    }
  }
}
