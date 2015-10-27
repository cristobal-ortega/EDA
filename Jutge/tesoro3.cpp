#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
using namespace std;



int main(){
	int n,m;
	cin >> n >> m;
	vector< vector<char> > mapa(n,vector<char>(m));
	for(int i=0; i<n;++i){
		for(int j=0; j<m;++j){
			char a;
			cin >> a;
			mapa[i][j]=a;
		}
	}
	/*for(int i=0; i<n;++i){
		for(int j=0; j<m;++j){
			cout << mapa[i][j]<< " ";
		}
		cout <<endl;
	}*/
	pair<int,int> aux;
	bool trobat=false;
	cin >> aux.first >> aux.second;
	queue< pair <int,int> > pila;
	
	--aux.first;
	--aux.second;
	int x=aux.first;int y=aux.second;
	//if(mapa[aux.first][aux.second]=='t') trobat = true;
	pila.push(aux);
	mapa[aux.first][aux.second]='0';
	int minimo=n*m;
	stack<int> distancias;
	while(not pila.empty()){
		aux=pila.front();
		pair<int,int> aux2;
		
		//Camino libre
		bool arriba;
		if(aux.first>0) arriba = (mapa[aux.first-1][aux.second]=='.') or (mapa[aux.first-1][aux.second]=='t');
		bool abajo;
		if(aux.first<n-1) abajo = (mapa[aux.first+1][aux.second]=='.')or (mapa[aux.first+1][aux.second]=='t');
		bool izq;
		if(aux.second>0)izq = (mapa[aux.first][aux.second-1]=='.')or (mapa[aux.first][aux.second-1]=='t');
		bool der;
		if(aux.second<m-1)der = (mapa[aux.first][aux.second+1]=='.'or (mapa[aux.first][aux.second+1]=='t'));
		

		if(aux.first>0 and arriba){
			if(mapa[aux.first-1][aux.second]=='t'){
								aux2.first=aux.first-1;
				aux2.second=aux.second;
				mapa[aux2.first][aux2.second]=mapa[aux.first][aux.second] +1;
				distancias.push((mapa[aux.first][aux.second] +1)-48);
								pila.push(aux2);
			 }
				 
			else {
				aux2.first=aux.first-1;
				aux2.second=aux.second;
				mapa[aux2.first][aux2.second]=mapa[aux.first][aux.second] +1;
				pila.push(aux2);

			}
		}
		if(aux.first<n-1 and abajo){
			if(mapa[aux.first+1][aux.second]=='t'){
								aux2.first=aux.first+1;
				aux2.second=aux.second;
				mapa[aux2.first][aux2.second]=mapa[aux.first][aux.second] +1;
				distancias.push((mapa[aux.first][aux.second] +1)-48);
								pila.push(aux2);
			 }
			 else {
				aux2.first=aux.first+1;
				aux2.second=aux.second;
				mapa[aux2.first][aux2.second]=mapa[aux.first][aux.second] +1;
				pila.push(aux2);
			}
		}
		if(aux.second>0 and izq){
			if(mapa[aux.first][aux.second-1]=='t'){
								aux2.first=aux.first;
				aux2.second=aux.second-1;
				mapa[aux2.first][aux2.second]=mapa[aux.first][aux.second] +1;
				distancias.push((mapa[aux.first][aux.second] +1)-48);
								pila.push(aux2);
			}
			 else {
				aux2.first=aux.first;
				aux2.second=aux.second-1;
				mapa[aux2.first][aux2.second]=mapa[aux.first][aux.second] +1;
				pila.push(aux2);
			}
		}
		if(aux.second<m-1 and der){
			if(mapa[aux.first][aux.second+1]=='t'){
				aux2.first=aux.first;
				aux2.second=aux.second+1;
				mapa[aux2.first][aux2.second]=mapa[aux.first][aux.second] +1;
				distancias.push((mapa[aux.first][aux.second] +1)-48);
								pila.push(aux2);
			}
			 else {
				aux2.first=aux.first;
				aux2.second=aux.second+1;
				mapa[aux2.first][aux2.second]=mapa[aux.first][aux.second] +1;
				pila.push(aux2);
			}
		}
		pila.pop();

		}
				int cuantos=0;
	if(not distancias.empty()){
			int min=distancias.top();distancias.pop();
			++cuantos;
			while(not distancias.empty()){
				int a=distancias.top();distancias.pop();
				if(min>a)min=a;
				++cuantos;
			}
	}

	cout << cuantos <<endl;
}
