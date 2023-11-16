#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9;
int n,m;
ll a[N],b[N],c[N];
struct tree
{
    int l,r,k,t;
    ll s,s2;
}T[N<<2];
void pushup(tree &T,tree T1,tree T2)
{
    T.s=(T1.s+T2.s*b[T1.t+1]%P+T2.s2*b[T1.t]%P)%P;
    T.s2=(T1.s2+T2.s*b[T1.t]%P+T2.s2*b[T1.t-1]%P)%P;
    T.t=T1.t+T2.t;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].k=(T[x<<1].k+T[x].k)%P;
    T[x<<1].s=(T[x<<1].s+c[T[x<<1].t]*T[x].k%P)%P;
    T[x<<1].s2=(T[x<<1].s2+c[T[x<<1].t-1]*T[x].k%P)%P;
    T[x<<1|1].k=(T[x<<1|1].k+T[x].k)%P;
    T[x<<1|1].s=(T[x<<1|1].s+c[T[x<<1|1].t]*T[x].k%P)%P;
    T[x<<1|1].s2=(T[x<<1|1].s2+c[T[x<<1|1].t-1]*T[x].k%P)%P;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=a[l];
        T[x].s2=0;
        T[x].t=1;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
void change(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) change(x<<1,q,k);
    else change(x<<1|1,q,k);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
void add(int x,int l,int r,int k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k=(T[x].k+k)%P;
        T[x].s=(T[x].s+c[T[x].t]*k%P)%P;
        T[x].s2=(T[x].s2+c[T[x].t-1]*k%P)%P;
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
    if(l<=z&&!(r>z)) s=sum(x<<1,l,r);
    else if(!(l<=z)&&r>z) s=sum(x<<1|1,l,r);
    else pushup(s,sum(x<<1,l,r),sum(x<<1|1,l,r));
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    b[1]=1,b[2]=1;
    for(int i=3;i<=n;++i) b[i]=(b[i-1]+b[i-2])%P;
    for(int i=1;i<=n;++i) c[i]=(c[i-1]+b[i])%P;
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            change(1,x,k);
        }
        else if(z==2)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%lld\n",sum(1,x,y).s);
        }
        else if(z==3)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            add(1,x,y,k);
        }
    }
    return 0;
}