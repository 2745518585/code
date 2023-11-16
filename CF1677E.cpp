#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
template<typename T>
inline void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int c[129]={0},k=0;
    while(x) c[++k]=x%10,x/=10;
    for(int i=k;i;--i) putchar(c[i]+'0');
}
const int N=1000001;
int n,q,a[N],b[N];
ll f[N];
vector<int> c[N];
struct str
{
    int x,y,u,t;
    str(){}
    str(int x,int y,int u,int t):x(x),y(y),u(u),t(t){}
};
struct str2
{
    int x,y;
    str2(){}
    str2(int x,int y):x(x),y(y){}
}g[N];
vector<str> d[N],e[N];
namespace Segment_tree
{
    struct tree
    {
        int l,r,s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=max(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        if(l==r)
        {
            T[x].s=a[l];
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s=max(s,sum(x<<1,l,r));
        if(r>z) s=max(s,sum(x<<1|1,l,r));
        return s;
    }
}
struct tree
{
    int l,r,t;
    ll s,ms,k,mk;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
    T[x].ms=T[x<<1].ms+T[x<<1|1].ms;
}
void maketag(int x,ll k,ll mk,int t)
{
    T[x].ms+=t*T[x].s+mk*(T[x].r-T[x].l+1);
    T[x].mk+=t*T[x].k+mk;
    T[x].s+=k*(T[x].r-T[x].l+1);
    T[x].k+=k;
    T[x].t+=t;
}
void pushdown(int x)
{
    maketag(x<<1,T[x].k,T[x].mk,T[x].t);
    maketag(x<<1|1,T[x].k,T[x].mk,T[x].t);
    T[x].k=T[x].mk=T[x].t=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,ll k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s+=k*(T[x].r-T[x].l+1);
        T[x].k+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
ll sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].ms;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
void check(int x1,int x2,int y1,int y2)
{
    d[y1].push_back(str(x1,x2,1,0));
    d[y2+1].push_back(str(x1,x2,-1,0));
}
bool cmp2(str2 a,str2 b)
{
    return a.x>b.x;
}
void solve(int l,int r)
{
    if(l>=r) return;
    int x=Segment_tree::sum(1,l,r);
    int w=0;
    for(auto i:c[x])
    {
        if(b[i]<l||b[x/i]>r||b[i]>b[x/i]||i==x/i) continue;
        if(min(b[i],b[x])==max(b[x],b[x/i]))
        {
            if(min(b[i],b[x])-1>=l) g[++w]=str2(min(b[i],b[x])-1,max(b[x],b[x/i]));
            if(max(b[x],b[x/i])+1<=r) g[++w]=str2(min(b[i],b[x]),max(b[x],b[x/i])+1);
        }
        else g[++w]=str2(min(b[i],b[x]),max(b[x],b[x/i]));
    }
    sort(g+1,g+w+1,cmp2);
    int t=r+1;
    for(int i=1;i<=w;++i)
    {
        if(g[i].y<t)
        {
            check(l,g[i].x,g[i].y,t-1);
            t=g[i].y;
        }
    }
    solve(l,b[x]-1);
    solve(b[x]+1,r);
}
bool cmp(int x,int y)
{
    return b[x]<b[y];
}
int main()
{
    read(n),read(q);
    for(int i=1;i<=n;++i)
    {
        read(a[i]);
        b[a[i]]=i;
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=1;a[i]*j<=n;++j) c[a[i]*j].push_back(a[i]);
    }
    Segment_tree::build(1,1,n);
    solve(1,n);
    for(int i=1;i<=q;++i)
    {
        int x,y;
        read(x),read(y);
        e[x-1].push_back(str(x,y,-1,i));
        e[y].push_back(str(x,y,1,i));
    }
    build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        for(auto j:d[i]) add(1,j.x,j.y,j.u);
        maketag(1,0,0,1);
        for(auto j:e[i]) f[j.t]+=sum(1,j.x,j.y)*j.u;
    }
    for(int i=1;i<=q;++i)
    {
        print(f[i]);
        putchar('\n');
    }
    return 0;
}