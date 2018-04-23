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

const int flipperRightHoldSwitch = A3; // the number of the switch pin
const int flipperRightHoldCoil = 8; //

const int flipperRightPowerSwitch = A4; //
const int flipperRightPowerCoil = 9; // the number of the flipper pin

const int flipperLeftHoldSwitch = A5; // the number of the switch pin
const int flipperLeftHoldCoil = 10; //

const int flipperLeftPowerSwitch = 2; //
const int flipperLeftPowerCoil = 11; // the number of the flipper pin

const int slingshotOneSwitch = 3; // the number of the switch pin
const int slingshotOne = 12; // the number of the slingshot pin
//const int slingshotOneLED = 17; // the number of the slingshotLED pin

const int slingshotTwoSwitch = 4; // the number of the switch pin
const int slingshotTwoS = 13; // the number of the slingshot pin
//const int slingshotLeftLED = 18; // the number of the slingshotLED pin

const int coinDetect = 100;
const int ballDeathSwith = 101;
const int startButton = 102;

const int newBalls = 5; //the number of new ball per pament
const int minCoinsRequerd = 2; // minnum coins requard to get balls

//points
const int pointsForPopBumper = 10;
const int pointsForSlingShot = 10;
const int pointsForRollOver = 10;

//free balls
const int freeBalls = 1;
const int freeBallPoints = 2000;

//***************************************************************************************************************

// PUBLIC VARs and setup

int scoreRecord;
int score;// the score for a inivial game
int coinsCounted; // the total coin in the maching
int coins; //
int ballsRemaining;
String message = "0Coins";


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
    pinMode(slingshotLeft, OUTPUT);

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

    delay(5);
}



//*********************************************************************************************************

//GAME LOGIC



