#include <iostream>
#include <queue>
using namespace std;

int main() {
	priority_queue<int> cola;
	char op;
	while (cin >> op) {
		if (op == 'S') {
			int num;
			cin >> num;
			cola.push(num);
		}else if (op == 'A') {
			if (cola.empty()) cout << "error!" << endl;
			else cout << cola.top() << endl;
		}else if (op == 'R') {
			if (cola.empty()) cout << "error!" << endl;
			else cola.pop();
		}else if (op == 'I') {
			int num;
			cin >> num;
			if (cola.empty()) cout << "error!" << endl;
			else {
				int aux = cola.top();
				cola.pop();
				cola.push(aux+num);
			}
		}else if (op == 'D') {
			int num;
			cin >> num;
			if (cola.empty()) cout << "error!" << endl;
			else {
				int aux = cola.top();
				cola.pop();
				cola.push(aux-num);
			}
		}
	}
}