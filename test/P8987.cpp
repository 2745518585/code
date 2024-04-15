#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const ll N=1000001;
ll n,m,a[N],b[N],c[N];
vector<ll> e[N];
vector<pair<ll,ll>> d[N];
struct sgt
{
    struct tree
    {
        ll l,r;
        ll s,w,k1,k2,t0,t1,t2;
    }T[N<<2];
    void pushup(ll x)
    {
        T[x].s=T[x<<1].s+T[x<<1|1].s;
        T[x].w=max(T[x<<1].w,T[x<<1|1].w);
        T[x].t0=max(T[x<<1].t0,T[x<<1|1].t0);
        T[x].t1=T[x<<1].t1+T[x<<1|1].t1;
        T[x].t2=T[x<<1].t2+T[x<<1|1].t2;
    }
    void maketag1(ll x,ll k)
    {
        T[x].s+=T[x].t1*k;
        T[x].w+=T[x].t0*k;
        T[x].k1+=k;
    }
    void maketag2(ll x,ll k)
    {
        T[x].s=T[x].t2*k;
        T[x].w=k;
        T[x].k1=0;
        T[x].k2=k;
    }
    void pushdown(ll x)
    {
        if(T[x].k2)
        {
            maketag2(x<<1,T[x].k2);
            maketag2(x<<1|1,T[x].k2);
            T[x].k2=0;
        }
        if(T[x].k1)
        {
            maketag1(x<<1,T[x].k1);
            maketag1(x<<1|1,T[x].k1);
            T[x].k1=0;
        }
    }
    void build(ll x,ll l,ll r)
    {
        T[x].l=l,T[x].r=r;
        if(l==r) return;
        ll z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add1(ll x,ll q,ll k,ll t1,ll t2)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=T[x].w=k;
            T[x].t0=T[x].t1=t1;
            T[x].t2=t2;
            return;
        }
        pushdown(x);
        ll z=T[x].l+T[x].r>>1;
        if(q<=z) add1(x<<1,q,k,t1,t2);
        else add1(x<<1|1,q,k,t1,t2);
        pushup(x);
    }
    void add2(ll x,ll l,ll r,ll k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            maketag2(x,k);
            return;
        }
        pushdown(x);
        ll z=T[x].l+T[x].r>>1;
        if(l<=z) add2(x<<1,l,r,k);
        if(r>z) add2(x<<1|1,l,r,k);
        pushup(x);
    }
    ll find(ll x,ll k)
    {
        if(T[x].l==T[x].r) return T[x].l;
        pushdown(x);
        if(T[x<<1].w>=k) return find(x<<1,k);
        else return find(x<<1|1,k);
    }
    ll sum(ll x,ll l,ll r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        pushdown(x);
        ll z=T[x].l+T[x].r>>1;
        ll s=0;
        if(l<=z) s+=sum(x<<1,l,r);
        if(r>z) s+=sum(x<<1|1,l,r);
        return s;
    }
}T1,T2;
void solve(vector<ll> &p,ll l,ll r)
{
    if(l==r)
    {
        // printf("%lld: ",l);
        // for(auto i:p) printf("%lld ",i);printf("\n");
        for(auto i:p) e[l].push_back(i);
        return;
    }
    ll z=l+r>>1;
    static ll S[N],T;
    T=0;
    for(ll i=l;i<=z;++i)
    {
        while(T>0&&b[S[T-1]]==b[i]&&c[S[T]]>c[i]) --T;
        while(T>1&&(ll)(c[i]-c[S[T]])*(b[i]-b[S[T-1]])<(ll)(c[i]-c[S[T-1]])*(b[i]-b[S[T]])) --T;
        S[++T]=i;
    }
    vector<ll> p1,p2;
    // printf("%lld %lld:\n",l,r);
    ll x=1;
    // for(ll i=1;i<=T;++i) printf("%lld ",S[i]);printf("\n");
    for(auto i:p)
    {
        while(x+1<=T&&(c[S[x+1]]-c[S[x]])<=(ll)i*(b[S[x+1]]-b[S[x]])) ++x;
        // printf("%lld %lld\n",x,S[x]);
        // printf("%lld %lld\n",c[S[x]]-(ll)i*b[S[x]],a[i]);
        if(c[S[x]]-(ll)i*b[S[x]]<=a[i]) p1.push_back(i);
        else p2.push_back(i);
    }
    solve(p1,l,z);
    solve(p2,z+1,r);
}
int main()
{
    scanf("%lld%lld",&n,&m);
    for(ll i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(ll i=1;i<=m;++i)
    {
        ll z;
        scanf("%lld",&z);
        if(z==1)
        {
            b[i]+=b[i-1];
            scanf("%lld",&c[i]);
        }
        else if(z==2)
        {
            ++b[i];
            --m,--i;
            d[i].push_back(make_pair(0,0));
        }
        else if(z==3)
        {
            ll l,r;
            scanf("%lld%lld",&l,&r);
            --m,--i;
            d[i].push_back(make_pair(l,r));
        }
    }
    vector<ll> p;
    for(ll i=1;i<=n;++i) p.push_back(i);
    solve(p,1,m+1);
    T1.build(1,1,n);
    T2.build(1,1,n);
    for(ll i=1;i<=n;++i)
    {
        T1.add1(1,i,a[i],i,1);
    }
    for(ll i=0;i<=m;++i)
    {
        if(T2.T[1].w>=c[i])
        {
            T2.add2(1,T2.find(1,c[i]),n,c[i]);
        }
        for(auto j:e[i])
        {
            T1.add1(1,j,0,0,0);
            T2.add1(1,j,c[i],j,1);
        }
        for(auto j:d[i])
        {
            if(j.first==0)
            {
                T1.maketag1(1,1);
                T2.maketag1(1,1);
            }
            else
            {
                printf("%lld\n",T1.sum(1,j.first,j.second)+T2.sum(1,j.first,j.second));
            }
        }
    }
    return 0;
}