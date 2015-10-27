 
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void vinga(int i, vector<int>& v, vector<bool>& b,int s,int max){
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
    else if(s<=max and i<n and s>=0){
			max = max - v[i];
            b[i]=true;
            vinga(i+1,v,b,s-v[i],max);
            b[i]=false;
            vinga(i+1,v,b,s,max);
    }

}












int main(){
    int n,s,max;
    cin >> s >> n;
    vector<int> v(n);
    vector<bool> b(n,false);
    //max=0;
    for(int i=0; i<n; ++i){
		 cin >> v[i];
		 max +=v[i];
	 }
    //vector<string> r(n);
    cout << max<<endl;
    vinga(0,v,b,s,max);
}
