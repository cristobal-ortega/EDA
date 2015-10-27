#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<cmath>
#include<queue>
using namespace std;


struct roca{
	double x;
	double y;
	double r;
	int dis;
};

int bfs(vector<roca>& v, double d){
	int n= v.size();
	queue<int> pila;
	pila.push(0);
	while(not pila.empty()){
		int aux = pila.front(); pila.pop();

		for(int i=1; i<n; ++i){
			roca aux2 = v[i];
			double x = aux2.x - v[aux].x;
			double y = aux2.y - v[aux].y;
			double r= aux2.r + v[aux].r;
			double hueco = sqrt((x*x) + (y*y)) -r;
			if( d >= hueco and v[i].dis ==-1){
				v[i].dis = v[aux].dis +1;
				pila.push(i);
			}
		}
	}
	return v[n-1].dis + 1;
}



int main(){
	int n;
	while(cin >> n){
		double d;
		cin >> d;
		vector<roca> v(n);
		for(int i=0;i<n;++i){
			cin >> v[i].x >> v[i].y >> v[i].r;
			v[i].dis=-1;
		}
		int saltos = bfs(v,d);
		if(saltos > 0) cout << saltos <<endl;
		else cout << "Xof!" <<endl;
	}
}
					
			
		
	
