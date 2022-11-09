#include <iostream>

using namespace std;

void printMatrix(int **matrix, int n, int m);

int main(void) {
   int n;
   int i, j, k;

   cin >> n;

   if(n == 2) {
      cout << "nao existe" << endl;
      return 0;
   }

   int **matrix = new int *[n];
   for(i = 0; i < n; i++) {
      matrix[i] = new int[n];
      for(j = 0; j < n; j++) {
         matrix[i][j] = 0;
      }
   }

   for(k = 1, i = 0, j = n/2; k <= n*n; k++) {
      if(matrix[i][j] != 0) {
         if(i != n-1) i++;
         else j = 0;
         
         k--;
         continue;
      }

      matrix[i][j] = k;

      if(i == 0 && j == n - 1) {
         i++;
         cout << 1 << endl;
      }else if(i == 0) {
         i = n-1;
         j++;
         cout << 2 << endl;
      }else if(j == n - 1) {
         i--;
         j = 0;
         cout << 3 << endl;
      } else {
         i--;
         j++;
         cout << 4 << endl;
      }

      printMatrix(matrix, n, n);
      cout << endl;
    }

    printMatrix(matrix, n, n);

   return 0;
}

void printMatrix(int **matrix, int n, int m) {
   int i, j;

   for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            cout << matrix[i][j] << ' ';
        }
        cout << '\n';
    }
}