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
  string word;
  regex r("[?]{2}[:]{1}\\d+[.]{1}\\d*");
  while((cin >> word, word != "Exit"))
  {
    if(regex_match(word, r))
    {
      cout << word << ",\n";
    }
  }
  return 0;
}