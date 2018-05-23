
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

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
