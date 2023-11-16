#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9;
int n,a[N],b1[N],b2[N];
ll s=0;
struct tree
{
    int l,r;
    ll s1,s2,k;
}T[N<<2];
void pushup(int x)
{
    T[x].s1=(T[x<<1].s1+T[x<<1|1].s1)%P;
    T[x].s2=(T[x<<1].s2+T[x<<1|1].s2)%P;
}
void maketag(int x,ll k)
{
    T[x].s1=k*(T[x].r-T[x].l+1)%P;
    T[x].s2=k*((ll)(T[x].l+T[x].r)*(T[x].r-T[x].l+1)/2%P)%P;
    T[x].k=k;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    maketag(x<<1,T[x].k);
    maketag(x<<1|1,T[x].k);
    T[x].k=0;
}
void build(int x,int l,int r,int *a)
{
    T[x].l=l,T[x].r=r;
    T[x].s1=T[x].s2=T[x].k=0;
    if(l==r)
    {
        maketag(x,a[l]);
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z,a);
    build(x<<1|1,z+1,r,a);
    pushup(x);
}
void add(int x,int l,int r,ll k)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        maketag(x,k);
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
ll sum1(int x,int l,int r)
{
    if(l>r) return 0;
    if(T[x].l>=l&&T[x].r<=r) return T[x].s1;
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s=(s+sum1(x<<1,l,r))%P;
    if(r>z) s=(s+sum1(x<<1|1,l,r))%P;
    return s;
}
ll sum2(int x,int l,int r)
{
    if(l>r) return 0;
    if(T[x].l>=l&&T[x].r<=r) return T[x].s2;
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s=(s+sum2(x<<1,l,r))%P;
    if(r>z) s=(s+sum2(x<<1|1,l,r))%P;
    return s;
}
void solve(int l,int r)
{
    if(l==r)
    {
        s=(s+(ll)a[l]*a[l]%P)%P;
        return;
    }
    int z=l+r>>1;
    b1[z+1]=0,b2[z+1]=1e9;
    for(int i=z;i>=l;--i) b1[i]=max(a[i],b1[i+1]);
    for(int i=z;i>=l;--i) b2[i]=min(a[i],b2[i+1]);
    build(1,l,z,b1);
    int x1=z,x2=z,w1=0,w2=1e9;
    for(int i=z+1;i<=r;++i)
    {
        w1=max(w1,a[i]);
        w2=min(w2,a[i]);
        while(x1>=l&&b1[x1]<w1) --x1;
        while(x2>=l&&b2[x2]>=w2) --x2;
        add(1,x1+1,z,w1);
        s=(s+sum1(1,x2+1,z)*w2%P*(i+1)%P-sum2(1,x2+1,z)*w2%P)%P;
    }
    b1[z]=0,b2[z]=1e9;
    for(int i=z+1;i<=r;++i) b1[i]=max(a[i],b1[i-1]);
    for(int i=z+1;i<=r;++i) b2[i]=min(a[i],b2[i-1]);
    build(1,z+1,r,b1);
    x1=z+1,x2=z+1,w1=0,w2=1e9;
    for(int i=z;i>=l;--i)
    {
        w1=max(w1,a[i]);
        w2=min(w2,a[i]);
        while(x1<=r&&b1[x1]<w1) ++x1;
        while(x2<=r&&b2[x2]>w2) ++x2;
        add(1,z+1,x1-1,w1);
        s=(s+sum2(1,z+1,x2-1)*w2%P-sum1(1,z+1,x2-1)*w2%P*(i-1)%P)%P;
    }
    solve(l,z);
    solve(z+1,r);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    solve(1,n);
    printf("%lld",s);
    return 0;
}