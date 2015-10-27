#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;


void escriu(int n) {
		stack<int> pila;
       pila.push(n);
       while (!pila.empty()) {
               int x = pila.top();
               pila.pop();
               cout << ' ' << x;
               if (x > 1) {
                       pila.push(x-1);
                       pila.push(x-1);
               }
       }

}

int main(){
	int n;
	while(cin >> n){
		escriu(n);
		cout << endl;
	}
}
