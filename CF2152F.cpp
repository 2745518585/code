#include<cstdio>
#include<algorithm>
#include<tuple>
using namespace std;
const int N=1000001,M=21;
int n,m,q,a[N],d[N],f[N][M],g[N][M],h[N][M];
pair<int,int> find(int x,int y)
{
    int t=0,s=0;
    if(d[x]<d[y]) swap(x,y);
    while(t>=0)
    {
        if(d[f[x][t]]>d[y]) x=f[x][t],s+=(1<<t),++t;
        else --t;
    }
    if(d[x]>d[y]) x=f[x][0],++s;
    if(x==y) return make_pair(x,s);
    t=0;
    while(t>=0)
    {
        if(f[x][t]!=f[y][t])
        {
            s+=(1<<t)*2;
            x=f[x][t];
            y=f[y][t];
            ++t;
        }
        else --t;
    }
    x=f[x][0];
    y=f[y][0];
    s+=2;;
    return make_pair(x,s);
}
int sum(int x,int r)
{
    int t=0,s=0;
    while(t>=0)
    {
        if(g[x][t]<=r) s+=h[x][t],x=g[x][t],++t;
        else --t;
    }
    if(x==r) return s-1;
    int y=x+1;
    t=0;
    while(t>=0)
    {
        if(f[x][t]<=r) s+=(1<<t),x=f[x][t],++t;
        else --t;
    }
    t=0;
    while(t>=0)
    {
        if(f[y][t]<=r) s+=(1<<t),y=f[y][t],++t;
        else --t;
    }
    return s;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1,j=1;i<=n;++i)
        {
            while(j<=n&&a[j]-a[i]<=m) ++j;
            f[i][0]=j;
        }
        d[n+1]=0;
        for(int i=n;i>=1;--i) d[i]=d[f[i][0]]+1;
        f[n+1][0]=n+1;
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n+1;++j)
            {
                f[j][i]=f[f[j][i-1]][i-1];
            }
        }
        for(int i=1;i<=n;++i)
        {
            tie(g[i][0],h[i][0])=find(i,i+1);
        }
        g[n+1][0]=n+1,h[n+1][0]=0;
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n+1;++j)
            {
                g[j][i]=g[g[j][i-1]][i-1];
                h[j][i]=h[j][i-1]+h[g[j][i-1]][i-1];
            }
        }
        // for(int i=1;i<=n;++i)
        // {
        //     for(int j=0;j<=3;++j) printf("%d %d: %d %d %d\n",i,j,f[i][j],g[i][j],h[i][j]);
        // }
        scanf("%d",&q);
        for(int i=1;i<=q;++i)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",sum(l,r)+2);
        }
    }
    return 0;
}