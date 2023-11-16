#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll inf=2e18;
int n,m,a[N];
ll f[N];
struct str
{
    int l,r,k;
}b[N];
struct tree
{
    int l,r,t;
    ll s1,s2,k;
}T[N<<2];
void pushup(int x)
{
    if(T[x<<1].s1>inf) T[x].s1=T[x<<1|1].s1,T[x].s2=T[x<<1|1].s2;
    else if(T[x<<1].s2>inf)
    {
        T[x].s1=T[x<<1].s1;
        if(T[x].s1!=T[x<<1|1].s1) T[x].s2=T[x<<1|1].s1;
        else T[x].s2=T[x<<1|1].s2;
    }
    else T[x].s1=T[x<<1].s1,T[x].s2=T[x<<1].s2;
}
void pushdown(int x)
{
    if(T[x].t==1)
    {
        T[x<<1].t=T[x<<1|1].t=1;
        T[x<<1].s1=T[x<<1|1].s1=T[x<<1].k=T[x<<1|1].k=0;
        T[x<<1].s2=T[x<<1|1].s2=inf*2;
        T[x].t=0;
    }
    if(T[x].k!=0)
    {
        T[x<<1].s1+=T[x].k;
        T[x<<1].s2+=T[x].k;
        T[x<<1].k+=T[x].k;
        T[x<<1|1].s1+=T[x].k;
        T[x<<1|1].s2+=T[x].k;
        T[x<<1|1].k+=T[x].k;
        T[x].k=0;
    }
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    T[x].k=T[x].t=0;
    if(l==r)
    {
        T[x].s1=a[l];
        T[x].s2=inf*2;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,ll k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s1+=k;
        T[x].s2+=k;
        T[x].k+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
ll sum(int x,int q)
{
    if(T[x].l==T[x].r) return T[x].s1;
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) return sum(x<<1,q);
    else return sum(x<<1|1,q);
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        build(1,1,n);
        scanf("%d",&m);
        int w=0;
        T[1].t=1;
        T[1].s1=T[1].k=0;
        T[1].s2=inf*2;
        // printf("%lld %lld\n",T[1].s1,T[1].s2);
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d%d",&b[i].l,&b[i].r,&b[i].k);
            add(1,b[i].l,b[i].r,b[i].k);
            // printf("%lld %lld\n",T[1].s1,T[1].s2);
            if(T[1].s1<0||(T[1].s1==0&&T[1].s2<0))
            {
                w=i;
                T[1].t=1;
                T[1].s1=T[1].s2=T[1].k=0;
            }
        }
        for(int i=1;i<=n;++i) f[i]=0;
        for(int i=1;i<=w;++i)
        {
            f[b[i].l]+=b[i].k;
            f[b[i].r+1]-=b[i].k;
        }
        for(int i=1;i<=n;++i) f[i]+=f[i-1];
        for(int i=1;i<=n;++i)
        {
            printf("%lld ",a[i]+f[i]);
        }
        printf("\n");
    }
    return 0;
}