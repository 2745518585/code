#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,p=1,t[N],b[N],c[N],o[N],u,l[N];
ll f[N],g[N],g2[N],d[N],r1[N],r2[N];
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
bool cmp(int x,int y)
{
    return d[x]*(f[y]+2)>d[y]*(f[x]+2);
}
void dfs1(int x)
{
    d[x]=b[x];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        dfs1(a[i].m);
        d[x]+=d[a[i].m];
    }
    u=0;
    for(int i=t[x];i!=0;i=a[i].q) o[++u]=a[i].m;
    sort(o+1,o+u+1,cmp);
    for(int i=1;i<=u;++i)
    {
        g[x]+=g[o[i]]+d[o[i]]*(f[x]+1);
        f[x]+=f[o[i]]+2;
    }
}
void dfs2(int x)
{
    c[x]=0;
    d[x]=b[x];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        dfs2(a[i].m);
        d[x]+=d[a[i].m];
        c[x]=max(c[x],c[a[i].m]+1);
    }
    u=0;
    for(int i=t[x];i!=0;i=a[i].q) o[++u]=a[i].m;
    sort(o+1,o+u+1,cmp);
    for(int i=1;i<=u;++i)
    {
        g[x]+=g[o[i]]+d[o[i]]*(f[x]+1);
        f[x]+=f[o[i]]+2;
        l[o[i]]=i;
    }
    if(u==0) return;
    r1[0]=0;
    for(int i=1;i<=u;++i) r1[i]=r1[i-1]+(f[o[i]]+2);
    r2[u+1]=0;
    for(int i=u;i>=1;--i) r2[i]=r2[i+1]+d[o[i]];
    g2[x]=5e18;
    for(int i=1;i<=u;++i)
    {
        if(c[o[i]]+1==c[x]) g2[x]=min(g2[x],g[x]-g[o[i]]+g2[o[i]]-(r1[i-1]+1)*d[o[i]]-r2[i+1]*(f[o[i]]+2)+(f[x]-(f[o[i]]+2)+1)*d[o[i]]);
    }
}
int main()
{
    int z;
    scanf("%d%d",&n,&z);
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d%d",&x,&b[i]);
        road(x,i);
    }
    if(z==0)
    {
        dfs1(1);
        printf("%lld %lld\n",f[1],g[1]);
    }
    else if(z==1)
    {
        dfs2(1);
        printf("%lld %lld\n",f[1]-c[1],g2[1]);
        return 0;
    }
    return 0;
}