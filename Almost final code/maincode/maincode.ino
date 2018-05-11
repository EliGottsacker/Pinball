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


//*****************************************************************************************************************
// Decare these varible to the corisopning Aurdino pins and wanted vaules for tuning game play exsperence


// constants won't change. They're used here to set pin numbers:
const int popBumperOneSwitch = A0; // the number of the switch pin
const int popBumperOne = 5; // the number of the popBumper pin
//const int popBumperOneLED = 14; // the number of the popBumperLED pin

const int popBumperTwoSwitch = A1; // the number of the switch pin
const int popBumperTwo = 6; // the number of the popBumper pin
//const int popBumperTwoLED = 15; // the number of the popBumperLED pin


const int popBumperThreeSwitch = A2; // the number of the switch pin
const int popBumperThree = 7; // the number of the popBumper pin
//const int popBumperThreeLED = 16; // the number of the popBumperLED pin

const int flipperRightHoldSwitch = A15; // the number of the switch pin
const int flipperRightHoldCoil = 8; //
const int flipperRightPowerSwitch = A4; //
const int flipperRightPowerCoil = 11; // the number of the flipper pin

const int flipperLeftHoldSwitch = A8; // the number of the switch pin
const int flipperLeftHoldCoil = 10; //

const int flipperLeftPowerSwitch = A11; //
const int flipperLeftPowerCoil = 9; // the number of the flipper pin

const int slingshotOneSwitch = A6; // the number of the switch pin
const int slingshotOne = 3; // the number of the slingshot pin
//const int slingshotOneLED = 17; // the number of the slingshotLED pin

const int slingshotTwoSwitch = A7; // the number of the switch pin
const int slingshotTwo = 4; // the number of the slingshot pin
//const int slingshotLeftLED = 18; // the number of the slingshotLED pin

const int gatePin = 103;
const int openTime = 1;

const int coinDetect = 100;
const int ballDeathSwith = 101;
const int startButton = 102;

const int newBalls = 5; //the number of new ball per pament
const int minCoinsRequerd = 1; // minnum coins requard to get balls

//points
const int pointsForPopBumper = 1;
const int pointsForSlingShot = 1;
const int pointsForRollOver = 1;

//free balls
const int freeBalls = 1;
const int freeBallPoints = 200;

//***************************************************************************************************************

// PUBLIC VARs and setup

const bool inputLogging = true; //Enable this to check if inputs are working

int scoreRecord;
int score;// the score for a inivial game
int coinsCounted; // the total coin in the maching
int coins; //
int ballsRemaining;
String message;
int freeBallPointsTracker = freeBallPoints;

int gameClock = 0;//this is used to make sure a lost ball does not get counted twice (independent from game state);
int recentLostBall = 0;

bool gameState;


//int money;

void setup() {
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
    pinMode(startButton, INPUT);
    pinMode(ballDeathSwith, INPUT);

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

    delay(50);

    gameClock += 1;
    if (gameClock == 10000) {
      gameClock = 0;
      recentLostBall -= 10000;
    }
}



//*********************************************************************************************************

//GAME LOGIC



