#include "heap.cpp"

using namespace std;

int main(void) {
   Heap<int> h(MAX_HEAP);
   
   h.insert(2);
   h.insert(1);
   h.insert(6);
   h.insert(8);
   h.insert(9);

   h.remove();

   int t = h.top();
   cout << t << endl;

   h.print();

   return 0;
}