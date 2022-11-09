#include <iostream>

std::string str_double(double value);
std::string stringfy(int value);
void replace_str(bool &needs_and, std::string &str, const std::string &singular, const std::string &plural, int value);

struct breakDouble {
   int cents;
   int hundreds;
   int thousands;
   int millions;

   breakDouble(double value);
};

int main(void) {
   using namespace std;
   double value;
   int tests;

   cin >> tests;
   while(tests--) {
      cin >> value;
      cout << str_double(value) << endl;
   }
}

std::string str_double(double value) {
   using namespace std;

   breakDouble money(value);
   string str = "";
   bool needs_and;

   /*
   cout << money.millions << endl;
   cout << money.thousands << endl;
   cout << money.hundreds << endl;
   cout << money.cents << endl;
   */

   needs_and = false;
   replace_str(needs_and, str, "MILHAO", "MILHOES", money.millions);
   replace_str(needs_and, str, "MIL", "MIL", money.thousands);
   replace_str(needs_and, str, "REAL", "REAIS", money.hundreds);
   replace_str(needs_and, str, "CENTAVO", "CENTAVOS", money.cents);


   return str;
}

breakDouble::breakDouble(double value):
   cents(0), hundreds(0), thousands(0), millions(0) {
   cents = (value - (int) value) * 100;

   int i_value = (int) value;

   int i = 0;
   while(i_value != 0 && i < 3) {
      int value_to_add = i_value % 10;

      for(int j = 0; j < i; j++) value_to_add *= 10;

      hundreds += value_to_add;
      i_value /= 10;
      i++;
   }

   i = 0;
   while(i_value != 0 && i < 3) {
      int value_to_add = i_value % 10;

      for(int j = 0; j < i; j++) value_to_add *= 10;

      thousands += value_to_add;
      i_value /= 10;
      i++;
   }

   i = 0;
   while(i_value != 0 && i < 3) {
      int value_to_add = i_value % 10;

      for(int j = 0; j < i; j++) value_to_add *= 10;

      millions += value_to_add;
      i_value /= 10;
      i++;
   }
}


std::string stringfy(int value) {
   if(value == 900) {
      return "NOVECENTOS";
   } else if(value > 900) {
      return "NOVECENTOS E " + stringfy(value - 900);
   }

   if(value == 800) {
      return "OITOCENTOS";
   } else if(value > 800) {
      return "OITOCENTOS E " + stringfy(value - 800);
   }

   if(value == 700) {
      return "SETECENTOS";
   } else if(value > 700) {
      return "SETECENTOS E " + stringfy(value - 700);
   }

   if(value == 600) {
      return "SEISCENTOS";
   } else if(value > 500) {
      return "SEISCENTOS E " + stringfy(value - 500);
   }

   if(value == 500) {
      return "QUINHENTOS";
   } else if(value > 500) {
      return "QUINHENTOS E " + stringfy(value - 500);
   }

   if(value == 400) {
      return "QUATROCENTOS";
   } else if(value > 400) {
      return "QUATROCENTOS E " + stringfy(value - 400);
   }

   if(value == 300) {
      return "TREZENTOS";
   } else if(value > 300) {
      return "TREZENTOS E " + stringfy(value - 300);
   }

   if(value == 200) {
      return "DUZENTOS";
   } else if(value > 200) {
      return "DUZENTOS E " + stringfy(value - 200);
   }

   if(value == 100) {
      return "CEM";
   } else if(value > 100) {
      return "CENTO E " + stringfy(value - 100);
   }

   if(value == 90) {
      return "NOVENTA";
   } else if(value > 90) {
      return "NOVENTA E " + stringfy(value - 90);
   }

   if(value == 80) {
      return "OITENTA";
   } else if(value > 80) {
      return "OITENTA E " + stringfy(value - 80);
   }

   if(value == 70) {
      return "SETENTA";
   } else if(value > 70) {
      return "SETENTA E " + stringfy(value - 70);
   }

   if(value == 60) {
      return "SESSENTA";
   } else if(value > 60) {
      return "SESSENTA E " + stringfy(value - 60);
   }

   if(value == 50) {
      return "CINQUENTA";
   } else if(value > 50) {
      return "CINQUENTA E " + stringfy(value - 50);
   }

   if(value == 40) {
      return "QUARENTA";
   } else if(value > 40) {
      return "QUARENTA E " + stringfy(value - 40);
   }

   if(value == 30) {
      return "TRINTA";
   } else if(value > 30) {
      return "TRINTA E " + stringfy(value - 30);
   }

   if(value == 20) {
      return "VINTE";
   } else if(value > 20) {
      return "VINTE E " + stringfy(value - 20);
   }

   switch(value) {
      case 0:
         return "";
      case 1:
         return "UM";
      case 2:
         return "DOIS";
      case 3:
         return "TRES";
      case 4:
         return "QUATRO";
      case 5:
         return "CINCO";
      case 6:
         return "SEIS";
      case 7:
         return "SETE";
      case 8:
         return "OITO";
      case 9:
         return "NOVE";
      case 10:
         return "DEZ";
      case 11:
         return "ONZE";
      case 12:
         return "DOZE";
      case 13:
         return "TREZE";
      case 14:
         return "CATORZE";
      case 15:
         return "QUINZE";
      case 16:
         return "DEZESSEIS";
      case 17:
         return "DEZESSETE";
      case 18:
         return "DEZOITO";
      case 19:
         return "DEZENOVE";
      default:
         return "ERROR";
   }
}

void replace_str(bool &needs_and, std::string &str, const std::string &singular, const std::string &plural, int value) {
   if(value != 0) {
      if(needs_and) str += " E ";

      needs_and = true;

      if(value == 1) str += stringfy(value) + ' ' + singular;
      else str += stringfy(value) + ' ' + plural;
   }
}