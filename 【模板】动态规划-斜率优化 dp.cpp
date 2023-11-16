#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N],Q[N*2],T=0,R=0;
ll b[N],c[N],f[N];
double abc(int x,int y)
{
    if(c[x]==c[y]) return 1e18;
    return double((f[x]+c[x]*c[x])-(f[y]+c[y]*c[y]))/(c[x]-c[y]);
}
int main()
{
    scanf("%d%d",&n,&m);
    c[0]=m+1;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=b[i-1]+a[i]+1;
        c[i]=c[i-1]+a[i]+1;
    }
    for(int i=1;i<=n;++i)
    {
        while(T<R&&abc(Q[T],Q[T+1])<2*b[i]) ++T;
        f[i]=f[Q[T]]+b[i]*b[i]-2*b[i]*c[Q[T]]+c[Q[T]]*c[Q[T]];
        while(T<R&&abc(Q[R],i)<abc(Q[R-1],Q[R])) --R;
        Q[++R]=i;
    }
    printf("%lld",f[n]);
    return 0;
}