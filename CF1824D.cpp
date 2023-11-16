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
int n,m,a[N],c[N];
ll d[N];
struct str
{
    int x,y,t,u;
    str(){}
    str(int x,int y,int t,int u):x(x),y(y),t(t),u(u){}
};
vector<str> b[N];
namespace sgt
{
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
}
struct tree
{
    int l,r,s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
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
void add(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=k;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1,s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
int sum1(int x,int k)
{
    if(T[x].l==T[x].r) return T[x].l;
    if(k<=T[x<<1].s) return sum1(x<<1,k);
    else return sum1(x<<1|1,k-T[x<<1].s);
}
int sum2(int x,int k)
{
    if(T[x].l==T[x].r) return T[x].l;
    if(k<=T[x<<1|1].s) return sum2(x<<1|1,k);
    else return sum2(x<<1,k-T[x<<1|1].s);
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<=m;++i)
    {
        int l1,r1,l2,r2;
        read(l1),read(r1),read(l2),read(r2);
        b[l2-1].push_back(str(l1,r1,i,-1));
        b[r2].push_back(str(l1,r1,i,1));
    }
    sgt::build(1,1,n);
    build(1,0,n);
    for(int i=1;i<=n;++i)
    {
        sgt::add(1,i,i,i);
        add(1,i,1);
        if(c[a[i]])
        {
            sgt::add(1,sum1(1,sum(1,1,c[a[i]]-1))+1,c[a[i]],sum2(1,sum(1,c[a[i]]+1,n))-c[a[i]]);
            add(1,c[a[i]],0);
        }
        sgt::maketag(1,0,0,1);
        c[a[i]]=i;
        for(auto j:b[i])
        {
            d[j.t]+=sgt::sum(1,j.x,j.y)*j.u;
        }
    }
    for(int i=1;i<=m;++i)
    {
        print(d[i]);
        putchar('\n');
    }
    return 0;
}