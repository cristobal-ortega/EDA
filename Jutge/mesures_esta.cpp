#include <iostream>
#include <queue>
#include <string>
using namespace std;


int main() {
	priority_queue< int,vector<int>,greater<int> > cola;
	cout.setf(ios_base::fixed);
	cout.precision(4);
	string op;
	double total = 0;
	int max = 0;
	while (cin >> op) {
		if (op == "number") {
			int n;
			cin >> n;
			if (cola.empty()) max = n;
			else if (max < n) max = n;
			cola.push(n);
			total += n;
		}else if (op == "delete") {
			if (not cola.empty()) {
				int n = cola.top();
				cola.pop();
				total -= n;
			}
		}
		if(cola.empty()) cout << "no elements" << endl;
		else cout << "minimum: " << cola.top() << ", maximum: " << max << ", average: " << total/cola.size() << endl;
	}
}