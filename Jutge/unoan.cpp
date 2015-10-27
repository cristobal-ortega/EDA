 
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void vinga(int i, vector<int>& v,vector<bool> b){
    int n=v.size();
    if(i==n ){
        cout << "(";
        bool primer=true;
        for(int i=0;i<n;++i){
            if(primer){
				 cout << v[i]+1;
				 primer=false;
			 }
            else cout << ","<<v[i]+1;

        }
        cout << ")";
        cout <<endl;
    }
    else{
            for(int j=0; j<n; ++j){
				if(not b[j]){
					v[i]=j;
					b[j]=true;
					vinga(i+1,v,b);
					b[j]=false;
				}
			}
    }

}












int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    vector<bool> b(n,false);
    //vector<string> r(n);
    vinga(0,v,b);
}
