#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200001;
int n,m,a[N],ls=1,rs=0;
ll s,b[N],f[N],g[N];
void add(int x)
{
    s+=b[x];
    ++b[x];
}
void del(int x)
{
    --b[x];
    s-=b[x];
}
ll sum(int l,int r)
{
    while(l<ls) add(a[--ls]);
    while(r>rs) add(a[++rs]);
    while(l>ls) del(a[ls++]);
    while(r<rs) del(a[rs--]);
    return s;
}
void solve(int l,int r,int ml,int mr)
{
    if(l>r||ml>mr) return;
    int z=l+r>>1;
    ll w=1e18,q=0;
    for(int i=ml;i<=min(z-1,mr);++i)
    {
        ll t=sum(i+1,z);
        if(g[i]+t<w) w=g[i]+t,q=i;
    }
    f[z]=w;
    solve(l,z-1,ml,q);
    solve(z+1,r,q,mr);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i) f[i]=1e18;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j) g[j]=f[j];
        solve(1,n,0,n);
    }
    printf("%lld",f[n]);
    return 0;
}