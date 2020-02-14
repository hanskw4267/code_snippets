/* Speed_filter.cpp
  Filter to extract the speed mesurements taken by the speed monitor 
  sensor on the referee system and outputing the matched meaasurements to stdout
*/
#include<regex>
#include<iostream>
#include<string>
using namespace std;

int main()
{

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
        cout << word << ",\n";
      }
    }
  }
  return 0;
}