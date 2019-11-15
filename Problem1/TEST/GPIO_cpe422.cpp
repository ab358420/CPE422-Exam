/* A Simple GPIO application
*/

#include<iostream>
#include<unistd.h> //for usleep
#include"GPIO.h"
using namespace exploringBB;
using namespace std;

int main(){
   GPIO outGPIO(49), inGPIO(46), inGPIO(26); 
// GPIO(49) = GPIO1_17 = (1x32)+17 external LED
// GPIO(46) = GPIO1_14 = (1x32)+14 Button B
// GPIO(26) = GPIO0_26 = (0x32)+26 Button A

   // Basic Output - Flash the LED 10 times, once per second
   outGPIO.setDirection(OUTPUT);
   for (int i=0; i<10; i++){
      outGPIO.setValue(HIGH);
      usleep(500000); //micro-second sleep 0.5 seconds
      outGPIO.setValue(LOW);
      usleep(500000);
   }
   // Basic Input example
   inGPIO.setDirection(INPUT);
   cout << "The value of the input is: "<< inGPIO.getValue() << endl;

   // Fast write to GPIO 1 million times
   outGPIO.streamOpen();
   for (int i=0; i<1000000; i++){
      outGPIO.streamWrite(HIGH);
      outGPIO.streamWrite(LOW);
   }
   outGPIO.streamClose();

   return 0;
}
