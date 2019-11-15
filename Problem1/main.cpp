// main function

//#include "control-grip.h"
#include "derek_LED.h"
#include "GPIO.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<cstdio>
#include<fcntl.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<pthread.h>
using namespace std;
using namespace exploringBB;

int main(){
   GPIO outGPIO(49), inGPIO_A(46), inGPIO_B(26); 
// GPIO(49) = GPIO1_17 = (1x32)+17 external LED
// GPIO(46) = GPIO1_14 = (1x32)+14 Button B
// GPIO(26) = GPIO0_26 = (0x32)+26 Button A
    LED led(3); // LED usr3 

// set directions
  outGPIO.setDirection(OUTPUT);
  inGPIO_A.setDirection(INPUT);
  inGPIO_B.setDirection(INPUT);

// set values, output low and inputs high
outGPIO.setValue(LOW);
inGPIO_A.setValue(HIGH);
inGPIO_A.setValue(HIGH);

// if A pressed output high
if (inGPIO_A.getValue() == 0)
{
      outGPIO.setValue(HIGH);
}

// if B pressed turn on LED usr3
else if (inGPIO_B.getValue() == 0)
{
        led.turnOn();   
}

// if neither are pressed, return to output low and inputs high
else 
{
  outGPIO.setValue(LOW);
  inGPIO_A.setValue(HIGH);
  inGPIO_B.setValue(HIGH);
  led.turnOff();
} 

/*
cout << "The value of the input A is: "<< inGPIO_A.getValue() << endl;
 cout << "The value of the input B is: "<< inGPIO_B.getValue() << endl;

   // Fast write to GPIO 1 million times
   outGPIO.streamOpen();
   for (int i=0; i<1000000; i++){
      outGPIO.streamWrite(HIGH);
      outGPIO.streamWrite(LOW);
   }
*/
   

   return 0;
}
