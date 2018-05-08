//Fritzing File: Serial to Serial Connection.fzz

int ledPin = 13;
int rec;
int Ack_tx = 2; // Acknowledgement tx.




// SETUP *************************************************************************
void setup(){

  Serial.begin(9600);       //Start serial communication at 9600bps
  pinMode(ledPin, OUTPUT);

} //End Setup

// LOOP *************************************************************************
void loop()
{

  while(Serial.available()<2) //Wait for 2 bytes to arrive
  {
    //do nothing
  } //End While


  byte b1=Serial.read();  //Read Upper byte
  byte b2=Serial.read();  //Read Lower byte
  rec=(b1*256)+b2;          //Combine Upper & Lower bytes
  //Serial.println(b1, DEC);
  //Serial.println(b2, DEC);
  //Serial.println(rec, DEC);  //Print received data from Uno


  if (rec == 1) digitalWrite(ledPin, HIGH);    //Select Uno LED On
  else digitalWrite(ledPin, LOW);              //Select Uno LED Off

    Serial.write(Ack_tx/256); //Send the Quotient or "how many times" value
    Serial.write(Ack_tx%256); //Send the Modulo or Remainder.
    delay(5); //Wait for the serial port.

} //End Loop
