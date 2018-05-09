String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
unsigned char selectDigit = 0;  // start no digit selected
const unsigned char selectLatch = 12; // start no digit selected
unsigned char cDataPinScore[8];
unsigned char cPinScore = 4;
unsigned char digitBCD = 0; // start no digit selected

// ASCII CODE DEFINES
#define ASCII_A 65
#define ASCII_B 66
#define ASCII_C 67
#define ASCII_D 68
#define ASCII_E 69
#define ASCII_F 70
#define ASCII_G 71
#define ASCII_H 72
#define ASCII_I 73
#define ASCII_J 74
#define ASCII_K 75
#define ASCII_L 76
#define ASCII_M 77
#define ASCII_N 78
#define ASCII_O 79
#define ASCII_P 80
#define ASCII_Q 81
#define ASCII_R 82
#define ASCII_S 83
#define ASCII_T 84
#define ASCII_U 85
#define ASCII_V 86
#define ASCII_W 87
#define ASCII_X 88
#define ASCII_Y 89
#define ASCII_Z 90
#define ASCII_EQUAL 61
#define ASCII_DOLLAR 36
#define ASCII_COMMA 44
#define ASCII_CR 13
#define ASCII_LF 10

enum  
{
  LED_ZERO,
  LED_ONE,
  LED_TWO,
  LED_THREE,
  PLAYER_ONE,
  PLAYER_TWO,
  CREDIT_BALLS  
};

#define LED_CHAN PLAYER_ONE // change this to the PLAYER that the unit will be driving

void setup() 
{
  Serial.flush();
  DDRB = B00111111;  // sets Arduino port B pins 0 to 4 as outputs
  DDRD = B11111111;  // sets Arduino port B pins 0 to 4 as outputs

  // initialize serial:
  Serial.begin(9600);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

    for (int i = 0; i < 8; i++) 
  {
    cDataPinScore[i] = i + 48;
  }

}

void loop() 
{

// continuously scan the PinScore display, outputing the most recent data
  for (int i = 2; i < 8; i++) 
  {
    selectDigit = i;  

    PORTD = (0); // clear all

    digitalWrite(selectDigit,HIGH);

    PORTB = (cDataPinScore[i-2]- 48); // subracting 48 converts an ASCII char to its equivalent int

    digitalWrite(selectLatch,HIGH);

    delay(3) ;// hold each digit for a period
  }

}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */

void serialEvent() 
{
  while (Serial.available()) 
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    Serial.print(inChar);

    // add it to the inputString:
    inputString += inChar;

    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') 
    {
      int inputLength = inputString.length();

      if (inputLength == 12) {

      if (inputString[0] == ASCII_DOLLAR) // check for header
      {
        cPinScore = inputString[4]; // PinScore id held here

        if (cPinScore == (LED_CHAN + 48)) //4 )
        {
          for (int k = 0; k<6; k++) // acount for numbers less than six digits
      {
      cDataPinScore[k] = inputString[k + 5];
      } // next k

        } // end If received ID matches the one this unit is programmed for

        stringComplete = true;
        inputString = "";

      } // end If first char was $ 

      } else {
        if (inputLength < 12) {
          return;
        } else {
          inputString = "";
          return;
        }
      }

    } // end If new line 

  } // end While

} // end Sub
