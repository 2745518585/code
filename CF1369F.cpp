#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,f[N][2];
int sum(ll x,ll y)
{
    if(x>y) return 0;
    if(y%2==1) return x%2;
    if(x>y/2) return x%2^1;
    if(x>y/4) return 0;
    return sum(x,y/4);
}
int main()
{
    scanf("%d",&n);
    f[0][0]=0;
    f[0][1]=1;
    for(int i=1;i<=n;++i)
    {
        ll x,y;
        scanf("%lld%lld",&x,&y);
        int z1=sum(x,y/2),z2=sum(x,y);
        f[i][0]=f[i-1][z1];
        f[i][1]=f[i-1][z2];
    }
    printf("%d %d",f[n][1]^1,f[n][0]^1);
    return 0;
}