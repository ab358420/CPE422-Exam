#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define FILE_PATH "/home/debian/cpe422/Exam/Problem2/"

int main(int argc, char* argv[])
{
string cmd(argv[1]); // puts character is cmd as a string
cout << "The current Path is: " << FILE_PATH << endl; // cout = print out
cout << "File name passed is: " << cmd << endl;
cout << endl;
fstream fs; 
string line;
int count=0;
string temp[10];
fs.open((FILE_PATH + cmd),std::fstream::in);
// temp[count++]=line;
// put data into array temp
// fs.open((path + cmd).c_str(),std::fstream::in);
while(getline(fs,line)) // remove cout, does not print on screen
  temp[count++]=line;
  float x; // temporary variable
  float sum=0;
  for (int i=0; i<count; i++)
    {
    x = stof(temp[i]); // stf = string to float
    sum = sum + x;
/* stf temp[];
float temp=temp[count]+temp[count++];
float average=temp/count; */
    }
float average = sum / count;
cout << "Average Temperature is: " << average << endl;
cout << endl;
	fs.close();
}
