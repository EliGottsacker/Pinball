/* This is the code for the main microcontroler.
*
*
*This control jobs are:
* [x]coin counter
* [ ]fliper control
* [x]com with screen ardino
* [ ]games played
* [needs work]display intergation
* [ASAP]test code
*
*this is how to use a larger int it is lite and has a range between 0 to 65,535((2^16) - 1 ) but must not be negitve 
* https://www.arduino.cc/reference/en/language/variables/data-types/unsignedint/
* 
* and this is for longs they have a range between -2,147,483,648 to 2,147,483,647. more than we will ever need
* https://www.arduino.cc/reference/en/language/variables/data-types/long/
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
const int minCoinsRequerd = 2; // minnum coins requard to get balls

//points
const int pointsForPopBumper = 1;//ardrino max int is 32,767 so score has 0 add on end 
const int pointsForSlingShot = 1;
const int pointsForRollOver = 1;

//free balls
const int freeBalls = 1;
const int freeBallPoints = 200;

//***************************************************************************************************************

// PUBLIC VARs and setup

int scoreRecord;
int score;// the score for a inivial game
int coinsCounted; // the total coin in the maching
int coins; //
int ballsRemaining;
String message;
int freeBallPointsTracker = freeBallPoints;


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
}



//*********************************************************************************************************

//GAME LOGIC



void GameControl(){
    bool coinCounted;
    int coinDetected = digitalRead(coinDetect);
    int startPushed = digitalRead(startButton);
    int ballState = digitalRead(ballDeathSwith);
    bool ballCounted;

    message = "888888";

    if (coinDetected == HIGH) {
        if(coinCounted == false){
            coinsCounted++;
            coins++;
            //message = coins +"coins";
            coinCounted = true;
            Serial.println("coin counted");
        }
    } else if (coinDetected == HIGH) {
        coinCounted = false;
    }

    //this closesn the gate if all balls have been used
    if (ballsRemaining < 1){
        BallGateControl(false);
        gameState = false;
        //Serial.println("  **** GAME OVER ****");
    }

    if (ballState == HIGH){
        if (ballCounted == false){
            ballsRemaining -= 1;
            ballCounted = true;
        }
    } else {
        ballCounted = false;
    }
    if (score > 32757){
      score = 0
      Serial.print("Max Score Reached. Wow.");
      
    }

    //this checks if requarments to start the game has been reheched and
    if (gameState == true || true){
        if (score > freeBallPointsTracker){
            AddBalls(freeBalls);
            freeBallPointsTracker = score + freeBallPoints;
            if (freeBallPointsTracker > 16000){
              freeBallPointsTracker = freeBallPoints;
            }
        }
        DisplayInt(score);
    } else {
        if (coins >= minCoinsRequerd){
            if (startPushed == HIGH){
                coins -= minCoinsRequerd;
                StartGame();
            } else {
                setMessage("aaaaaa");//enough coins
            }
        } else {
            setMessage("aaaaaa");//not enough coins coins
        }
    }  
}

void AddBalls(int _ballsToAdd){
    ballsRemaining += _ballsToAdd;
    Serial.println("PLAYS: balls have been added");
}
void AddScore(int _score){
    score += _score;
    //Serial.println("SCORE: "+ score);
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
    if (getChar != 0 && getChar != 1 && getChar != 2 && getChar != 3 && getChar != 4 && getChar != 5 && getChar != 6 && getChar != 7 && getChar != 8 && getChar != 9) {
      Serial.println("SOMETHING HAS GONE HORRIBLY WRONG IF THIS PRINTS");
    }
    setstring = comb + comb2;
    //setstring = String(getChar) + setstring;
  }
  
  //Serial.print(setLength);
  
  for (int i = 0; i < 5-setLength; i++) {
    setstring = "a"+setstring;
  }
  
  message = setstring+"0";
  //Serial.print(message);
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

void StartGame(){
    Serial.println("RUNNING: game is now running");

    //resets varible to defalt states
    gameState = true;
    score = 0;
    AddBalls(newBalls);
    BallGateControl(true);
    //AddMessage();
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
    SlingshotControl(slingshotOne, slingshotOneSwitch, pointsForSlingShot);
    SlingshotControl(slingshotTwo, slingshotTwoSwitch, pointsForSlingShot);
    PopBumperControl(popBumperOne, popBumperOneSwitch, pointsForPopBumper);
    PopBumperControl(popBumperTwo, popBumperTwoSwitch, pointsForPopBumper);
    PopBumperControl(popBumperThree, popBumperThreeSwitch, pointsForPopBumper);
    FlipperControl(flipperLeftPowerCoil, flipperLeftHoldCoil, flipperLeftPowerSwitch, flipperLeftHoldSwitch);
    FlipperControl(flipperRightPowerCoil, flipperRightHoldCoil, flipperRightPowerSwitch, flipperRightHoldSwitch);
}

void BallGateControl (bool _open){ //puts ball into play NOT DONE
    if (_open){
        //open
        //digitalWrite(gatePin, HIGH);
        //Serial.println("RUNNING: gate open");
    } else {
        //Serial.println("RUNNING: gate closed");
        //close
    }
}

void PopBumperControl(int _popBumper, int _popBumperSwitch, int _points){ 

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(_popBumperSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        AddScore(_points);
        digitalWrite(_popBumper, HIGH);
        delay(40);
        digitalWrite(_popBumper, LOW);
        //Serial.print("RUNNING: PopBumperControl  ");
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

void FlipperControl(int _flipperPowerCoil, int _flipperHoldCoil, int _flipperPowerSwitch, int _flipperHoldSwitch) {

    int buttonState = 1;
    int button2State = 1;
    // read the state of the pushbutton value:
    buttonState = digitalRead(_flipperPowerSwitch);
    button2State = digitalRead(_flipperHoldSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH && button2State == LOW) {
        Serial.print("RUNNING: FlipperControl  ");
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

void SlingshotControl(int _slingshot, int _slingshotSwitch, int _points) {//NOT DONE

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(_slingshotSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        Serial.print("RUNNING: SlingshotControl  ");
        AddScore(_points);
        digitalWrite(_slingshot, HIGH);
        delay(40);
        digitalWrite(_slingshot, LOW);
    } else {
        // turn LED off:
        digitalWrite(_slingshot, LOW);
    }
}


