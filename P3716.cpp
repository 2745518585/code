#include<cstdio>
#include<algorithm>
using namespace std;
const int N=300001;
int n,m,ls,rs,q,t[N],p=1,r,q1,q2,s=-1e9,h[N][2],b[N];
bool g[N];
struct tree
{
    int s,ms,d,h,w;
}T[N];
struct tree2
{
    int l,r,s,s2,k;
}T2[N<<2];
struct road
{
    int m,q,w;
}a[N<<1];
struct road2
{
    int x,y,w;
}a2[N];
void pushup(int x)
{
    T2[x].s=max(T2[x<<1].s,T2[x<<1|1].s);
    T2[x].s2=max(T2[x<<1].s2,T2[x<<1|1].s2);
}
void pushdown(int x)
{
    if(T2[x].k==0) return;
    T2[x<<1].s=max(T2[x<<1].s,T2[x<<1].s2);
    T2[x<<1].s2=-1e9;
    T2[x<<1|1].s=max(T2[x<<1|1].s,T2[x<<1|1].s2);
    T2[x<<1|1].s2=-1e9;
    T2[x<<1].k=T2[x<<1|1].k=1;
    T2[x].k=0;
}
void build(int x,int l,int r)
{
    T2[x].l=l;
    T2[x].r=r;
    T2[x].s=T2[x].s2=-1e9;
    T2[x].k=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q,int k)
{
    if(T2[x].l==T2[x].r)
    {
        T2[x].s2=max(T2[x].s2,k);
        return;
    }
    pushdown(x);
    int z=T2[x].l+T2[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(l>r) return -1e9;
    if(T2[x].l>=l&&T2[x].r<=r)
    {
        return T2[x].s;
    }
    pushdown(x);
    int z=T2[x].l+T2[x].r>>1,s=-1e9;
    if(l<=z) s=max(s,sum(x<<1,l,r));
    if(r>z) s=max(s,sum(x<<1|1,l,r));
    return s;
}
int sum2(int x,int l,int r)
{
    if(l>r) return -1e9;
    if(T2[x].l>=l&&T2[x].r<=r)
    {
        return T2[x].s2;
    }
    pushdown(x);
    int z=T2[x].l+T2[x].r>>1,s=-1e9;
    if(l<=z) s=max(s,sum2(x<<1,l,r));
    if(r>z) s=max(s,sum2(x<<1|1,l,r));
    return s;
}
void clear(int x)
{
    if(T2[x].l==T2[x].r)
    {
        T2[x].s=T2[x].s2=-1e9;
        T2[x].k=0;
        return;
    }
    if(T2[x<<1].s>-1e9||T2[x<<1].s2>-1e9) clear(x<<1);
    if(T2[x<<1|1].s>-1e9||T2[x<<1|1].s2>-1e9) clear(x<<1|1);
    pushup(x);
}
bool cmp(road2 a,road2 b)
{
    return a.w<b.w;
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
    h[++q2][0]=T[x].d;
    h[q2][1]=T[x].h;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        T[a[i].m].d=T[x].d+b[a[i].w]*(a[i].w!=T[x].w);
        T[a[i].m].h=T[x].h+1;
        T[a[i].m].w=a[i].w;
        dfs2(a[i].m,x);
    }
}
void solve(int x)
{
    q1=q2=0;
    int o=0;
    clear(1);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        T[a[i].m].d=b[a[i].w];
        T[a[i].m].h=1;
        T[a[i].m].w=a[i].w;
        dfs2(a[i].m,x);
        if(a[i].w!=o) T2[1].k=1;
        o=a[i].w;
        for(int j=q1+1;j<=q2;++j)
        {
            if(h[j][1]>rs) continue;
            int s1=sum(1,max(ls-h[j][1],1),max(rs-h[j][1],0)),s2=sum2(1,max(ls-h[j][1],1),max(rs-h[j][1],0));
            s=max(s,max(h[j][0]+s1,h[j][0]+s2-b[a[i].w]));
            if(h[j][1]>=ls&&h[j][1]<=rs) s=max(s,h[j][0]);
        }
        for(int j=q1+1;j<=q2;++j)
        {
            add(1,h[j][1],h[j][0]);
        }
        q1=q2;
    }
}
void dfs(int x)
{
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
    scanf("%d%d%d%d",&n,&m,&ls,&rs);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        scanf("%d%d%d",&a2[i].x,&a2[i].y,&a2[i].w);
    }
    sort(a2+1,a2+n,cmp);
    for(int i=1;i<=n-1;++i)
    {
        road(a2[i].x,a2[i].y,a2[i].w);
        road(a2[i].y,a2[i].x,a2[i].w);
    }
    build(1,1,n);
    T[1].s=n;
    T[0].ms=1e9;
    dfs(1);
    printf("%d",s);
    return 0;
}