#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3000001;
int n,a[N],b[N],c[N],Q[N*2],T=0,R=0;
ll d[N],e[N],f[N];
ll abc(int x,int y)
{
    if(d[x]==d[y]) return 1e18;
    return ((f[x]+e[x])-(f[y]+e[y]))/(d[x]-d[y]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&a[i],&b[i],&c[i]);
        d[i]=d[i-1]+b[i];
        e[i]=e[i-1]+a[i]*b[i];
    }
    for(int i=1;i<=n;++i)
    {
        while(T<R&&abc(Q[T],Q[T+1])<a[i]) ++T;
        f[i]=f[Q[T]]+a[i]*(d[i]-d[Q[T]])-(e[i]-e[Q[T]])+c[i];
        while(T<R&&abc(Q[R-1],Q[R])>abc(Q[R],i)) --R;
        Q[++R]=i;
    }
    ll s=1e18;
    for(int i=n;i>=1;--i)
    {
        s=min(s,f[i]);
        if(b[i]) break;
    }
    printf("%lld",s);
    return 0;
}