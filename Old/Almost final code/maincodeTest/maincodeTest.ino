/* This is the code for the main microcontroler.
*
*
*This control jobs are:
* [x]coin counter
* [x]fliper control
* [x]com with screen ardino
* [ ]games played
* [x]display intergation
* [ASAP]test code
*
*
*/

#include <Servo.h>  // servo library

Servo servo1;  // servo control object

int angle;


//pop bumpers
const int popBumperOneSwitch = A0;
const int popBumperOne = 52;

const int popBumperTwoSwitch = A4;
const int popBumperTwo = 44;

const int popBumperThreeSwitch = A2;
const int popBumperThree = 48;

//flippers
const int flipperRightHoldSwitch = A9;
const int flipperRightHoldCoil = 40;
const int flipperRightPowerSwitch = A11;
const int flipperRightPowerCoil = 36;

const int flipperLeftHoldSwitch = A6;
const int flipperLeftHoldCoil = 32;
const int flipperLeftPowerSwitch = A7;
const int flipperLeftPowerCoil = 28;

//slingshots
const int slingshotOneSwitch = A13;
const int slingshotOne = 24;

const int slingshotTwoSwitch = A15;
const int slingshotTwo = 22;

//leds pins
const int led1 = 51;
const int led2 = 47;
const int led3 = 43;
const int led4 = 39;
const int led5 = 35;
const int led6 = 31;

const int pointsPerLed = 200;

//more
const int servo1pin = 53;
const int ballDeathSwith = 7;

const int coinDetect = 100;

//coin constents
const int minCoinsRequerd = 1;

const int newBalls = 5;


//points
const int pointsForPopBumper = 1;
const int pointsForSlingShot = 1;
const int pointsForRollOver = 1;

//free balls
const int freeBalls = 1;
const int freeBallPoints = 200;

//debugging flages
const bool inputLogging = true; //Enable this to check if inputs are working
const bool ledsByScore = true;//will cause score to set how many leds

//***************************************************************************************************************

// PUBLIC VARs and setup



int scoreRecord;
int score = 0;// the score for a inivial game
int coinsCounted = 0; // the total coin in the maching
int coins = 0; //
int ballsRemaining = 0;
String message;
int freeBallPointsTracker = freeBallPoints;
int lightsOn = 0;

int gameClock = 0;//this is used to make sure a lost ball does not get counted twice (independent from game state);
int recentLostBall = 0;

bool gameState;
bool gameRunning;

//ledgrid
int myLedsSize = 6;
int myLeds[2][6] = {
  {led1,led2,led3,led4,led5,led6},//
  {1,1,1,1,1,1}//led states
};

//int money;

