   #include <iostream>

   void encontraPrimos(int *arr, int n);
   bool primo(int n);

   int main(void) {

      int n;
      std::cin >> n;

      int *primos = new int[n];

      int x, y;
      std::cin >> x;
      std::cin >> y;

      encontraPrimos(primos, n);

      for(int i = x - 1; i < y; i++) {
         std::cout << primos[i] << ' ';
      }

      std::cout << std::endl;

      return 0;
   }

   void encontraPrimos(int *arr, int n) {
      arr[0] = 2;

      for(int i = 1; i < n; i++) {
         for(int j = arr[i - 1] + 1; true; j++) {
            if(primo(j)) {
               arr[i] = j;
               break;
            }
         }
      }
   }

   bool primo(int n) {
      for(int i = 2; i < n; i++) {
         if((n % i) == 0) return false;
      }

      return true;
   }