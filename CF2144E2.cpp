#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,q,a[N],b[N],d1[N],d2[N];
ll f[N];
struct tree
{
    int l,r;
    ll s,k;
}T[N<<2];
void pushup(int x)
{
    T[x].s=(T[x<<1].s+T[x<<1|1].s)%P;
}
void pushdown(int x)
{
    if(T[x].k==1) return;
    T[x<<1].s=T[x<<1].s*T[x].k%P;
    T[x<<1].k=T[x<<1].k*T[x].k%P;
    T[x<<1|1].s=T[x<<1|1].s*T[x].k%P;
    T[x<<1|1].k=T[x<<1|1].k*T[x].k%P;
    T[x].k=1;
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    T[x].s=0,T[x].k=1;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add1(int x,int q,ll k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=(T[x].s+k)%P;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add1(x<<1,q,k);
    else add1(x<<1|1,q,k);
    pushup(x);
}
void add2(int x,int l,int r,ll k)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s=T[x].s*k%P;
        T[x].k=T[x].k*k%P;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add2(x<<1,l,r,k);
    if(r>z) add2(x<<1|1,l,r,k);
    pushup(x);
}
ll sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r) return T[x].s;
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s=(s+sum(x<<1,l,r))%P;
    if(r>z) s=(s+sum(x<<1|1,l,r))%P;
    return s;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=0;i<=n+1;++i) b[i]=0,d1[i]=d2[i]=-1;
        q=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            b[++q]=a[i];
        }
        sort(b+1,b+q+1);
        q=unique(b+1,b+q+1)-b-1;
        for(int i=1;i<=n;++i)
        {
            a[i]=lower_bound(b+1,b+q+1,a[i])-b;
        }
        int x=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i]>x) d1[a[i]]=x,x=a[i];
        }
        x=0;
        for(int i=n;i>=1;--i)
        {
            if(a[i]>x) d2[a[i]]=x,x=a[i];
        }
        build(1,0,q);
        add1(1,0,1);
        for(int i=1;i<=n;++i)
        {
            f[i]=-sum(1,a[i],a[i]);
            add2(1,a[i],q,2);
            if(d1[a[i]]!=-1) add1(1,a[i],sum(1,d1[a[i]],d1[a[i]]));
            f[i]+=sum(1,a[i],a[i]);
        }
        ll s=0;
        build(1,0,q);
        add1(1,0,1);
        for(int i=n;i>=1;--i)
        {
            add2(1,a[i],q,2);
            if(d2[a[i]]!=-1)
            {
                add1(1,a[i],sum(1,d2[a[i]],d2[a[i]]));
                if(a[i]==x) s=(s+f[i]*sum(1,d2[a[i]],d2[a[i]])%P)%P;
            }
        }
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}