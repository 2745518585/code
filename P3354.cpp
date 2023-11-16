#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=201;
int n,m,p=1,t[N];
ll b[N],c[N],f[N][N][N],g[N][N][N];
bool h[N][N];
struct road
{
    int m,q,w;
}a[N];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void dfs0(int x,int fa)
{
    for(int i=1;i<=n;++i)
    {
        h[x][i]=h[fa][i];
    }
    h[x][x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        c[a[i].m]=c[x]+a[i].w;
        dfs0(a[i].m,x);
    }
}
void dfs(int x)
{
    for(int i=0;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            f[x][i][j]=1e18;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(h[x][i]==false) continue;
        f[x][i==x][i]=(c[x]-c[i])*b[x];
    }
    for(int i=t[x];i!=0;i=a[i].q)
    {
        dfs(a[i].m);
        for(int j=0;j<=m;++j)
        {
            for(int k=1;k<=n;++k)
            {
                if(h[x][k]==false) continue;
                g[x][j][k]=f[x][j][k];
                f[x][j][k]=1e18;
            }
        }
        for(int j=0;j<=m;++j)
        {
            for(int k=0;k<=j;++k)
            {
                for(int l=1;l<=n;++l)
                {
                    if(h[x][l]==false) continue;
                    f[x][j][l]=min(f[x][j][l],min(f[a[i].m][k][l],f[a[i].m][k][a[i].m])+g[x][j-k][l]);
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    ++n,++m;
    for(int i=2;i<=n;++i)
    {
        int x,w;
        scanf("%d%d%d",&b[i],&x,&w);
        road(x+1,i,w);
    }
    b[1]=0;
    dfs0(1,0);
    dfs(1);
    printf("%lld",f[1][m][1]);
    return 0;
}