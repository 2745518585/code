#include<cstdio>
#include<algorithm>
using namespace std;
const int N=8001;
int n,m,k,p=1,tot,t[N],b[N],c[N],d[N],e[N];
bool g[N],h[N<<1],h2[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs0(int x,int fa)
{
    b[x]=c[x]=++tot;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(b[a[i].m]==0)
        {
            dfs0(a[i].m,x);
            c[x]=min(c[x],c[a[i].m]);
            if(c[a[i].m]>b[x]) g[i/2]=false;
        }
        c[x]=min(c[x],b[a[i].m]);
    }
}
void dfs(int x,int fa)
{
    h2[x]=true;
    d[++k]=x;
    int z;
    while(true)
    {
        z=1e9;
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(a[i].m==fa||h[i]==true||h2[a[i].m]==true) continue;
            z=min(z,a[i].m);
        }
        if(z!=1e9) dfs(z,x);
        else break;
    }
}
bool check()
{
    for(int i=1;i<=n;++i)
    {
        if(d[i]!=e[i]) return d[i]<e[i];
    }
    return false;
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
    if(m==n-1)
    {
        dfs(1,0);
        for(int i=1;i<=n;++i)
        {
            printf("%d ",d[i]);
        }
        return 0;
    }
    for(int i=1;i<=n;++i) g[i]=true;
    dfs0(1,0);
    e[1]=1e9;
    for(int i=1;i<=m;++i)
    {
        if(g[i]==true)
        {
            h[i*2]=h[i*2+1]=true;
            k=0;
            for(int j=1;j<=n;++j) h2[j]=false;
            dfs(1,0);
            if(check())
            {
                for(int j=1;j<=n;++j) e[j]=d[j];
            }
            h[i*2]=h[i*2+1]=false;
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d ",e[i]);
    }
    return 0;
}