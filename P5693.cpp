#include<cstdio>
#include<algorithm>
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
int n,m,a[N];
struct str
{
    ll a,b;
    str() {}
    str(ll a,ll b):a(a),b(b) {}
    friend str operator+(str a,str b)
    {
        return str(a.a+b.a,a.b+b.b);
    }
    friend bool operator<(str a,str b)
    {
        if(a.b!=b.b) return a.b<b.b;
        return a.a<b.a;
    }
};
ll check(str a,str b)
{
    if(a.a==b.a) return 1e18;
    if(((a.b-b.b)>0)^((a.a-b.a)>0)) return (b.b-a.b)/(a.a-b.a);
    else return 1e18;
}
struct tree
{
    int l,r;
    ll t,k;
    str s,ls,rs,ms;
}T[N<<2];
void pushup(tree &T,tree T1,tree T2)
{
    T.t=min(T1.t,T2.t);
    T.s=max(max(T1.s,T2.s),T1.rs+T2.ls);
    T.t=min(min(T.t,check(T1.s,T2.s)),min(check(T1.s,T1.rs+T2.ls),check(T2.s,T1.rs+T2.ls)));
    T.ls=max(T1.ls,T1.ms+T2.ls);
    T.t=min(T.t,check(T1.ls,T1.ms+T2.ls));
    T.rs=max(T2.rs,T2.ms+T1.rs);
    T.t=min(T.t,check(T2.rs,T2.ms+T1.rs));
    T.ms=T1.ms+T2.ms;
}
void pushdown(int x);
void maketag(int x,ll k)
{
    if(k<=T[x].t)
    {
        T[x].k+=k;
        T[x].t-=k;
        T[x].s.b+=T[x].s.a*k;
        T[x].ls.b+=T[x].ls.a*k;
        T[x].rs.b+=T[x].rs.a*k;
        T[x].ms.b+=T[x].ms.a*k;
    }
    else
    {
        T[x].k+=k;
        pushdown(x);
        pushup(T[x],T[x<<1],T[x<<1|1]);
    }
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    maketag(x<<1,T[x].k);
    maketag(x<<1|1,T[x].k);
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    if(l==r)
    {
        T[x].s=T[x].ms=T[x].ls=T[x].rs=str(1,a[l]);
        T[x].t=1e18;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
void add(int x,int l,int r,ll k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        maketag(x,k);
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
tree sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x];
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    tree s;
    if(r<=z) s=sum(x<<1,l,r);
    else if(l>z) s=sum(x<<1|1,l,r);
    else pushup(s,sum(x<<1,l,r),sum(x<<1|1,l,r));
    return s;
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=n;++i) read(a[i]);
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        read(z);
        if(z==1)
        {
            int l,r,k;
            read(l),read(r),read(k);
            add(1,l,r,k);
        }
        else if(z==2)
        {
            int l,r;
            read(l),read(r);
            print(max(sum(1,l,r).s.b,0ll));
            putchar('\n');
        }
    }
    return 0;
}