void setup() {

  servo1.attach(servo1pin, 900, 2100);

  // initialize the LED pin as an output:
  pinMode(popBumperOne, OUTPUT);
  pinMode(popBumperTwo, OUTPUT);
  pinMode(popBumperThree, OUTPUT);

  pinMode(flipperRightPowerCoil, OUTPUT);
  pinMode(flipperRightHoldCoil, OUTPUT);

  pinMode(flipperLeftPowerCoil, OUTPUT);
  pinMode(flipperLeftHoldCoil, OUTPUT);

  pinMode(slingshotOne, OUTPUT);
  pinMode(slingshotTwo, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(popBumperOneSwitch, INPUT);
  pinMode(popBumperTwoSwitch, INPUT);
  pinMode(popBumperOneSwitch, INPUT);

  pinMode(flipperRightHoldSwitch, INPUT);
  pinMode(flipperLeftHoldSwitch, INPUT);
  pinMode(flipperRightPowerSwitch, INPUT);
  pinMode(flipperLeftPowerSwitch, INPUT);

  pinMode(slingshotOneSwitch, INPUT);
  pinMode(slingshotTwoSwitch, INPUT);

  pinMode(coinDetect, INPUT);
  pinMode(ballDeathSwith, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  //initialize Serial comuticion
  Serial.begin(9600); // start serial communication at 9600bps with USB port
  Serial1.begin(9600); // start serial1 communication at 9600bps with screen control aduino

  Serial.flush(); // flush communication
  Serial1.flush(); // flush communication
}

void loop(){

    GameControl();

    ElectronicsLoop();

    ToDisplay(message);
    LedStuff();

    delay(50);

    gameClock += 1;
    if (gameClock == 10000) {
      gameClock = 0;
      recentLostBall -= 10000;
    }

    //LedGridLightUP();
}



//*********************************************************************************************************

//GAME LOGIC



void GameControl(){

    message = "000000";
    coins = 1;

    Always();
    if (gameState == true){
      During();
    } else {
      Waiting();
    }
}

void During(){
  int ballState = digitalRead(ballDeathSwith);
  bool ballCounted;

  DisplayInt(score);

  if (ballsRemaining < 1){
    gameState = false;
    Serial.println("LOGIC: Game ended");
  }
  if (ballState == HIGH){
    if (inputLogging == true) {Serial.println("INPUT: Ball death triggered");}
    if (ballCounted == false){
      if (gameClock-recentLostBall < 3000) {//make sure that bounced ball is not counted twice
        ballsRemaining -= 1;
        ballCounted = true;
        delay(1000);//delay after ball is detected
        if (ballsRemaining > 0) {
          ReleaseBall();
        }
      }
    }
  } else {
    ballCounted = false;
  }
  if (score > freeBallPointsTracker){
      AddBalls(freeBalls);
      freeBallPointsTracker = score + freeBallPoints;
  }
}
void Waiting(){
  if (coins >= minCoinsRequerd){
    coins -= minCoinsRequerd;
    StartGame();
  } else {
    message = "aaaaaa";//not enough coins coins
    for(int i = lightsOn; i <= myLedsSize; i++){
      myLeds[2][i] = 0;
    }
  }
}
void Always(){
  bool coinCounted;
  int coinDetected = digitalRead(coinDetect);
  if (coinDetected == HIGH) {//if coin sensor is on
    if(coinCounted == false){//and we have not counted it yet
      coinsCounted++;
      coins++;
      coinCounted = true;//count it
      Serial.println("LOGIC: Coin counted");
    }
  } else if (coinDetected == LOW) {//if sensor is off
      coinCounted = false;//let us count it next time
  }
}

void StartGame(){
  Serial.println("LOGIC: Starting new game");

  //resets varible to defalt states
  gameRunning = true;
  score = 0;
  message = "aaaaaa";

  AddBalls(newBalls);
  ReleaseBall();
}

void endGame(){//run once per game when over

}

void AddBalls(int _ballsToAdd){
  ballsRemaining += _ballsToAdd;
  Serial.println("LOGIC: Balls have been added");
}
void ReleaseBall() {
  servo1.write(180);
  delay(1500);
  servo1.write(0);
}

void AddScore(int _score){
    score += _score;
    if (score > 30000) {
      score = 0;
      freeBallPointsTracker = freeBallPoints;
    }
}

void DisplayInt(int score) {
  int setLength = 1;
  if (score > 9) {
    setLength = 2;
  }
  if (score > 99) {
    setLength = 3;
  }
  if (score > 999) {
    setLength = 4;
  }
  if (score > 9999) {
    setLength = 5;
  }
  if (score > 99999) {
    setLength = 6;
  }

  String setstring;
  int getChar;
  String comb;
  String comb2;

  for (int i = 0; i < setLength; i++) {
    getChar = 0;

    if (i == 0) {
      getChar = (score / 1U) % 10;
    }
    if (i == 1) {
      getChar = (score / 10U) % 10;
    }
    if (i == 2) {
      getChar = (score / 100U) % 10;
    }
    if (i == 3) {
      getChar = (score / 1000U) % 10;
    }
    if (i == 4) {
      getChar = (score / 10000U) % 10;
    }
    if (i == 5) {
      getChar = (score / 100000U) % 10;
    }

    comb2 = setstring;

    if (getChar == 0) {
      comb = "0";
    }
    if (getChar == 1) {
      comb = "1";
    }
    if (getChar == 2) {
      comb = "2";
    }
    if (getChar == 3) {
      comb = "3";
    }
    if (getChar == 4) {
      comb = "4";
    }
    if (getChar == 5) {
      comb = "5";
    }
    if (getChar == 6) {
      comb = "6";
    }
    if (getChar == 7) {
      comb = "7";
    }
    if (getChar == 8) {
      comb = "8";
    }
    if (getChar == 9) {
      comb = "9";
    }
    setstring = comb + comb2;
  }

  for (int i = 0; i < 5-setLength; i++) {
    setstring = "a"+setstring;
  }
  if (setstring == "aaaa0") {
    message = "aaaaa0";
  } else {
    message = setstring+"0";
  }
}
void ToDisplay (String _inputString){ //could work for length 6 to 1
    int lengthInput = _inputString.length();
    String combine = "$PIN4"+_inputString;
    if (true || (lengthInput < 7 && lengthInput > -1)){
        Serial1.print(combine);
        Serial1.write('\n');

    } else if (lengthInput > 6){// not supported yet.
        Serial.println("ERROR: string value too long");
    } else {
        Serial.println("ERROR: invalited print to display value");
    }
}

//under work for pi
//int OpenCom(String _type, String _ID){/* start comuticion with another device */}
//int SendTo(String _data, String _ID){/* */}
//String ReceiveFrom(){}

bool RollOverSwichLogic(int _inputPin){// NOT TESTED will take in a pin and making into a bool roll over switch
    int rollOverSwich = digitalRead(_inputPin);
    bool rollOverSwichCounted;

    if (rollOverSwich == HIGH && rollOverSwichCounted == false){
        rollOverSwichCounted = true;
        return true;

    } else if (rollOverSwich == LOW){
        rollOverSwichCounted = false;
        return false;

    } else {
        return false;
    }
}

void LedStuff(){
  LedStateControl();
  LedLightControl();
}
void LedStateControl(){
  int nextLed = pointsPerLed;
  if (ledsByScore == true){
    if (score > nextLed){
      lightsOn++;
      nextLed = nextLed + score;
    }
  } else {lightsOn = myLedsSize;}
  if (lightsOn > myLedsSize) {
    lightsOn = 0;
    Serial.println("Trying to light up too many leds!");
  }
  for(int i = 0; i <= lightsOn; i++){
    myLeds[2][i] = 1;
  }
  for(int i = lightsOn; i <= myLedsSize; i++){
    myLeds[2][i] = 0;
  }
}
void LedLightControl(){
  for(int i = 0; i <= myLedsSize; i++){
    if (myLeds[2][i] == 1){digitalWrite(myLeds[1][i], HIGH);}
    else if (myLeds[2][i] == 0) { digitalWrite(myLeds[1][i], LOW);}
    else {Serial.println("ERROR: I did soming wrong with arrays in LedGridLightUP");}
  }
}


//******************************************************************************************************

// ELECTRONICS CONTROL



void ElectronicsLoop(){
    SlingshotControl("Slingshot one", slingshotOne, slingshotOneSwitch, pointsForSlingShot);
    SlingshotControl("Slingshot two", slingshotTwo, slingshotTwoSwitch, pointsForSlingShot);
    PopBumperControl("PopBumper one", popBumperOne, popBumperOneSwitch, pointsForPopBumper);
    PopBumperControl("PopBumper two", popBumperTwo, popBumperTwoSwitch, pointsForPopBumper);
    PopBumperControl("PopBumper three", popBumperThree, popBumperThreeSwitch, pointsForPopBumper);
    FlipperControl("Flipper left", flipperLeftPowerCoil, flipperLeftHoldCoil, flipperLeftPowerSwitch, flipperLeftHoldSwitch);
    FlipperControl("Flipper right", flipperRightPowerCoil, flipperRightHoldCoil, flipperRightPowerSwitch, flipperRightHoldSwitch);
}

void PopBumperControl(String which, int _popBumper, int _popBumperSwitch, int _points){

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(_popBumperSwitch);

   if (inputLogging == true && buttonState == HIGH) {
     Serial.println("RUNNING: " + which + " triggered");
   }

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        AddScore(_points);
        digitalWrite(_popBumper, HIGH);
        delay(40);
        digitalWrite(_popBumper, LOW);
        delay(40);
    } else {
        // turn LED off:
        digitalWrite(_popBumper, LOW);
    }
}

void RollOverSwichControl (int _rollOverSwich){//not done
    bool swichState;
    swichState = RollOverSwichLogic(_rollOverSwich);
    if (swichState){
        AddScore(pointsForRollOver);
    }
}

void FlipperControl(String which, int _flipperPowerCoil, int _flipperHoldCoil, int _flipperPowerSwitch, int _flipperHoldSwitch) {

    int buttonState = 1;
    int button2State = 1;
    // read the state of the pushbutton value:
    buttonState = digitalRead(_flipperPowerSwitch);
    button2State = digitalRead(_flipperHoldSwitch);

    if (inputLogging == true) {
      if (button2State == HIGH) {Serial.println("RUNNING: " + which + " hold switch triggered");}
      if (buttonState == HIGH) {Serial.println("RUNNING: " + which + " button detected");}
    }

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH && button2State == LOW) {
        digitalWrite(_flipperHoldCoil, HIGH);
        digitalWrite(_flipperPowerCoil, HIGH);
    } else if (buttonState == HIGH && button2State == HIGH){
        digitalWrite(_flipperPowerCoil, LOW);
    } else {
        // turn LED off:
        digitalWrite(_flipperPowerCoil, LOW);
        digitalWrite(_flipperHoldCoil, LOW);
    }
}

void SlingshotControl(String which, int _slingshot, int _slingshotSwitch, int _points) {

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(_slingshotSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        if (inputLogging == true) {
        Serial.println("RUNNING: " + which + " triggered");
        }
        //AddScore(_points);
        digitalWrite(_slingshot, HIGH);
        delay(40);
        digitalWrite(_slingshot, LOW);
        delay(40);
    } else {
        // turn LED off:
        digitalWrite(_slingshot, LOW);
    }
}
