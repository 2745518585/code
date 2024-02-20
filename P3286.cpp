#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
typedef long long ll;
const int N=51,M=1001;
int n,m,k,a[N];
ll f[N][M][2],g[N][M][2];
pair<ll,ll> dfs(int x,int t,bool u)
{
    if(x==0) return make_pair(0,t==m);
    if(f[x][t][u]!=-1) return make_pair(f[x][t][u],g[x][t][u]);
    f[x][t][u]=g[x][t][u]=0;
    for(int i=0;i<=(u?a[x]:k-1)&&t+i<=m;++i)
    {
        auto z=dfs(x-1,t+i,u&&i==a[x]);
        if(t>m/2) z.first+=z.second*(m-t);
        f[x][t][u]+=z.first,g[x][t][u]+=z.second;
    }
    if(t<=m/2) f[x][t][u]+=g[x][t][u]*t;
    return make_pair(f[x][t][u],g[x][t][u]);
}
int main()
{
    ll l,r;
    scanf("%lld%lld%d",&l,&r,&k);
    ll s=0;
    {
        --l;
        n=0;
        while(l) a[++n]=l%k,l/=k;
        for(m=0;m<=500;++m)
        {
            memset(f,-1,sizeof(f));
            memset(g,-1,sizeof(g));
            s-=dfs(n,0,true).first;
        }
    }
    {
        n=0;
        while(r) a[++n]=r%k,r/=k;
        for(m=0;m<=500;++m)
        {
            memset(f,-1,sizeof(f));
            memset(g,-1,sizeof(g));
            s+=dfs(n,0,true).first;
        }
    }
    printf("%lld",s);
    return 0;
}