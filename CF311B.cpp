#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,k,Q[N*2],T=0,R=0;
ll a[N],b[N],c[N],f[N],g[N],s;
double abc(int x,int y)
{
    if(x==y) return -1e18;
    return double((g[x]+c[x])-(g[y]+c[y]))/(x-y);
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=2;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        a[i]+=a[i-1];
    }
    for(int i=1;i<=m;++i)
    {
        int x;
        ll t;
        scanf("%d%lld",&x,&t);
        b[i]=t-a[x];
    }
    sort(b+1,b+m+1);
    for(int i=1;i<=m;++i)
    {
        c[i]=c[i-1]+b[i];
        f[i]=i*b[i]-c[i];
    }
    s=f[m];
    for(int i=2;i<=k;++i)
    {
        T=R=0;
        Q[0]=0;
        for(int j=1;j<=m;++j) g[j]=f[j];
        for(int j=1;j<=m;++j)
        {
            while(T<R&&abc(Q[T],Q[T+1])<b[j]) ++T;
            f[j]=g[Q[T]]+b[j]*(j-Q[T])-(c[j]-c[Q[T]]);
            while(T<R&&abc(Q[R],j)<abc(Q[R-1],Q[R])) --R;
            Q[++R]=j;
        }
        s=min(s,f[m]);
    }
    printf("%lld",s);
    return 0;
}