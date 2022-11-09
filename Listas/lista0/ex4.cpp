#include <iostream>
#include <deque>
#include <map>
#include <string>

using namespace std;

void printFront(const deque<int> &d);
void printBack(const deque<int> &d);
void quebraString(const string &input, string &funcao, string &deque_name, int &new_value);

int main(void) {
   string input;
	map<string, deque<int>> deques;
	string funcao;
	string name;
   int new_value;
	bool first_input = true;

   while(true) {
      if(!first_input) cin.ignore();
		getline(cin, input);

		if(input == "fim") {
			deques.clear();
         return 0;
		}

		quebraString(input, funcao, name, new_value);

		/*
		cout << funcao << endl;
		cout << name << endl;
		cout << new_value << endl;
		*/
      
		if(funcao == "criarDeque") {
			// deques[name] = deque<int>();
		} else if(funcao == "pushEsquerda") {
         deques[name].push_front(new_value);
      } else if(funcao == "pushDireita") {
         deques[name].push_back(new_value);
      } else if(funcao == "popEsquerda") {
         deques[name].pop_front();
      } else if(funcao == "popDireita") {
         deques[name].pop_back();
      } else if(funcao == "listEsquerda") {
         printFront(deques[name]);
      } else if(funcao == "listDireita") {
         printBack(deques[name]);
      }
   }
}

void printFront(const deque<int> &d) {
   for(auto it = d.begin(); it < d.end(); it++) {
		cout << *it << ' ';
	}

	cout << endl;
}

void printBack(const deque<int> &d) {
	for(auto it = d.end() - 1; it >= d.begin(); it--) {
		cout << *it << ' ';
	}

	cout << endl;
}

void quebraString(const string &input, string &funcao, string &deque_name, int &new_value) {
	bool lendo_funcao = true;
	bool lendo_name = false;
	bool lendo_new_value = false;
	string str_value = "";

	funcao = "";
	deque_name = "";

	for(char letra : input) {
		if(letra == ')') break;

		if(lendo_funcao) {
			if(letra == '(') {
				lendo_funcao = false;
				lendo_name = true;
				continue;
			}

			funcao += letra;
		} else if(lendo_name) {
			if(letra == ',') {
				lendo_name = false;
				lendo_new_value = true;
				continue;
			}

			deque_name += letra;
		} else if(lendo_new_value) {
			str_value += letra;
		}
	}

	if(lendo_new_value) {
		new_value = stoi(str_value);
	}
}