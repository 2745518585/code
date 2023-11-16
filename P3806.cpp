#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001,M=1001,K=10000001;
int n,m,q,t[N],p=1,tot,p2,r,q1,q2,b[M],h1[N];
bool g[N],h2[K<<1],l[M];
struct tree
{
    int s,ms,d;
}T[N];
struct road
{
    int m,q,w;
}a[N<<1];
struct road2
{
    int x,y,w;
}a2[N];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void rebuild(int x,int fa)
{
    int z=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(z==0)
        {
            a2[++p2]=(road2){x,a[i].m,a[i].w};
            z=x;
        }
        else
        {
            a2[++p2]=(road2){z,++tot,0};
            a2[++p2]=(road2){tot,a[i].m,a[i].w};
            z=tot;
        }
        rebuild(a[i].m,x);
    }
}
void dfs1(int x,int fa)
{
    T[x].s=1;
    T[x].ms=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        dfs1(a[i].m,x);
        T[x].s+=T[a[i].m].s;
        T[x].ms=max(T[x].ms,T[a[i].m].s);
    }
    T[x].ms=max(T[x].ms,q-T[x].s);
    if(T[x].ms<T[r].ms) r=x;
}
void dfs2(int x,int fa)
{
    if(T[x].d>K) return;
    if(x<=n) h1[++q2]=T[x].d;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        T[a[i].m].d=T[x].d+a[i].w;
        dfs2(a[i].m,x);
    }
}
void solve(int x)
{
    q1=q2=0;
    h2[0]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        T[a[i].m].d=a[i].w;
        dfs2(a[i].m,x);
        for(int j=q1+1;j<=q2;++j)
        {
            for(int k=1;k<=m;++k)
            {
                if(h1[j]<=b[k]&&h2[b[k]-h1[j]]) l[k]=true;
            }
        }
        for(int j=q1+1;j<=q2;++j) h2[h1[j]]=true;
        q1=q2;
    }
    for(int i=1;i<=q2;++i) h2[h1[i]]=false;
}
void dfs(int x)
{
    dfs1(x,0);
    r=0;
    q=T[x].s;
    dfs1(x,0);
    solve(r);
    g[r]=true;
    for(int i=t[r];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        dfs(a[i].m);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    tot=n;
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    rebuild(1,0);
    p=1;
    for(int i=1;i<=n;++i) t[i]=0;
    for(int i=1;i<=p2;++i)
    {
        road(a2[i].x,a2[i].y,a2[i].w);
        road(a2[i].y,a2[i].x,a2[i].w);
    }
    for(int i=1;i<=m;++i) scanf("%d",&b[i]);
    T[1].s=n;
    T[0].ms=1e9;
    dfs(1);
    for(int i=1;i<=m;++i)
    {
        if(l[i]) printf("AYE\n");
        else printf("NAY\n");
    }
    return 0;
}