#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;



void escriu(int n) {
	stack<int> pila;
	int x = n;
	while (true) {
		if (x >= 1) pila.push(x--);
		else {
			if (pila.empty()) return;
			else {
			x = pila.top();
			pila.pop();
			cout << ' ' << x--;
			}
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

