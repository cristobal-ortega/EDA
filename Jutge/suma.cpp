 
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void vinga(int i, vector<int>& v, vector<bool>& b,int s){
    int n=v.size();
    if(i==n and s==0){
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
    else if(i<n){
            b[i]=true;
            vinga(i+1,v,b,s-v[i]);
            b[i]=false;
            vinga(i+1,v,b,s);
    }

}












int main(){
    int n,s;
    cin >> s >> n;
    vector<int> v(n);
    vector<bool> b(n,false);
    for(int i=0; i<n; ++i) cin >> v[i];
    //vector<string> r(n);
    vinga(0,v,b,s);
}
