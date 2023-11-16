#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,p=1,t[N],f[N][2][2],f2[2][2],b[N],fa[N],ga[N];
bool g[N],g1[N],g2[N],h[N];
struct road
{
    int m,q;
}a[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
int find(int x,int k)
{
    while(fa[x]!=k) x=fa[x];
    return ga[x];
}
void dfs(int x)
{
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa[x]||g[i]==true) continue;
        if(h[a[i].m]==true)
        {
            g[i]=g[i^1]=true;
            g1[x]=true;
            g2[find(x,a[i].m)]=true;
            continue;
        }
        fa[a[i].m]=x;
        ga[a[i].m]=i;
        dfs(a[i].m);
    }
}
void dfs2(int x)
{
    h[x]=true;
    if(g1[x]==true) f[x][0][0]=0,f[x][0][1]=f[x][1][0]=-1e9,f[x][1][1]=b[x];
    else f[x][0][0]=0,f[x][1][0]=b[x],f[x][0][1]=f[x][1][1]=-1e9;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]==true) continue;
        dfs2(a[i].m);
        for(int j=0;j<=1;++j)
        {
            for(int k=0;k<=1;++k) f2[j][k]=f[x][j][k],f[x][j][k]=-1e9;
        }
        for(int j1=0;j1<=1;++j1)
        {
            for(int j2=0;j2<=1;++j2)
            {
                if(j1==1&&j2==1) continue;
                for(int k1=0;k1<=1;++k1)
                {
                    for(int k2=0;k2<=1;++k2)
                    {
                        if(g2[i]==true&&j1==1&&k2==1) continue;
                        if(g2[i]==true) f[x][j1][k1]=max(f[x][j1][k1],f2[j1][k1]+f[a[i].m][j2][k2]);
                        else f[x][j1][k1|k2]=max(f[x][j1][k1|k2],f2[j1][k1]+f[a[i].m][j2][k2]);
                    }
                }
            }
        }
    }
    // printf("%d:%d %d %d %d\n",x,f[x][0][0],f[x][1][0],f[x][0][1],f[x][1][1]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    dfs(1);
    for(int i=1;i<=n;++i) h[i]=false;
    dfs2(1);
    printf("%d",max(max(f[1][0][0],f[1][1][0]),max(f[1][0][1],f[1][1][1])));
    return 0;
}