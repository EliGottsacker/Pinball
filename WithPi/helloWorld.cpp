#include <iostream>
#include <stdio.h>
#include <wiringPi.h>

int main() {

  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  while (true)
  {
    digitalWrite (0, HIGH) ;
    delay (500) ;
    digitalWrite (0,  LOW) ;
    delay (500) ;
  }

  printf("hello world \r\n");
  return 0;
}
