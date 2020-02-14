/* Speed_filter.cpp
  Filter to extract the speed mesurements taken by the speed monitor 
  sensor on the referee system and outputing the matched measurements to file
  stated.
*/
#include<fstream>
#include<regex>
#include<iostream>
#include<string>
#include<time.h>
using namespace std;

int main()
{
  //gets current date & time as a string in buffer
  time_t rawtime = time(0);
  struct tm * timeinfo;
  char buffer [100];
  timeinfo = localtime (&rawtime);
  strftime(buffer, 100, "./Recordings/%Y%m%d_%H%M%S.csv", timeinfo);

  //build filename and opens file
  string filename = buffer;
  fstream file;
  cout << "Saving to " << filename << endl;
  file.open(filename, ios::out | ios::app);

  // stores word being read, match count and regex to match against
  string word;
  long count = 0;
  regex r("[?]{2}[:]{1}\\d+[.]{1}\\d*");

  while((cin >> word, word != "Exit"))
  {
    if(regex_match(word, r))
    {
      count++;
      if(count%2)
      {
        word = word.substr(3);
        file << word << ",\n";
      }
    }
  }

  file.close();
  return 0;
}