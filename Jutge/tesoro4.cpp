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
	vector< vector<int> > puntu(n,vector<int>(m,0));
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
	puntu[aux.first][aux.second]=0;
	int minimo=n*m;
	vector< vector<bool> > visit(n,vector<bool>(m,false));
	stack<int> distancias;
	while(not pila.empty()){
		aux=pila.front();
		pair<int,int> aux2;
		pila.pop();
		
		//Camino libre
		bool arriba;
		if(aux.first>0) arriba = mapa[aux.first-1][aux.second]!='X';//(mapa[aux.first-1][aux.second]=='.') or (mapa[aux.first-1][aux.second]=='t');
		bool abajo;
		if(aux.first<n-1) abajo = (mapa[aux.first+1][aux.second]!='X');//or (mapa[aux.first+1][aux.second]=='t');
		bool izq;
		if(aux.second>0)izq = (mapa[aux.first][aux.second-1]!='X');//or (mapa[aux.first][aux.second-1]=='t');
		bool der;
		if(aux.second<m-1)der = (mapa[aux.first][aux.second+1]!='X');//or (mapa[aux.first][aux.second+1]=='t'));
		

		if(aux.first>0 and arriba and not visit[aux.first-1][aux.second]){
			visit[aux.first-1][aux.second]=true;
			if(mapa[aux.first-1][aux.second]=='t'){
				distancias.push((puntu[aux.first][aux.second] +1));
								aux2.first=aux.first-1;
				aux2.second=aux.second;
				puntu[aux2.first][aux2.second]=puntu[aux.first][aux.second] +1;
				pila.push(aux2);
			 }
				 
			else {
				aux2.first=aux.first-1;
				aux2.second=aux.second;
				puntu[aux2.first][aux2.second]=puntu[aux.first][aux.second] +1;
				pila.push(aux2);

			}
		}
		if(aux.first<n-1 and abajo and not visit[aux.first+1][aux.second]){
			visit[aux.first+1][aux.second]=true;
			if(mapa[aux.first+1][aux.second]=='t'){
				distancias.push((puntu[aux.first][aux.second] +1));
								aux2.first=aux.first+1;
				aux2.second=aux.second;
				puntu[aux2.first][aux2.second]=puntu[aux.first][aux.second] +1;
				pila.push(aux2);
			 }
			 else {
				aux2.first=aux.first+1;
				aux2.second=aux.second;
				puntu[aux2.first][aux2.second]=puntu[aux.first][aux.second] +1;
				pila.push(aux2);
			}
		}
		if(aux.second>0 and izq and not visit[aux.first][aux.second-1]){
			visit[aux.first][aux.second-1]=true;
			if(mapa[aux.first][aux.second-1]=='t'){
				distancias.push((puntu[aux.first][aux.second] +1));
								aux2.first=aux.first;
				aux2.second=aux.second-1;
				puntu[aux2.first][aux2.second]=puntu[aux.first][aux.second] +1;
				pila.push(aux2);
			}
			 else {
				aux2.first=aux.first;
				aux2.second=aux.second-1;
				puntu[aux2.first][aux2.second]=puntu[aux.first][aux.second] +1;
				pila.push(aux2);
			}
		}
		if(aux.second<m-1 and der and not visit[aux.first][aux.second+1]){
			visit[aux.first][aux.second+1] = true;
			if(mapa[aux.first][aux.second+1]=='t'){
				aux2.first=aux.first;
				aux2.second=aux.second+1;
				puntu[aux2.first][aux2.second]=puntu[aux.first][aux.second] +1;
				pila.push(aux2);
				distancias.push((puntu[aux.first][aux.second] +1));
			}
			 else {
				aux2.first=aux.first;
				aux2.second=aux.second+1;
				puntu[aux2.first][aux2.second]=puntu[aux.first][aux.second] +1;
				pila.push(aux2);
			}
		}
		/*for(int i=0; i<n;++i){
			for(int j=0; j<m;++j){
				cout << puntu[i][j]<< " ";
			}
		cout <<endl;
		}
		cout <<endl;*/

	}
	
	if(not distancias.empty()){
			int max=distancias.top();distancias.pop();
			while(not distancias.empty()){
				int a=distancias.top();distancias.pop();
				if(max<a)max=a;
			}
		cout << "distancia maxima: "<<max<<endl;  
	}

	else 			cout << "no es pot arribar a cap tresor"<<endl;
}
