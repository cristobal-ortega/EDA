#include <iostream>

using namespace std;

#define REQUIEM_VERSION "1.1"

typedef pair<int,int> PII;
typedef pair<int, PII> PIPII;

#define fori(n) for(int i=0;i<(int)n;++i)
#define forj(n) for(int j=0;j<(int)n;++j)

#define foreach(i,m) for(typeof((m).begin()) i=(m).begin();i!=(m).end();++i)

int s2i(const string &s);
