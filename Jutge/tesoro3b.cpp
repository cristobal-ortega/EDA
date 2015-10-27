#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;



int main(){
	int n,m;
	cin >> n >> m;
	vector< vector<char> > mapa(n,vector<char>(m));
	vector< vector<bool> > visit(n,vector<bool>(m,false));
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
	int trobat=0;
	cin >> aux.first >> aux.second;
	stack< pair <int,int> > pila;
	
	--aux.first;
	--aux.second;
	//if(mapa[aux.first][aux.second]=='t') trobat = true;
	visit[aux.first][aux.second]=true;
	pila.push(aux);
	while(not pila.empty()){
		  //arriba
		aux=pila.top();
		pila.pop();
		//cout << "visitando " << aux.first << " "<<aux.second<<endl;
		visit[aux.first][aux.second]=true;
		/*char yoquese;
		cin >> yoquese;
		*/
		pair<int,int> aux2;
		bool arriba;
		if(aux.first>0) arriba = visit[aux.first-1][aux.second];
		bool abajo;
		if(aux.first<n-1) abajo = visit[aux.first+1][aux.second];
		bool izq;
		if(aux.second>0)izq = visit[aux.first][aux.second-1];
		bool der;
		if(aux.second<m-1)der = visit[aux.first][aux.second+1];
		
		bool arribax;
		if(aux.first>0) arribax = mapa[aux.first-1][aux.second]=='X';
		bool abajox;
		if(aux.first<n-1) abajox = mapa[aux.first+1][aux.second]=='X';
		bool izqx;
		if(aux.second>0)izqx = mapa[aux.first][aux.second-1]=='X';
		bool derx;
		if(aux.second<m-1)derx = mapa[aux.first][aux.second+1]=='X';
		
		
		/*if(aux.first<n-1 and aux.first > 0 and aux.second < m-1 and aux.second >0){
			cout << mapa[aux.first-1][aux.second] <<endl;
			cout << visit[aux.first-1][aux.second] <<endl;
		}*/
		//mapa[aux.first-1][aux.second]!='X'
		if(aux.first>0 and not arribax and not arriba){
							aux2.first=aux.first-1;
				aux2.second=aux.second;
				//cout << "meto en pila: "<<aux2.first << " "<<aux2.second<<endl;
				pila.push(aux2);
			visit[aux.first-1][aux.second]=true;
			if(mapa[aux.first-1][aux.second]=='t') ++trobat;
		}
		//abajo mapa[aux.first+1][aux.second]!='X'
		if(aux.first<n-1 and not abajox and not abajo){
			//cout << "abajo"<<endl;
			visit[aux.first+1][aux.second]=true;
							aux2.first=aux.first+1;
				aux2.second=aux.second;
				//			cout << "meto en pila: "<<aux2.first << " "<<aux2.second<<endl;
				pila.push(aux2);
			if(mapa[aux.first+1][aux.second]=='t') trobat++;

		}
		//izquierda mapa[aux.first][aux.second-1]!='X'
		if(aux.second>0 and not izqx and not izq){
			//cout << "izquierda"<<endl;
			visit[aux.first][aux.second-1]=true;
							aux2.first=aux.first;
				aux2.second=aux.second-1;
				//		cout << "meto en pila: "<<aux2.first << " "<<aux2.second<<endl;
				pila.push(aux2);
			if(mapa[aux.first][aux.second-1]=='t') trobat++;

		}
		//derecha mapa[aux.first][aux.second+1]!='X'
		if(aux.second<m-1 and not derx and not der){
			//cout << "derecha"<<endl;
			visit[aux.first][aux.second+1]=true;
							aux2.first=aux.first;
				aux2.second=aux.second+1;
				//cout << "meto en pila: "<<aux2.first << " "<<aux2.second<<endl;
				pila.push(aux2);
			if(mapa[aux.first][aux.second+1]=='t') trobat++;

		}
		
		//if((arriba or arribax) and (abajo or abajox) and (izq or izqx) and (der or derx)){
			// pila.pop();
			 //cout << "quitando de pila: "<<aux.first << " " <<aux.second<<endl;
		// }
	}
   cout << trobat<<endl;
}
