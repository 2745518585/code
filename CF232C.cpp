#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
typedef long long ll;
int m,n,q;
ll a[N],b[N];
pair<ll,ll> f[N],g[N];
pair<ll,ll> solve(ll x,ll t,pair<ll,ll> *f)
{
    if(t<=0) return f[t]=make_pair(0,0);
    if(t==1)
    {
        if(x==1) return f[t]=make_pair(0,1);
        else return f[t]=make_pair(1,0);
    }
    if(x<=a[t-1])
    {
        auto z=solve(x,t-1,f);
        return f[t]=make_pair(min(z.first,z.second+2),min(z.first,z.second)+1+b[t-2]);
    }
    else
    {
        auto z=solve(x-a[t-1],t-2,f);
        return f[t]=make_pair(z.first+1,z.second);
    }
}
int main()
{
    scanf("%d%d",&m,&n);
    a[0]=1,a[1]=2;
    b[0]=0,b[1]=1;
    for(int i=2;i<=n;++i)
    {
        a[i]=a[i-1]+a[i-2];
        b[i]=b[i-2]+1;
        if(a[i]>1e17)
        {
            n=i;
            break;
        }
    }
    for(int i=1;i<=m;++i)
    {
        ll x,y;
        scanf("%lld%lld",&x,&y);
        if(x>y) swap(x,y);
        solve(x,n,f);
        solve(y,n,g);
        ll s=1e18;
        int z=n;
        while(true)
        {
            auto z1=f[z],z2=g[z];
            s=min(s,z1.first+z2.first);
            if(y<=a[z-1]) --z;
            else if(x>a[z-1]) x-=a[z-1],y-=a[z-1],z-=2;
            else break;
        }
        auto z1=f[z-1],z2=g[z-2];
        s=min(s,min(z1.first,z1.second)+z2.first+1);
        printf("%lld\n",s);
    }
    return 0;
}