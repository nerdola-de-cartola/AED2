#include <iostream>

#define CLOCKWISE 1
#define COUNTERCLOCKWISE 0

using namespace std;

struct Node {
    int number;
    struct Node *next;
    struct Node *prev;
};

struct List{
    Node *first;
    Node *last;
    int size;
};


List newList() {
    List l;

    l.first = NULL;
    l.last = NULL;
    l.size = 0;

    return l;
}

void push(List *l, int number) {
    Node *new_node = NULL;

    new_node = new Node;
    new_node->number = number;

    if(l->size == 0) {
        l->first = new_node;
        l->last = new_node;
        new_node->prev = l->last;
        new_node->next = l->first;
        l->size++;
        return;
    }
    
    l->last->next = new_node;
    l->first->prev = new_node;
    new_node->prev = l->last;
    new_node->next = l->first;
    l->last = new_node;
    l->size++;
}

void freeList(List *l) {
   Node *p, *tmp;
   int i, total;

   total = l->size;

   for(p = l->first, i = 0; i < total; p = tmp, i++) {
      tmp = p->next;
      delete p;
   }

   *l = newList();
}

void removeList(List *l, Node *old_node) {
    if(l->size == 1) {
         freeList(l);
         return;
    }

   old_node->prev->next = old_node->next;
   old_node->next->prev = old_node->prev;
   if(old_node == l->last) l->last = old_node->prev;
   if(old_node == l->first) l->first = old_node->next;

   l->size--;
   delete old_node;
}

Node *searchList(Node *start, int search, char way) {
   Node *p = start;
   int i;

   for(i = 1; i != search; i++) {
      if(way == CLOCKWISE) p = p->next;
      else if(way == COUNTERCLOCKWISE) p = p->prev;
   }

   return p;
}

void printList(List *l) {
    Node *p;
    int i;

    for(p = l->first, i = 0; i < l->size; p = p->next, i++) {
        cout << p->number << ' ';
    }

    cout << endl;
}

int main(void) {
   Node *cw = NULL, *ccw = NULL, *tmp = NULL;

   int n, k, m;
   int i;

   cin >> n;
   cin >> k;
   cin >> m;

   List circle = newList();

   for(i = 1; i <= n; i++) push(&circle, i);

   cw = circle.first;
   ccw = circle.last;
   while(circle.size != 0) {
      printList(&circle);
      cw = searchList(cw, k, CLOCKWISE);
      ccw = searchList(ccw, m, COUNTERCLOCKWISE);

      if(cw == NULL || ccw == NULL) {
         cout << "Deu merda" << endl;
         continue;
      }
      
      if(cw == ccw) {
         // cout << cw->number << ' ';

         tmp = cw;
         cw = cw->next;
         ccw = cw->prev;

         removeList(&circle, tmp);
         continue;
      }

      // cout << cw->number << ' ';
      // cout << ccw->number << ' ';

      tmp = cw;
      cw = cw->next;
      removeList(&circle, tmp);

      tmp = ccw;
      ccw = cw->prev;
      removeList(&circle, tmp);
   }

   cout << endl;

   return 0;
}