#include "binary_search_tree.cpp"
#include <vector>

using namespace std;

int main(void) {
   Tree<int> t;

   t.insert(5);
   t.insert(3);
   t.insert(2);
   t.insert(1);
   t.insert(4);
   t.insert(7);
   t.insert(6);

   auto v = t.BFS();

   for(auto value : v) {
      cout << value << ' ';
   }
   cout << endl;

   cout << t.size() << endl;

   return 0;
}