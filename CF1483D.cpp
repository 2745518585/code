#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
int n,m,q;
ll f[N][N],g[N][N];
struct road
{
    int x,y;
    ll w;
}a[N*N];
bool check(int x,int y,ll w)
{
    for(int i=1;i<=n;++i)
    {
        if(g[i][x]+w<=f[i][y]) return true;
    }
    return false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) g[i][j]=1e18;
        g[i][i]=0;
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        a[i].x=x,a[i].y=y,a[i].w=w;
        g[x][y]=min(g[x][y],w);
        g[y][x]=min(g[y][x],w);
    }
    for(int k=1;k<=n;++k)
    {
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) f[i][j]=-1e18;
    }
    scanf("%d",&q);
    for(int i=1;i<=q;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        if(g[x][y]>w) continue;
        for(int j=1;j<=n;++j)
        {
            f[x][j]=max(f[x][j],w-g[j][y]);
            f[y][j]=max(f[y][j],w-g[j][x]);
        }
    }
    int s=0;
    for(int i=1;i<=m;++i)
    {
        if(check(a[i].x,a[i].y,a[i].w)||check(a[i].y,a[i].x,a[i].w)) ++s;
    }
    printf("%d",s);
    return 0;
}