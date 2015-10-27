 
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void vinga(int i, vector<string>& v, vector<bool>& b, int m){
    int n=v.size();
    if(i==n and m==0){
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
    else if (n-i>=m){
			if(m>0){
				b[i]=true;
				vinga(i+1,v,b,m-1);
			}
            b[i]=false;
            vinga(i+1,v,b,m);
    }

}





int main(){
    int n,m;
    cin >> m >> n;
    vector<string> v(n);
    vector<bool> b(n,false);
    for(int i=0; i<n; ++i) cin >> v[i];
    //vector<string> r(n);
    vinga(0,v,b,m);
}
