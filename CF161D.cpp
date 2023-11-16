#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100001;
int n,m,q,t[N],p=1,r,q1,q2,h1[N],h2[N];
bool g[N];
ll s;
struct tree
{
    int s,ms,d;
}T[N];
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
    if(T[x].d>m) return;
    h1[++q2]=T[x].d;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        T[a[i].m].d=T[x].d+1;
        dfs2(a[i].m,x);
    }
}
void sum(int x)
{
    q1=q2=0;
    h2[0]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        T[a[i].m].d=1;
        dfs2(a[i].m,x);
        for(int j=q1+1;j<=q2;++j)
        {
            if(h1[j]<=m) s+=h2[m-h1[j]];
        }
        for(int j=q1+1;j<=q2;++j) ++h2[h1[j]];
        q1=q2;
    }
    for(int i=1;i<=q2;++i) h2[h1[i]]=0;
}
void dfs(int x)
{
    r=0;
    q=T[x].s;
    dfs1(x,0);
    sum(r);
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
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    T[1].s=n;
    T[0].ms=1e9;
    dfs(1);
    printf("%lld",s);
    return 0;
}