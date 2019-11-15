#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h> // to use sleep function
using namespace std;

#define ADC_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"
#define FILE_PATH "/home/debian/cpe422/Exam/Problem2"
#define ADC 0

// temperature is linear
float getTemperature(int adc_value) {     // from the TMP36 datasheet
   float cur_voltage = adc_value * (1.80f/4096.0f); // (maximum volt temp can read) Vcc = 1.8V, 12-bit
   float diff_degreesC = (cur_voltage-0.75f)/0.01f;
   return (25.0f + diff_degreesC); // temp is degrees C
// taking value 0-4095, 4096 values total
}

int readAnalog(int number){
   stringstream ss;
   ss << ADC_PATH << number << "_raw"; // in_voltage0_raw
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in); // convert to c string
   fs >> number; // reading file, puts it into variable number
// ** line for reading fs >> number, this is from 0 to 4095 not temp
   fs.close();
   return number;
}

int main(int argc, char*argv[]){
// print to file
string cmd(argv[1]);
fstream fs;
string path(FILE_PATH);
fs.open((path + "/" + cmd).c_str(),std::fstream::out);
/* Declarations
fs << "The current Temperature path is: " << FILE_PATH << endl; 
fs << "File name passed is: " << cmd << endl;
fs << endl;
fs << "Starting the TMP36 example" << endl;
fs << endl;
*/
for (int i=0;i<10;i++)
{
// fs << "The ADC value input is: " << readAnalog(ADC) << endl;
float temp = getTemperature(readAnalog(ADC));
fs << temp << "°C" << endl;
// fs << "Temperature Reading is: " << temp << "°C" << endl;
sleep(1); // delay for 1 second in between
// fs << endl;
} 

/*  print to screen
   std::cout << "Starting the TMP36 example" << std::endl;
   std::cout << "The ADC value input is: " << readAnalog(ADC) << endl;
   float temp = getTemperature(readAnalog(ADC));
   cout << "Temperature is " << temp << "°C" << endl;
*/
fs.close();
cout << endl;
return 0;
}
