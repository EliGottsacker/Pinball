* This is the code for the main microcontroler.
*
*
*This control jobs are:
* [ ]coin counter
* [ ]fliper control
* [x]com with screen ardino
* [ ]games played
* [ ]
*
*
*/
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

const int slingshotRightSwitch = 3; // the number of the switch pin
const int slingshotRight = 12; // the number of the slingshot pin
//const int slingshotRightLED = 17; // the number of the slingshotLED pin

const int slingshotLeftSwitch = 4; // the number of the switch pin
const int slingshotLeft = 13; // the number of the slingshot pin
//const int slingshotLeftLED = 18; // the number of the slingshotLED pin

const int coinDetect = 100;

const int newBalls = 5; //the number of new ball per pament
const int minCoinsRequerd = 2; // minnum coins requard to get balls

// PUBLIC VARs

int scoreRecord[];
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

 pinMode(slingshotRight, OUTPUT);
 pinMode(slingshotLeft, OUTPUT);

 // initialize the pushbutton pin as an input:
 pinMode(popBumperOneSwitch, INPUT);
 pinMode(popBumperTwoSwitch, INPUT);
 pinMode(popBumperOneSwitch, INPUT);

 pinMode(flipperRightHoldSwitch, INPUT);
 pinMode(flipperLeftHoldSwitch, INPUT);
 pinMode(flipperRightPowerSwitch, INPUT);
 pinMode(flipperLeftPowerSwitch, INPUT);

 pinMode(slingshotRightSwitch, INPUT);
 pinMode(slingshotLeftSwitch, INPUT);

 pinMode(coinDetect, INPUT);

//initialize Serial comuticion
 Serial.begin(9600); // start serial communication at 9600bps with USB port
 Serial1.begin(9600); // start serial1 communication at 9600bps with screen control aduino

 Serial.flush(); // flush communication
 Serial1.flush(); // flush communication
}


void loop(){

 GameControl();

 popBumperOneControl();
 popBumperTwoControl();
 popBumperThreeControl();

 flipperRightControl();
 flipperLeftControl();

 slingshotRightControl();
 SlingshotLeftControl();

 delay(5);
}






//*********************************************************************************************************

//GAME LOGIC



void GameControl(){
 bool coinCounted;
 bool startPushed;
 startPushed = digitalRead

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
 if (ballsRemaining <= 0){
 BallGateControl(false);
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

void BallGateControl (bool _open){ //puts ball into play
 if (_open){
 //open
 } else {
 //close
 }
}

void DisplayInt(int _int){
 String outputSting;
 message = outputSting;
}

void DisplayManger(){ //do not use
 String oldMessage;
 int oldScore;
 if (message != oldMessage || score != oldScore){

 }
}

void ToDisplay (String _inputString ){ //could work for length 6 to 1
 char charString [_inputString.length()];

 if (_inputString.length() <= 6 && _inputString.length() >= 1){
 _inputString.toCharArray(charString, _inputString.length());
 Serial1.write(charString);

 } else if (_inputString.length() >= 7){
 // not supported yet.
 Serial.println("ERROR: string value too long");

 } else {
 Serial.println("ERROR: invalited print to display value");
 }
}


//******************************************************************************************************





// ELECTRONICS CONTROL


void popBumperOneControl() {

 int buttonState = 1; // variable for reading the pushbutton status
 // read the state of the pushbutton value:
 buttonState = digitalRead(popBumperOneSwitch);

 // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
 if (buttonState == HIGH) {
 // turn LED on:
 digitalWrite(popBumperOne, HIGH);
 addScore(10);
 delay(40);
 digitalWrite(popBumperOne, LOW);
 } else {
 // turn LED off:
 digitalWrite(popBumperOne, LOW);
 }
}

void popBumperTwoControl() {

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

void flipperLeftControl() {

 int buttonState = 1;
 int button2State = 1;
 // read the state of the pushbutton value:
 buttonState = digitalRead(flipperLeftPowerSwitch);
 button2State = digitalRead(flipperLeftHoldSwitch);

 // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
 if (buttonState == HIGH && button2State == LOW) {
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

void slingshotRightControl() {

 int buttonState = 1; // variable for reading the pushbutton status
 // read the state of the pushbutton value:
 buttonState = digitalRead(slingshotRightSwitch);

 // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
 if (buttonState == HIGH) {
 // turn LED on:
 digitalWrite(slingshotRight, HIGH);
 delay(40);
 digitalWrite(slingshotRight, LOW);
 } else {
 // turn LED off:
 digitalWrite(slingshotRight, LOW);
 }
}

void SlingshotLeftControl() {

 int buttonState = 1; // variable for reading the pushbutton status
 // read the state of the pushbutton value:
 buttonState = digitalRead(slingshotLeftSwitch);

 // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
 if (buttonState == HIGH) {
 // turn LED on:
 digitalWrite(slingshotLeft, HIGH);
 delay(40);
 digitalWrite(slingshotLeft, LOW);
 } else {
 // turn LED off:
 digitalWrite(slingshotLeft, LOW);
 }
}