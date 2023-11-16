#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,k;
ll s;
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=sqrt(k);++i)
    {
        int x=k/(i+1)+1,y=min(k/i,n);
        s+=(ll)i*(x+y)*(y-x+1)/2;
        if(k/i!=i) s+=(ll)(k/i)*i;
    }
    printf("%lld",(ll)k*n-s);
    return 0;
}