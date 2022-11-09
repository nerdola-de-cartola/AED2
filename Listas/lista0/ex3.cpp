   #include <iostream>

   int encontraPrimos(int start, int end);
   bool primo(int n);

   int main(void) {

      int x, y, n;
      std::cin >> x;
      std::cin >> y;

      n = encontraPrimos(x, y);

      std::cout << n << std::endl;

      return 0;
   }

   int encontraPrimos(int start, int end) {
      int qtd = 0;

      for(int j = start; j <= end; j++) {
         if(primo(j)) qtd++;
      }

      return qtd;
   }

   bool primo(int n) {
      if(n == 1 || n == 0) return false;

      for(int i = 2; i < n; i++) {
         if((n % i) == 0) return false;
      }

      return true;
   }