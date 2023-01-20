#include <iostream>
#include <stdlib.h>

enum TypeHeap {MAX_HEAP, MIN_HEAP};

template <typename T>
void swap(T &a, T &b);

template <typename T>
class Heap {
   private:
      T *m_arr;
      TypeHeap m_type;
      int m_size;
      int m_capacity;

   public:
      Heap(TypeHeap type);
      virtual ~Heap();
      int size();
      int capacity();
      void insert(T new_data);
      void print();
      void reHeapUp(int i);
      T top();
      void remove();
      void reHeapDown(int i);

};

template <typename T>
Heap<T>::Heap(TypeHeap type)
   : m_arr(NULL), m_type(type), m_size(0), m_capacity(0) {}

template <typename T>
Heap<T>::~Heap() {
   delete m_arr;
}

template <typename T>
int Heap<T>::size() {
   return m_size;
}

template <typename T>
int Heap<T>::capacity() {
   return m_capacity;
}


template <typename T>
void Heap<T>::insert(T new_data) {
   if(m_arr == NULL) {
      m_arr = new T;
      m_capacity = 1;
      m_size = 1;
      m_arr[0] = new_data;
      return;
   }

   if(m_size == m_capacity) {
      T *tmp = (T *) realloc(m_arr, 2 * m_capacity * sizeof(T));
      
      if(tmp == NULL) {
         std::cout << "Allocation error" << std::endl;
         exit(1);
      }

      m_arr = tmp;
      m_capacity *= 2;
   }

   m_arr[m_size] = new_data;
   m_size++;

   this->reHeapUp(m_size - 1);

}

template<typename T>
void Heap<T>::print() {
   int i;

   for(i = 0; i < m_size - 1; i++) {
      std::cout << m_arr[i] << ", ";
   }

   std::cout << m_arr[m_size - 1] << std::endl;
}

template<typename T>
void Heap<T>::reHeapUp(int i) {
   int temp;
   int index_father = (i - 1) / 2;

   if(this->m_type == MAX_HEAP) {
      while(i > 0 && m_arr[i] > m_arr[index_father]) {
         // troca o elemento a[i] com seu pai
         swap(m_arr[i], m_arr[index_father]);

         i = index_father;
         index_father = (i - 1) / 2;
      }
   } else {
      while(i > 0 && m_arr[i] < m_arr[index_father]) {
         // troca o elemento a[i] com seu pai
         swap(m_arr[i], m_arr[index_father]);

         i = index_father;
         index_father = (i - 1) / 2;
      }
   }

}

template<typename T>
void swap(T &a, T &b) {
   T tmp = a;
   a = b;
   b = tmp;
}

template<typename T>
T Heap<T>::top() {
   return m_arr[0];
}

template<typename T>
void Heap<T>::remove() {
  
   if(m_size == 0) return;

   swap(m_arr[0], m_arr[m_size - 1]);

   m_size--;

   this->reHeapDown(0);
}

template<typename T>
void Heap<T>::reHeapDown(int i) {
  int temp;
  int index_child = 2 * i + 1;

   while (index_child < m_size) {

      if((index_child + 1) < m_size && (m_arr[index_child + 1] > m_arr[index_child]))
         index_child++;
      
      if(m_arr[i] > m_arr[index_child]) 
         break; 
 
      swap(m_arr[i], m_arr[index_child]);

      i = index_child;
      index_child = 2 * i + 1;
   }
}