#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const ll N=3001;
ll n,m,w,b[N],c[N];
ll g[N][N];
struct str
{
    ll x,s;
    str(){}
    str(ll x,ll s):x(x),s(s){}
}f[N];
str min(str a,str b)
{
    if(a.x!=b.x) return a.x<b.x?a:b;
    return a.s>b.s?a:b;
}
bool cmp(ll x,ll y)
{
    return b[x]<b[y];
}
void check(ll x)
{
    for(ll i=1;i<=n;++i)
    {            
        if(g[x][i]==1e18) continue;
        str z=str(f[x].x,f[x].s);
        if(g[x][i]<=f[x].s) z.s-=g[x][i];
        else
        {
            ll u=(g[x][i]-f[x].s)/b[x];
            if(u*b[x]+f[x].s<g[x][i]) ++u;
            z.x+=u;
            z.s=u*b[x]+f[x].s-g[x][i];
        }
        f[i]=min(f[i],z);
    }
}
int main()
{
    ll T;
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld%lld",&n,&m,&w);
        for(ll i=1;i<=n;++i)
        {
            scanf("%lld",&b[i]);
            c[i]=i;
        }
        sort(c+1,c+n+1,cmp);
        for(ll i=1;i<=n;++i)
        {
            for(ll j=1;j<=n;++j) g[i][j]=g[j][i]=1e18;
        }
        for(ll i=1;i<=n;++i) g[i][i]=0;
        for(ll i=1;i<=m;++i)
        {
            ll x,y,w;
            scanf("%lld%lld%lld",&x,&y,&w);
            g[x][y]=min(g[x][y],w);
        }
        for(ll k=1;k<=n;++k)
        {
            for(ll i=1;i<=n;++i)
            {
                for(ll j=1;j<=n;++j)
                {
                    g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
                }
            }
        }
        for(ll i=1;i<=n;++i) f[i]=str(1e18,1e18);
        f[1]=str(0,w);
        for(ll i=1;i<=n;++i) check(c[i]);
        printf("%lld\n",f[n].x>1e16?-1:f[n].x);
    }
    return 0;
}