void GameControl(){
    bool coinCounted;
    bool coinDetect = digitalRead(coinDetect);
    bool startPushed = digitalRead(startButton);
    bool ballState = digitalRead(ballDeathSwith);
    bool ballCounted;

    int freeBallPointsTracker;

    if (coinDetect == true) {
        if(coinCounted == false){
            coinsCounted++;
            coins++;
            //message = coins +"coins";
            coinCounted = true;
        }
    } else if (coinDetect == false) {
        coinCounted = false;
    }

    //this closesn the gate if all balls have been used
    if (ballsRemaining < 1){
        BallGateControl(false);
        gameState = false;
    }

    if (ballState == true){
        if (ballCounted == false){
            ballsRemaining -= 1;
            ballCounted = true;
        }
    } else {
        ballCounted = false;
    }

    //this checks if requarments to start the game has been reheched and
    if (gameState == true){
        DisplayInt(score);
    } else {

        if (coins >= minCoinsRequerd){
            if (startPushed){
            coins -= minCoinsRequerd;
            StartGame();
            } else {
            message = "Ready";
            }
        } else {
            message = "+Coins";
        }
    }

    if (score > freeBallPointsTracker){
        AddBalls(freeBalls);
        freeBallPointsTracker = score + freeBallPoints;
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

void EndGame(){

}

void AddBalls(int _ballsToAdd){
    ballsRemaining += _ballsToAdd;
}
void AddScore(int _score){
    score += _score;
}



void DisplayInt(int _int){//NOT DONE, NOT TESTED
    String outputSting;
    outputSting = String(_int);
    if (outputSting.length() < 7){
        for(int i = 0; ;){

        }
    }
    message = outputSting;
}

void DisplayManger(String _str){ //NOT DONE. do not use untill test rest of code. This will make it so display it show proper timing
    String oldMessage;
    int oldScore;
    if (message != oldMessage || score != oldScore){

    }
}

void ToDisplay (String _inputString ){ //could work for length 6 to 1
    char charString [_inputString.length()];

    if (_inputString.length() <= 6 && _inputString.length() > 0){
        _inputString.toCharArray(charString, _inputString.length());
        Serial1.write(charString);

    } else if (_inputString.length() >= 7){// not supported yet.     
        Serial.println("ERROR: string value too long");
    } else {
        Serial.println("ERROR: invalited print to display value");
    }
}

bool RollOverSwich(int _inputPin){// NOT TESTED will take in a pin and making into a bool roll over switch
    bool rollOverSwich = digitalRead(_inputPin);
    bool rollOverSwichCounted;

    if (rollOverSwich == true && rollOverSwichCounted == false){
        rollOverSwichCounted = true;
        return true;

    } else if (rollOverSwich == false){
        rollOverSwichCounted = false;
        return false;

    } else {
        return false;
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
    } else {
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
    } else {
        // turn LED off:
        digitalWrite(_popBumper, LOW);
    }
}

void UseLED(int _ledPin,  int _mode){//NOT DONE
    bool LEDState;

    if (_mode == 0){// LED off
        LEDState = true;
    } else if (_mode == 1){//LED on
        LEDState = false;
    } else if (_mode == 2) {// LED bink DO NOT USE
        digitalWrite(_ledPin, HIGH);
    }else if (_mode == 3){
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

void SlingshotControl(int _slingshot, _slingshotSwitch, _points) {//NOT DONE

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(_slingshotSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        AddScore(_points);
        digitalWrite(_slingshot, HIGH);
        delay(40);
        digitalWrite(_slingshot, LOW);
    } else {
        // turn LED off:
        digitalWrite(_slingshot, LOW);
    }
}


















/*
// this has been cleaned up
void PopBumperOneControl() {

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(popBumperOneSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
    // turn LED on:
        digitalWrite(popBumperOne, HIGH);
        AddScore(10);
        delay(40);
        digitalWrite(popBumperOne, LOW);
    } else {
        // turn LED off:
        digitalWrite(popBumperOne, LOW);
    }
}

void PopBumperTwoControl() {

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(popBumperTwoSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        digitalWrite(popBumperTwo, HIGH);
        delay(40);
        digitalWrite(popBumperTwo, LOW);
    } else {
        // turn LED off:
        digitalWrite(popBumperTwo, LOW);
    }
}

void PopBumperThreeControl() {

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(popBumperThreeSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        AddScore(pointsForSlingShot);
        digitalWrite(popBumperThree, HIGH);
        delay(40);
        digitalWrite(popBumperThree, LOW);
    } else {
        // turn LED off:
        digitalWrite(popBumperThree, LOW);
    }
}
void FlipperRightControl() {

    int buttonState = 1;
    int button2State = 1;
    // read the state of the pushbutton value:
    buttonState = digitalRead(flipperRightPowerSwitch);
    button2State = digitalRead(flipperRightHoldSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH && button2State == LOW) {

        digitalWrite(flipperRightHoldCoil, HIGH);
        digitalWrite(flipperRightPowerCoil, HIGH);
    } else if (buttonState == HIGH && button2State == HIGH){
        digitalWrite(flipperRightPowerCoil, LOW);
    } else {
        // turn LED off:
        digitalWrite(flipperRightPowerCoil, LOW);
        digitalWrite(flipperRightHoldCoil, LOW);
    }
}

void FlipperLeftControl() {

    int buttonState = 1;
    int button2State = 1;
    // read the state of the pushbutton value:
    buttonState = digitalRead(flipperLeftPowerSwitch);
    button2State = digitalRead(flipperLeftHoldSwitch);

    
    if (buttonState == HIGH && button2State == LOW) {// check if the pushbutton is pressed. If it is, the buttonState is HIGH:
        digitalWrite(flipperLeftHoldCoil, HIGH);
        digitalWrite(flipperLeftPowerCoil, HIGH);
    } else if (buttonState == HIGH && button2State == HIGH){
        digitalWrite(flipperLeftPowerCoil, LOW);
    } else {
        // turn LED off:
        digitalWrite(flipperLeftPowerCoil, LOW);
        digitalWrite(flipperLeftHoldCoil, LOW);
    }
}
void slingshotOneControl() {

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(slingshotOneSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        AddScore(pointsForSlingShot);
        digitalWrite(slingshotOne, HIGH);
        delay(40);
        digitalWrite(slingshotOne, LOW);
    } else {
        // turn LED off:
        digitalWrite(slingshotOne, LOW);
    }
}

void SlingshotLeftControl() {

    int buttonState = 1; // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    buttonState = digitalRead(slingshotTwoSwitch);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        AddScore(pointsForSlingShot);
        digitalWrite(slingshotLeft, HIGH);
        delay(40);
        digitalWrite(slingshotLeft, LOW);
    } else {
        // turn LED off:
        digitalWrite(slingshotLeft, LOW);
    }
}
*/