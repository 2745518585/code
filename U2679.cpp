#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1 = buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T> inline
void read(T& x)
{
    scanf("%d",&x);
    return;
    T f=1,b=0;char ch=gc();
    while (ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=gc();
    }
    while(ch >='0'&&ch<='9') b*=10,b+=ch-'0',ch=gc();
    x=f*b;return;
}
template<typename T> inline
void print(T x)
{
    if(x == 0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int st[129]={0},k=0;
    while(x) st[++k]=x%10,x/=10;
    for (int i=k;i;i--) putchar(st[i]+'0');
}
const int N=3000001;
int n,q;
ll a[N],b[N];
struct tree
{
    int l,r;
    ll s,s1,s2,k;
}T[N<<2];
void pushup(int x)
{
    T[x].s=min(T[x<<1].s,T[x<<1|1].s);
    T[x].s1=min(T[x<<1].s1,T[x<<1|1].s1);
    T[x].s2=min(T[x<<1].s2,T[x<<1|1].s2);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].s+=T[x].k;
    T[x<<1].s1+=T[x].k;
    T[x<<1].s2+=T[x].k;
    T[x<<1].k+=T[x].k;
    T[x<<1|1].s+=T[x].k;
    T[x<<1|1].s1+=T[x].k;
    T[x<<1|1].s2+=T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s=T[x].s1=T[x].s2=1e18;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q,ll k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=min(T[x].s,k);
        T[x].s1=min(T[x].s1,k-b[q]);
        T[x].s2=min(T[x].s2,k+b[q]);
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
ll sum1(int x,int l,int r)
{
    if(l>r) return 1e18;
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s1;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=1e18;
    if(l<=z) s=min(s,sum1(x<<1,l,r));
    if(r>z) s=min(s,sum1(x<<1|1,l,r));
    return s;
}
ll sum2(int x,int l,int r)
{
    if(l>r) return 1e18;
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s2;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=1e18;
    if(l<=z) s=min(s,sum2(x<<1,l,r));
    if(r>z) s=min(s,sum2(x<<1|1,l,r));
    return s;
}
int main()
{
    read(n);
    for(int i=1;i<=n;++i)
    {
        read(a[i]);
        b[i]=a[i];
    }
    b[n+1]=0;
    sort(b+1,b+n+2);
    q=unique(b+2,b+n+2)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(b+1,b+q+1,a[i])-b;
    }
    build(1,1,q);
    add(1,1,0);
    for(int i=1;i<=n;++i)
    {
        ll k1=sum1(1,1,a[i]),k2=sum2(1,a[i],q);
        T[1].k+=abs(b[a[i]]-b[a[i-1]]);
        add(1,a[i-1],min(k1+b[a[i]],k2-b[a[i]]));
    }
    print(T[1].s);
    return 0;
}