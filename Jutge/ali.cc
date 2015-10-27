 
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

typedef set<int>::iterator Iterator;

int main(){
    /*vector<int> v(1);
    vector<int>::iterator it;
    make_heap (v.begin(), v.end());
    */
    cout.setf( ios_base::fixed, ios_base::floatfield );
	cout.precision( 0 );
    int n;
    cin >> n;
    set<int> cueva;
    set<int> bolsa;
    string com;
    double suma=0;
    int m;
    while (cin >> com){
        cin >> m;

       // cout << "tamaño bolsa "<<bolsa.size() << endl;
        if(com=="deixar"){
			Iterator b = bolsa.begin();
			int size = bolsa.size();
			//cout << "minimo en bolsa: "<< (*b) <<endl;
			//cout << "size bolsa: "<< size <<endl;
			if( bolsa.empty() or size < n){
				bolsa.insert(m);
				suma = suma + m;
			}
			else if(m > (*b)){
				cueva.insert(*b);
				suma = suma - (*b);
				bolsa.erase(b);
				bolsa.insert(m);
				suma = suma + m;
			}
			else cueva.insert(m);
			//cout << "Insertado en cueva"<<endl;
            
        }
        else if(com == "endur"){
			//cout << "borrado de cueva"<<endl;
			Iterator b = bolsa.find(m);
			if( b!=bolsa.end() ){
				suma = suma - (*b);
				bolsa.erase(b);
				Iterator c = cueva.end();
				if(cueva.begin() != cueva.end() ){
					--c;
					bolsa.insert(*c);
					cueva.erase(c);
					suma = suma + (*c);
				}
					
			}
			else cueva.erase(m);
        }
        cout <<suma << endl;
    }

}