void GameControl(){
    bool coinCounted;
    int coinDetected = digitalRead(coinDetect);
    int startPushed = digitalRead(startButton);
    int ballState = digitalRead(ballDeathSwith);
    bool ballCounted;

    message = "000000";


    //Serial.read()

    coins = 1;

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

    //this closesn the gate if all balls have been used
    if (ballsRemaining < 1){
      if (gameState == true) {
        //BallGateControl(false);//no need to close gate
        gameState = false;
        Serial.println("LOGIC: Game ended");
      }
    }

    if (ballState == HIGH){
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

    //this checks if requarments to start the game has been reheched and
    if (gameState == true){
        if (score > freeBallPointsTracker){
            AddBalls(freeBalls);
            freeBallPointsTracker = score + freeBallPoints;
        }
        DisplayInt(score);
    } else {
        if (coins >= minCoinsRequerd){
            //if (startPushed == HIGH){
                coins -= minCoinsRequerd;
                StartGame();
            //} else {
            //    setMessage("aaaaaa");//enough coins
            //}
        } else {
            setMessage("aaaaaa");//not enough coins coins
        }
    }  
}

void StartGame(){
    Serial.println("LOGIC: Starting new game");

    //resets varible to defalt states
    gameState = true;
    score = 0;
    message = "aaaaaa";

    AddBalls(newBalls);
    ReleaseBall();
}

void AddBalls(int _ballsToAdd){
    ballsRemaining += _ballsToAdd;
    Serial.println("LOGIC: Balls have been added");
}

void ReleaseBall() {/*//UNFINISHED
  digitalWrite(gatePin, HIGH);
  Serial.println("RUNNING: gate open new ball released");
  delay(100);
  digitalWrite(gatePin, LOW);*/
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

void setMessage(String mess) {
  //message[];
  //for (int i = 0; i < sizeof(mess); i++) {
  //  message[i] = mess[i];
  //}
message = mess;
}

void ToDisplay (String _inputString){ //could work for length 6 to 1
    int lengthInput = _inputString.length();
    /*char setCharThing[6];*/
    String combine = "$PIN4"+_inputString;
    /*if (combine.startsWith("$") == false) {
      return true;
    }*/
    //Serial.println(combine);
    /*combine.toCharArray(setCharThing, 12);*/

    //Serial.println(setCharThing);

    if (true || (lengthInput < 7 && lengthInput > -1)){
        Serial1.print(combine);
        //Serial1.write(setCharThing);
        Serial1.write('\n');
        //Serial.println(_inputChar);

    } else if (lengthInput > 6){// not supported yet.
        Serial.println("ERROR: string value too long");
    } else {
        Serial.println("ERROR: invalited print to display value");
    }
}

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

void LedGridLightUP(){
    int myLeds[] = {};
    int myLedsSize = sizeof(myLeds);
    int lights; 
    if (gameState == true){
        if (score > freeBallPointsTracker){
            lights++;
        }
        for(int i; i <= myLedsSize; i++){
            digitalWrite(myLeds[i], HIGH);
        }
    } else {
        for(int i; i <= myLedsSize; i++){
            digitalWrite(myLeds[i], LOW);
        }
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

void RollOverSwichControl (int _rollOverSwich){
    bool swichState;
    swichState = RollOverSwichLogic(_rollOverSwich);
    if (swichState){
        AddScore(pointsForRollOver);
    }
}

void UseLED(int _ledPin,  int _mode){//NOT DONE
    bool LEDState;

    if (_mode == 0){// LED off
        LEDState = true;
    } else if (_mode == 1){//LED on
        LEDState = false;
    } else if (_mode == 2) { // LED pulse
        LEDState = true;
        delay(40);//ajust time
        LEDState = false;
    }else if (_mode == 3){ // LED bink DO NOT USE
        digitalWrite(_ledPin, HIGH);
    }

    if (LEDState){
        digitalWrite(_ledPin, HIGH);
    }else{
        digitalWrite(_ledPin, LOW);
    }
}

void FlipperControl(String which, int _flipperPowerCoil, int _flipperHoldCoil, int _flipperPowerSwitch, int _flipperHoldSwitch) {

    int buttonState = 1;
    int button2State = 1;
    // read the state of the pushbutton value:
    buttonState = digitalRead(_flipperPowerSwitch);
    button2State = digitalRead(_flipperHoldSwitch);

    if (inputLogging == true) {

    if (button2State == HIGH) {   
     Serial.println("RUNNING: " + which + " hold switch triggered");
    }

    if (buttonState == HIGH) {
      Serial.println("RUNNING: " + which + " button detected");
    }

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

void SlingshotControl(String which, int _slingshot, int _slingshotSwitch, int _points) {//NOT DONE

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(_slingshotSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        if (inputLogging == true) {
        Serial.print("RUNNING: " + which + " triggered");
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

