#include <iostream>

using namespace std;

int repeticoesDoDigito(int k, int num) {
   if(num == 0) return 0;

   short int ultimo_digito = num % 10;

   if(ultimo_digito == k) return 1 + repeticoesDoDigito(k, num / 10);
   return repeticoesDoDigito(k, num / 10);
}

int main(void) {
   int testes;
   cin >> testes;

   int k;
   cin >> k;

   while(testes--) {
      int num;
      cin >> num;
      cout << repeticoesDoDigito(k, num) << endl;
   }

   return 0;
}