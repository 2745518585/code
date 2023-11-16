#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
ll pls(ll x) {return x;}
template<typename ...T> ll pls(ll x,T ...y) {return (x+pls(y...))%P;}
template<typename ...T> ll getpls(ll &x,T ...y) {return x=(x+pls(y...))%P;}
ll mul(ll x) {return x;}
template<typename ...T> ll mul(ll x,T ...y) {return (x*mul(y...))%P;}
template<typename ...T> ll getmul(ll &x,T ...y) {return x=(x*mul(y...))%P;}
int n,m,q;
ll pow2[N];
struct tree
{
    int l,r;
    ll s,s1,s2,k1,k2;
}T[N<<2];
void pushup(int x)
{
    T[x].s=pls(T[x].s1,T[x<<1].s,T[x<<1|1].s);
}
void maketag1(int x,ll k)
{
    getmul(T[x].s,k);
    getmul(T[x].s1,k);
    getmul(T[x].k1,k);
}
void maketag2(int x,ll k)
{
    getmul(T[x].s2,k);
    getmul(T[x].k2,k);
}
void pushdown(int x)
{
    if(T[x].k1!=1)
    {
        maketag1(x<<1,T[x].k1);
        maketag1(x<<1|1,T[x].k1);
        T[x].k1=1;
    }
    if(T[x].k2!=1)
    {
        maketag2(x<<1,T[x].k2);
        maketag2(x<<1|1,T[x].k2);
        T[x].k2=1;
    }
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s=T[x].s1=0;
    T[x].s2=1;
    T[x].k1=T[x].k2=1;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,int t)
{
    pushdown(x);
    if(T[x].l>=l&&T[x].r<=r)
    {
        getpls(T[x].s1,pow2[t-1]);
        maketag1(x<<1,2);
        maketag1(x<<1|1,2);
        pushup(x);
        return;
    }
    int z=T[x].l+T[x].r>>1;
    getpls(T[x].s2,pow2[t-1]);
    if(r<=z)
    {
        add(x<<1,l,r,t);
        getpls(T[x<<1|1].s1,pow2[t-1]-T[x<<1|1].s2);
        getmul(T[x<<1|1].s2,2);
        pushdown(x<<1|1);
        maketag1((x<<1|1)<<1,2);
        maketag2((x<<1|1)<<1,2);
        maketag1((x<<1|1)<<1|1,2);
        maketag2((x<<1|1)<<1|1,2);
        pushup(x<<1|1);
    }
    else if(l>z)
    {
        add(x<<1|1,l,r,t);
        getpls(T[x<<1].s1,pow2[t-1]-T[x<<1].s2);
        getmul(T[x<<1].s2,2);
        pushdown(x<<1);
        maketag1((x<<1)<<1,2);
        maketag2((x<<1)<<1,2);
        maketag1((x<<1)<<1|1,2);
        maketag2((x<<1)<<1|1,2);
        pushup(x<<1);
    }
    else
    {
        add(x<<1,l,r,t);
        add(x<<1|1,l,r,t);
    }
    pushup(x);
}
int main()
{
    scanf("%d%d",&n,&m);
    build(1,1,n);
    pow2[0]=1;
    for(int i=1;i<=m;++i) pow2[i]=mul(pow2[i-1],2);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            add(1,x,y,++q);
        }
        else
        {
            printf("%lld\n",(T[1].s%P+P)%P);
        }
    }
    return 0;
}