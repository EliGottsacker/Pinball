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
const int slingshotTwo = 13; // the number of the slingshot pin
//const int slingshotLeftLED = 18; // the number of the slingshotLED pin

const int gatePin = 103;
const int openTime = 1;

const int coinDetect = 100;
const int ballDeathSwith = 101;
const int startButton = 102;

const int newBalls = 5; //the number of new ball per pament
const int minCoinsRequerd = 2; // minnum coins requard to get balls

const int messageArraySize = 6;

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
char message[messageArraySize];
//char imputMessage;
int freeBallPointsTracker = 0;


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

    delay(5);
}



//*********************************************************************************************************

//GAME LOGIC



void GameControl(){
    bool coinCounted;
    int coinDetected = digitalRead(coinDetect);
    int startPushed = digitalRead(startButton);
    int ballState = digitalRead(ballDeathSwith);
    bool ballCounted;

    setMessage("888888");


    //Serial.read()

    

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

    //this checks if requarments to start the game has been reheched and
    if (gameState == true){
        if (score > freeBallPointsTracker){
            AddBalls(freeBalls);
            freeBallPointsTracker = score + freeBallPoints;
        }
        DisplayInt(score);
    } else {
        if (coins >= minCoinsRequerd){
            if (startPushed == HIGH){
                coins -= minCoinsRequerd;
                StartGame();
            } else {
                //message[1] = 'a';//"ready";
                setMessage("ready");
            }
        } else {
            setMessage("888888");     
        }
    }  
}

void setMessage(char mess[]) {
  //message[];
  for (int i = 0; i < sizeof(mess); i++) {
    message[i] = mess[i];
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


void AddBalls(int _ballsToAdd){
    ballsRemaining += _ballsToAdd;
    Serial.println("PLAYS: balls have been added");
}
void AddScore(int _score){
    score += _score;
    Serial.println("SCORE: "+ score);
}



void DisplayInt(int _int){//NOT DONE, NOT TESTED
    //String outputSting;
    /*
    char outputChar[messageArraySize];
    int countOfNeededZeros;
    int lengthOutputChar = sizeof(outputChar);
    char neededZeros[]];
    

    if (true){
        for(int i = 0; i < countOfNeededZeros ; i++){
            neededZeros[i] = '0'; 
        }
        outputChar[messageArraySize] =  neededZeros + char(_int) ;
    }
    //outputSting = String();
    message = outputChar
    */
}


/*
void DisplayManger(String _str){ //NOT DONE. do not use untill test rest of code. This will make it so display it show proper timing
    char oldMessage;
    int oldScore;
    if (message != oldMessage || score != oldScore){

    }
}
*/

void ToDisplay (char _inputChar[6] ){ //could work for length 6 to 1
    int lengthInputChar = sizeof(_inputChar);

    if (lengthInputChar <= 6 && lengthInputChar >= 0){
        Serial1.write(_inputChar);
        Serial1.write('\n');
        //Serial.println(_inputChar);

    } else if (lengthInputChar >= 7){// not supported yet.
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
        Serial.print("RUNNING: PopBumperControl  ");
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

