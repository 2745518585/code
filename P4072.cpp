#include<cstdio>
#include<algorithm>
using namespace std;
const int M=10001,N=10001;
int n,m,a[N],Q[N*2],T=0,R=0,f[N],g[N];
int abc(int x,int y)
{
    if(a[x]==a[y]) return 1e9;
    return ((g[x]+a[x]*a[x])-(g[y]+a[y]*a[y]))/(a[x]-a[y]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        a[i]=a[i-1]+x;
        g[i]=1e9;
    }
    g[0]=0;
    for(int i=1;i<=m;++i)
    {
        T=0,R=0;
        for(int j=1;j<=n;++j)
        {
            while(T<R&&abc(Q[T],Q[T+1])<2*a[j]) ++T;
            f[j]=g[Q[T]]+(a[j]-a[Q[T]])*(a[j]-a[Q[T]]);
            while(T<R&&abc(Q[R],j)<abc(Q[R-1],Q[R])) --R;
            Q[++R]=j;
        }
        for(int j=1;j<=n;++j) g[j]=f[j];
    }
    printf("%d",f[n]*m-a[n]*a[n]);
    return 0;
}