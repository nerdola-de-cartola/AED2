#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int binarySearch(const vector<unsigned int> &arr, unsigned int target);
int binarySearch(const vector<unsigned int> &arr, unsigned int start, unsigned int end, unsigned int target);

int main(void) {
   unsigned int tests;
   cin >> tests;

   while(tests--) {
      vector<unsigned int> arr;
      map<unsigned int, unsigned int> initial_index;
      unsigned int target;
      cin >> target;

      while(true) {
         unsigned int input;
         cin >> input;

         if(input == -1)  break;

         arr.push_back(input);
      }

      for(int i = 0; i < arr.size(); i++) initial_index[arr[i]] = i;

      sort(arr.begin(), arr.end(), [] (int a, int b) {
         return a < b;
      });
      
      // for(unsigned int item : arr) cout << item << endl;

      int target_index = binarySearch(arr, target);
      
      if(target_index == -1) cout << "ausente";
      else cout << initial_index[arr[target_index]] + 1;

      cout << endl;
   }

   return 0;
}

int binarySearch(const vector<unsigned int> &arr, unsigned int target) {
   return binarySearch(arr, 0, arr.size(), target);
}

int binarySearch(const vector<unsigned int> &arr, unsigned int start, unsigned int end, unsigned int target) {
   if(start == end) return -1;

   unsigned int mid_index = (start + end) / 2;

   if(arr[mid_index] == target) return mid_index;
   else if(arr[mid_index] > target) return binarySearch(arr, start, mid_index, target);
   else return binarySearch(arr, mid_index + 1, end, target);
}