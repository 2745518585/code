#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int main()
{
    vector<int> a({1,1,2,2,3});
    a.resize(unique(a.begin(),a.end())-a.begin());
    for(auto i:a) printf("%d ",i);printf("\n");
    return 0;
}