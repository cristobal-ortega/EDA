 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


void vinga(int i, vector<int>& v, vector<bool>& b,int s,bool& acabar){
    int n=v.size();
    if(i==n and s==0 and not acabar){
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
        acabar=true;
    }
    else if(i<n and not acabar){
            b[i]=true;
            vinga(i+1,v,b,s-v[i],acabar);
            b[i]=false;
            vinga(i+1,v,b,s,acabar);
    }

}












int main(){
    int n,s;
    cin >> s >> n;
    vector<int> v(n);
    vector<bool> b(n,false);
    for(int i=0; i<n; ++i) cin >> v[i];
    sort(v.begin(),v.end(),greater<int>());
    //vector<string> r(n);
    bool acabar=false;
    vinga(0,v,b,s,acabar);
    if(not acabar) cout << "no solution"<<endl;
}
