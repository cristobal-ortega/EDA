 
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void vinga(int i, vector<string>& v,vector<bool> b,vector<string>& c){
    int n=v.size();
    if(i==n ){
        cout << "(";
        bool primer=true;
        for(int i=0;i<n;++i){
            if(primer){
				 cout << c[i];
				 primer=false;
			 }
            else cout << ","<<c[i];

        }
        cout << ")";
        cout <<endl;
    }
    else{
            for(int j=0; j<n; ++j){
				if(not b[j]){
					c[i]=v[j];
					b[j]=true;
					vinga(i+1,v,b,c);
					b[j]=false;
				}
			}
    }

}












int main(){
    int n;
    cin >> n;
    vector<string> v(n);
    vector<string> c(n);
    for(int i=0; i<n; ++i) cin >> v[i];
    vector<bool> b(n,false);
    //vector<string> r(n);
    vinga(0,v,b,c);
}
