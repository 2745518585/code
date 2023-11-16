#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=101;
ll n,k,t,f[N],g[N];
ll dfs(ll x,ll n)
{
    if(n==0) return 0;
    if(n<f[x-1]) return dfs(x-1,n);
    return g[x-1]+(f[x-1]<=k)+dfs(x-2,n-f[x-1]);
}
int main()
{
    f[1]=1,f[2]=2;
    t=2;
    while(true)
    {
        if(f[t]+f[t-1]>3e18) break;
        ++t;
        f[t]=f[t-1]+f[t-2];
    }
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld",&k,&n);
        g[1]=0;
        for(int i=2;i<=t;++i)
        {
            g[i]=g[i-1]+g[i-2]+(f[i-1]<=k);
        }
        printf("%lld\n",dfs(t,n-1));
    }
    return 0;
}