#pragma GCC optimize("Ofast")
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
const int N=1000001;
int n,m,k,tot,rt1,rt2;
ll a[N],k1,k2,mx;
struct tree
{
    int l,r,s;
}T[N<<4];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void add(int &x,ll ls,ll rs,ll q,int k)
{
    if(x==0) x=++tot;
    if(ls==rs)
    {
        T[x].s+=k;
        return;
    }
    ll z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q,k);
    else add(T[x].r,z+1,rs,q,k);
    pushup(x);
}
int sum(int x,ll ls,ll rs,ll l,ll r)
{
    if(ls>=l&&rs<=r) return T[x].s;
    ll z=ls+rs>>1;
    int s=0;
    if(l<=z) s+=sum(T[x].l,ls,z,l,r);
    if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
    return s;
}
ll sum2(int x,ll ls,ll rs,int k,ll t)
{
    if(ls==rs) return ls;
    ll z=ls+rs>>1;
    int p=T[T[x].r].s+sum(rt2,0,mx,(z+1)+t*k2,min(rs+t*k2,mx));
    if(p>=k) return sum2(T[x].r,z+1,rs,k,t);
    return sum2(T[x].l,ls,z,k-p,t);
}
ll solve(ll t)
{
    return sum2(rt1,0,mx,k,t);
}
int main()
{
    // freopen("data.in","r",stdin);
    // freopen("data.out","w",stdout);
    read(n),read(k),read(m),read(k1),read(k2);
    mx=1e9+k1+n*k2;
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=m+1;i<=n;++i) add(rt1,0,mx,a[i],1);
    for(int i=1;i<=m;++i) add(rt2,0,mx,a[i]+k1+i*k2,1);
    ll s=solve(1);
    for(int i=2;i<=n-m+1;++i)
    {
        add(rt1,0,mx,a[i-1],1);
        add(rt1,0,mx,a[i+m-1],-1);
        add(rt2,0,mx,a[i-1]+k1+(i-1)*k2,-1);
        add(rt2,0,mx,a[i+m-1]+k1+(i+m-1)*k2,1);
        s=max(s,solve(i));
    }
    printf("%lld",s);
    return 0;
}