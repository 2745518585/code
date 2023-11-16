#include<bits/stdc++.h>
using namespace std;
const int N=1000001;
typedef long long ll;
int n,m,g[N],Q[N],T,R;
ll a[N],f[N];
double abc(int x,int y)
{
    return (double)((f[x]+a[x]*a[x])-(f[y]+a[y]*a[y]))/(a[x]-a[y]);
}
int solve(ll x)
{
    T=1,R=0;
    Q[++R]=0;
    for(int i=1;i<=n;++i) f[i]=g[i]=0;
    for(int i=1;i<=n;++i)
    {
        while(T<R&&abc(Q[T],Q[T+1])<=2*a[i]) ++T;
        f[i]=f[Q[T]]+(a[i]-a[Q[T]])*(a[i]-a[Q[T]])+x;
        g[i]=g[Q[T]]+1;
        while(T<R&&abc(Q[R-1],Q[R])>=abc(Q[R],i)) --R;
        Q[++R]=i;
    }
    return g[n];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        a[i]+=a[i-1];
    }
    ll l=0,r=2e18;
    while(l<r)
    {
        ll z=l+r+1>>1;
        if(solve(z)>=m) l=z;
        else r=z-1;
    }
    solve(l);
    printf("%lld",(f[n]-l*m)+2*a[n]+m);
    return 0;
}