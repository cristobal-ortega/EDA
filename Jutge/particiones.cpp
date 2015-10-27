 
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void vinga(int i, vector<string>& v, vector<int>& c, int p){
    int n=v.size();
    if(i==n){
		for(int j=0; j<p; ++j){;
			cout << "subconjunt "<<j+1<<": "; 
			cout << "{";
			bool primer=true;
			for(int k=0;k<n;++k){
				if(primer and c[k]==j){
					 cout << v[k];
					 primer=false;
				 }
				else if(c[k]==j) cout << ","<<v[k];
			}
			cout << "}";
			cout <<endl;
		}
		cout <<endl;

    }
    else{
		for(int j=0; j<p; ++j){
			c[i]=j;
			vinga(i+1,v,c,p);
		}
	}

}





int main(){
    int n,p;
    cin >> n;
    vector<string> v(n);
    vector<int> c(n,0);
    for(int i=0; i<n; ++i) cin >> v[i];
    cin >> p;
    vinga(0,v,c,p);
}
