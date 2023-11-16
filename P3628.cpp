#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3000001;
int n,a,b,c,Q[N*2],T=0,R=0;
ll d[N],f[N];
ll abc(int x,int y)
{
    if(d[x]==d[y]) return 1e18;
    return ((f[x]+a*d[x]*d[x]-b*d[x])-(f[y]+a*d[y]*d[y]-b*d[y]))/(d[x]-d[y]);
}
int main()
{
    scanf("%d%d%d%d",&n,&a,&b,&c);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        d[i]=d[i-1]+x;
    }
    for(int i=1;i<=n;++i)
    {
        while(T<R&&abc(Q[T],Q[T+1])>2*a*d[i]) ++T;
        f[i]=f[Q[T]]+a*(d[i]-d[Q[T]])*(d[i]-d[Q[T]])+b*(d[i]-d[Q[T]])+c;
        while(T<R&&abc(Q[R-1],Q[R])<abc(Q[R],i)) --R;
        Q[++R]=i;
    }
    printf("%lld",f[n]);
    return 0;
}