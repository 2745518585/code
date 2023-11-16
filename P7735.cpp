#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
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
int n,m,tot;
vector<int> a[N];
namespace sgt
{
    struct tree
    {
        int l,r,s,k;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=T[x<<1].s+T[x<<1|1].s;
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        T[x<<1].k=T[x].k;
        T[x<<1].s=T[x<<1].r-T[x<<1].l+1;
        T[x<<1|1].k=T[x].k;
        T[x<<1|1].s=T[x<<1|1].r-T[x<<1|1].l+1;
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        T[x].s=T[x].k=0;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].k=k;
            T[x].s=T[x].r-T[x].l+1;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
    void add2(int x,int q)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=0;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add2(x<<1,q);
        else add2(x<<1|1,q);
        pushup(x);
    }
    void add3(int x,int q,int k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].k=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add3(x<<1,q,k);
        else add3(x<<1|1,q,k);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(l>r) return 0;
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s+=sum(x<<1,l,r);
        if(r>z) s+=sum(x<<1|1,l,r);
        return s;
    }
    int sum2(int x,int q)
    {
        if(T[x].l==T[x].r)
        {
            return T[x].k;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1,s=0;
        if(q<=z) return sum2(x<<1,q);
        else return sum2(x<<1|1,q);
    }
}
struct tree
{
    int f,s,d,t,z,b;
}T[N];
void dfs1(int x)
{
    T[x].s=1;
    T[x].z=0;
    T[x].d=T[T[x].f].d+1;
    for(auto i:a[x])
    {
        if(i==T[x].f) continue;
        T[i].f=x;
        dfs1(i);
        T[x].s+=T[i].s;
        if(T[i].s>T[T[x].z].s) T[x].z=i;
    }
}
void dfs2(int x,int t)
{
    T[x].b=++tot;
    T[x].t=t;
    if(T[x].z) dfs2(T[x].z,t);
    for(auto i:a[x])
    {
        if(i==T[x].f||i==T[x].z) continue;
        dfs2(i,i);
    }
}
void check(int x,int y,int t)
{
    if(T[x].z) sgt::add2(1,T[T[x].z].b);
    if(T[y].z) sgt::add2(1,T[T[y].z].b);
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>T[T[y].t].d)
        {
            sgt::add(1,T[T[x].t].b+1,T[x].b,t);
            sgt::add3(1,T[T[x].t].b,t);
            x=T[T[x].t].f;
            if(T[x].z) sgt::add2(1,T[T[x].z].b);
        }
        else
        {
            sgt::add(1,T[T[y].t].b+1,T[y].b,t);
            sgt::add3(1,T[T[y].t].b,t);
            y=T[T[y].t].f;
            if(T[y].z) sgt::add2(1,T[T[y].z].b);
        }
    }
    if(T[x].d<=T[y].d)
    {
        sgt::add(1,T[x].b+1,T[y].b,t);
        sgt::add3(1,T[x].b,t);
        sgt::add2(1,T[x].b);
    }
    else
    {
        sgt::add(1,T[y].b+1,T[x].b,t);
        sgt::add3(1,T[y].b,t);
        sgt::add2(1,T[y].b);
    }
}
int solve(int x,int y)
{
    int s=0;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>T[T[y].t].d)
        {
            s+=sgt::sum(1,T[T[x].t].b+1,T[x].b);
            int z1=sgt::sum2(1,T[T[x].t].b),z2=sgt::sum2(1,T[T[T[x].t].f].b);
            if(z1!=0&&z1==z2) ++s;
            x=T[T[x].t].f;
        }
        else
        {
            s+=sgt::sum(1,T[T[y].t].b+1,T[y].b);
            int z1=sgt::sum2(1,T[T[y].t].b),z2=sgt::sum2(1,T[T[T[y].t].f].b);
            if(z1!=0&&z1==z2) ++s;
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<=T[y].d) s+=sgt::sum(1,T[x].b+1,T[y].b);
    else s+=sgt::sum(1,T[y].b+1,T[x].b);
    return s;
}
void abc()
{
    read(n),read(m);
    tot=0;
    for(int i=1;i<=n;++i) a[i].clear();
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        read(x),read(y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs1(1);
    dfs2(1,1);
    sgt::build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z,x,y;
        read(z),read(x),read(y);
        if(z==1) check(x,y,i);
        else if(z==2) printf("%d\n",solve(x,y));
    }
}
int main()
{
    int T;
    read(T);
    while(T--) abc();
    return 0;
}