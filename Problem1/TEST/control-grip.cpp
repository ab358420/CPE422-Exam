// implementation
#include "control-grip.h" // stream stream
using namespace std;

// LED functions
void LED::writeLED(string filename, string value){
   ofstream fs;// output fstream fs
   fs.open((path + filename).c_str());
   fs << value;
   fs.close();
}

void LED::removeTrigger(){
   writeLED("/trigger", "none");
}

void LED::turnOn(){
   cout << "Turning LED3 on." << endl; 
  //  cout << "Turning LED" << number << " on." << endl; // tells which LED number
   removeTrigger();
   writeLED("/brightness", "1");
}

void LED::turnOff(){
   cout << "Turning LED3 off." << endl;
 //  cout << "Turning LED" << number << " off." << endl;
 removeTrigger();
   writeLED("/brightness", "0");
}

void LED::flash(string delayms = "50"){ 
   cout << "Making LED3 flash." << endl;
   //  cout << "Making LED" << number << " flash." << endl;
   writeLED("/trigger", "timer");
   writeLED("/delay_on", delayms);
   writeLED("/delay_off", delayms);
}

void LED::outputState(){
   ifstream fs;
   fs.open( (path + "/trigger").c_str());
   string line;
   while(getline(fs,line)) cout << line << endl;
   fs.close();
}

LED::~LED(){// destructor
   cout << "destroying the LED with path: " << path << endl;
}

// GPIO functions
namespace exploringBB
{
GPIO::GPIO(int number) {
	this->number = number;
	this->debounceTime = 0;
	this->togglePeriod=100;
	this->toggleNumber=-1; //infinite number
	this->callbackFunction = NULL;
	this->threadRunning = false;
	ostringstream s;
	s << "gpio" << number;
	this->name = string(s.str());
	this->path = GPIO_PATH + this->name + "/";
	this->exportGPIO();
	usleep(250000); // 250ms delay
}

int GPIO::exportGPIO(){
return write(GPIO_PATH,"export",this->number);
}

int GPIO::unexportGPIO(){
return write(GPIO_PATH,"unexport",this->number);
}

int GPIO::setDirection(GPIO::DIRECTION dir){
   switch(dir){
   case INPUT: return write(this->path, "direction", "in");
      break;
   case OUTPUT:return write(this->path, "direction", "out");
      break;
   }
   return -1;
}

int GPIO::setValue(GPIO::VALUE value){
   switch(value){
   case HIGH: return write(this->path, "value", "1");
      break;
   case LOW: return write(this->path, "value", "0");
      break;
   }
   return -1;
}

GPIO::VALUE GPIO::getValue(){
	string input = read(this->path, "value");
	if (input == "0") return LOW;
	else return HIGH;
}

GPIO::DIRECTION GPIO::getDirection(){
	string input = read(this->path, "direction");
	if (input == "in") return INPUT;
	else return OUTPUT;
}

int GPIO::streamOpen(){
	stream.open((path + "value").c_str());
	return 0;
}
int GPIO::streamWrite(GPIO::VALUE value){
	stream << value << std::flush;
	return 0;
}
int GPIO::streamClose(){
	stream.close();
	return 0;
}

GPIO::~GPIO(){
this->unexportGPIO();
}
}
