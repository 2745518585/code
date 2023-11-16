#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,k1,k2,t[N],p=1,rt,q1,q2;
ll s;
bool g[N];
struct str
{
    int x,s;
    str(){}
    str(int x,int s):x(x),s(s){}
}h[N];
bool cmp(str a,str b)
{
    return a.x<b.x;
}
struct tree
{
    int s,ms,d;
}T[N];
struct road
{
    int m,q,w;
}a[N<<1];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
namespace Tree
{
    int T[N];
    void add(int x,int k)
    {
        ++x;
        while(x<=n) T[x]+=k,x+=x&-x;
    }
    int sum(int x)
    {
        ++x;
        if(x<=0) return 0;
        int s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
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
    if(T[x].ms<T[rt].ms) rt=x;
}
void dfs2(int x,int fa,int w)
{
    h[++q2]=str(w,T[x].d);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        T[a[i].m].d=T[x].d+1;
        dfs2(a[i].m,x,max(w,a[i].w));
    }
}
void solve(int x)
{
    q1=q2=0;
    h[++q2]=str(0,0);
    q1=q2;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        T[a[i].m].d=1;
        dfs2(a[i].m,x,a[i].w);
        sort(h+q1+1,h+q2+1,cmp);
        int z=1,w=0;
        for(int i=q1+1;i<=q2;++i)
        {
            s-=(ll)h[i].x*(Tree::sum(k2-h[i].s)-Tree::sum(k1-h[i].s-1));
            Tree::add(h[i].s,1);
        }
        for(int i=q1+1;i<=q2;++i) Tree::add(h[i].s,-1);
        q1=q2;
    }
    sort(h+1,h+q2+1,cmp);
    for(int i=1;i<=q2;++i)
    {
        s+=(ll)h[i].x*(Tree::sum(k2-h[i].s)-Tree::sum(k1-h[i].s-1));
        Tree::add(h[i].s,1);
    }
    for(int i=1;i<=q2;++i) Tree::add(h[i].s,-1);
}
void dfs(int x)
{
    rt=0;
    q=T[x].s;
    dfs1(x,0);
    solve(rt);
    g[rt]=true;
    for(int i=t[rt];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        dfs(a[i].m);
    }
}
int main()
{
    scanf("%d%d%d",&n,&k1,&k2);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    T[1].s=n;
    T[0].ms=1e9;
    dfs(1);
    printf("%lld",s*2);
    return 0;
}