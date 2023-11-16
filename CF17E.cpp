#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=51123987;
int n,f[N<<1];
char a[N<<1];
struct tree
{
    int l,r,k;
    ll s,s2;
}T[N<<2];
void pushup(int x)
{
    T[x].s=(T[x<<1].s+T[x<<1|1].s)%P;
    T[x].s2=(T[x<<1].s2+T[x<<1|1].s2)%P;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].k=(T[x<<1].k+T[x].k)%P;
    T[x<<1].s=(T[x<<1].s+(T[x<<1].r-T[x<<1].l+1)*T[x].k)%P;
    T[x<<1].s2=(T[x<<1].s2+((T[x<<1].l+T[x<<1].r)*(T[x<<1].r-T[x<<1].l+1)/2%P)*T[x].k)%P;
    T[x<<1|1].k=(T[x<<1|1].k+T[x].k)%P;
    T[x<<1|1].s=(T[x<<1|1].s+(T[x<<1|1].r-T[x<<1|1].l+1)*T[x].k)%P;
    T[x<<1|1].s2=(T[x<<1|1].s2+((T[x<<1|1].l+T[x<<1|1].r)*(T[x<<1|1].r-T[x<<1|1].l+1)/2%P)*T[x].k)%P;
    T[x].k=0;
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
void add(int x,int l,int r,int k)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k=(T[x].k+k)%P;
        T[x].s=(T[x].s+(T[x].r-T[x].l+1)*k)%P;
        T[x].s2=(T[x].s2+((T[x].l+T[x].r)*(T[x].r-T[x].l+1)/2%P)*k)%P;
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
    if(l>r) return 0;
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s=(s+sum(x<<1,l,r))%P;
    if(r>z) s=(s+sum(x<<1|1,l,r))%P;
    return s;
}
ll sum2(int x,int l,int r)
{
    if(l>r) return 0;
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s2;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s=(s+sum2(x<<1,l,r))%P;
    if(r>z) s=(s+sum2(x<<1|1,l,r))%P;
    return s;
}
int main()
{
    scanf("%d%s",&n,a+1);
    build(1,1,n);
    for(int i=n;i>=1;--i)
    {
        a[i*2]=a[i];
        a[i*2-1]='#';
    }
    n=n*2+1;
    a[n]='#';
    a[0]='~';
    a[n+1]='@';
    int x=1;
    ll s=0,w=0;
    for(int i=1;i<=n;++i)
    {
        if(i<x+f[x]) f[i]=min(x+f[x]-i,f[x*2-i]);
        else f[i]=1;
        while(a[i-f[i]]==a[i+f[i]]) ++f[i];
        if(i+f[i]>x+f[x]) x=i;
        if(f[i]>=2)
        {
            s=(s+sum(1,1,(i-f[i]+2)/2-1)*(f[i]/2))%P;
            s=(s+(i/2)*sum(1,(i-f[i]+2)/2,i/2)-sum2(1,(i-f[i]+2)/2,i/2));
        }
        add(1,(i+1)/2,(i+f[i]-2)/2,1);
        w=(w+f[i]/2)%P;
    }
    printf("%lld",((w*(w-1)/2-s)%P+P)%P);
    return 0;
}