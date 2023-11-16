#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=200001;
int n,m,k,q,t[N],p=1,r,q1,q2,h[N],T2[N];
bool g[N];
ll s;
struct tree
{
    int s,ms,d;
}T[N];
struct road
{
    int m,q,w;
}a[N<<1];
void add(int x,int q)
{
    T2[x]+=q;
    while(x<=k+1)
    {
        x+=(x&-x);
        T2[x]+=q;
    }
}
int num(int x)
{
    int s=T2[x];
    while(x>=1)
    {
        x-=(x&-x);
        s+=T2[x];
    }
    return s;
}
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
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
    if(T[x].d>k) return;
    h[++q2]=T[x].d;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        T[a[i].m].d=T[x].d+a[i].w;
        dfs2(a[i].m,x);
    }
}
void sum(int x)
{
    q1=q2=0;
    add(1,1);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        T[a[i].m].d=a[i].w;
        dfs2(a[i].m,x);
        for(int j=q1+1;j<=q2;++j)
        {
            if(h[j]<=k) s+=num(k-h[j]+1);
        }
        for(int j=q1+1;j<=q2;++j) add(h[j]+1,1);
        q1=q2;
    }
    for(int i=1;i<=q2;++i) add(h[i]+1,-1);
    add(1,-1);
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
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    scanf("%d",&k);
    T[1].s=n;
    T[0].ms=1e9;
    dfs(1);
    printf("%lld",s);
    return 0;
}