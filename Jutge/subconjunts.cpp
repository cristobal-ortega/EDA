 
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void vinga(int i, vector<string>& v, vector<bool>& b){
    int n=v.size();
    if(i==n){
        cout << "{";
        bool primer=true;
        for(int i=0;i<n;++i){
            if(primer and b[i]){
				 cout << v[i];
				 primer=false;
			 }
            else if(b[i]) cout << ","<<v[i];

        }
        cout << "}";
        cout <<endl;
    }
    else{
            b[i]=true;
            vinga(i+1,v,b);
            b[i]=false;
            vinga(i+1,v,b);
    }

}












int main(){
    int n;
    cin >> n;
    vector<string> v(n);
    vector<bool> b(n,false);
    for(int i=0; i<n; ++i) cin >> v[i];
    //vector<string> r(n);
    vinga(0,v,b);
}
