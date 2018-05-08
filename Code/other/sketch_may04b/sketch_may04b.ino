char test[7] = {'9', '0', '8', '1','2','3','\n'};

void setup() {
    Serial.begin(9600); // start serial communication at 9600bps with USB port
    Serial1.begin(9600); // start serial1 communication at 9600bps with screen control aduino

    Serial.flush(); // flush communication
    Serial1.flush(); // flush communication
}

void loop() {
 Serial1.write(test);
 Serial.write(test);
 
}
