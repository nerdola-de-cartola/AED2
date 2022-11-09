#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main(void) {
   string input = "";
   vector<string> arr;

   while(true) {
      getline(cin, input);
      if(input == "DESC" || input == "ASC") break;
      arr.push_back(input);
   }

   if(input == "DESC") {
      sort(arr.begin(), arr.end(), [](string a, string b) {
         return a > b;
      });
   } else {
      sort(arr.begin(), arr.end(), [](string a, string b) {
         return a < b;
      });
   }

   for(const string &line : arr) {
      cout << line << endl;
   }

   return 0;
}