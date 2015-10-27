 
#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool legal (int i,vector<int>& v) {
	for (int k=0; k<i; ++k) {
			if (v[k]==v[i] or v[i]-i==v[k]-k or v[i]+i==v[k]+k) {
			  return false;
			}   
		}
	return true;
}




void vinga(int i, vector<int>& v, int& a){
    int n=v.size();
    if(i==n ){
        ++a;
    }
    else{
            for(int j=0; j<n; ++j){
				v[i]=j;
				if(legal(i,v)){
					vinga(i+1,v,a);
				}
			}
    }

}












int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    int a=0;
    vinga(0,v,a);
    cout << a << endl;
}
