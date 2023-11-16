#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100001,M=201;
int n,m,Q[N*2],h[M][N],T=0,R=0;
ll a[N],f[N],g[N];
ll abc(int x,int y)
{
    if(a[x]==a[y]) return 1e18;
    return ((g[x]-a[x]*a[x])-(g[y]-a[y]*a[y]))/(a[x]-a[y]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        a[i]=a[i-1]+x;
    }
    for(int i=1;i<=m;++i)
    {
        T=0,R=0;
        Q[0]=0;
        for(int j=1;j<=n;++j)
        {
            while(T<R&&abc(Q[T],Q[T+1])>-a[j]) ++T;
            f[j]=g[Q[T]]+a[Q[T]]*(a[j]-a[Q[T]]);
            h[i][j]=Q[T];
            while(T<R&&abc(Q[R],j)>abc(Q[R-1],Q[R])) --R;
            Q[++R]=j;
        }
        for(int j=1;j<=n;++j) g[j]=f[j];
    }
    printf("%lld\n",f[n]);
    for(int i=m,j=h[m][n];i>=1;j=h[--i][j]) printf("%d ",j);
    return 0;
}