#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=998244353;
int n,m,q,t,d[N];
vector<int> a[N];
vector<pair<int,int>> b[N];
struct str
{
    int l,r,k;
}c[N];
namespace sgt1
{
    struct tree
    {
        int l,r,s,k;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=max(T[x<<1].s,T[x<<1|1].s);
    }
    void pushdown(int x)
    {
        if(T[x].k==t+1) return;
        T[x<<1].s=min(T[x<<1].s,T[x].k);
        T[x<<1].k=min(T[x<<1].k,T[x].k);
        T[x<<1|1].s=min(T[x<<1|1].s,T[x].k);
        T[x<<1|1].k=min(T[x<<1|1].k,T[x].k);
        T[x].k=t+1;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        T[x].s=T[x].k=t+1;
        if(l==r) return;
        int z=T[x].l+T[x].r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s=min(T[x].s,k);
            T[x].k=min(T[x].k,k);
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        pushdown(x);
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s=max(s,sum(x<<1,l,r));
        if(r>z) s=max(s,sum(x<<1|1,l,r));
        return s;
    }
}
namespace sgt2
{
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
        T[x].s=0;
        T[x].k=1;
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
            T[x].s=k;
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
}
bool cmp(pair<int,int> a,pair<int,int> b)
{
    return a.second<b.second;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) []()
    {
        scanf("%d%d%d",&n,&q,&m);
        for(int i=1;i<=q;++i)
        {
            scanf("%d%d%d",&c[i].l,&c[i].r,&c[i].k);
            d[i]=c[i].k;
        }
        sort(d+1,d+q+1);
        t=unique(d+1,d+q+1)-d-1;
        for(int i=1;i<=t+1;++i) a[i].clear(),b[i].clear();
        for(int i=1;i<=q;++i)
        {
            c[i].k=lower_bound(d+1,d+t+1,c[i].k)-d;
            b[c[i].k].push_back(make_pair(c[i].l,c[i].r));
        }
        sgt1::build(1,1,n);
        for(int i=1;i<=t;++i)
        {
            for(auto j:b[i])
            {
                if(sgt1::sum(1,j.first,j.second)<i)
                {
                    printf("0\n");
                    return;
                }
                sgt1::add(1,j.first,j.second,i);
            }
        }
        for(int i=1;i<=n;++i)
        {
            a[sgt1::sum(1,i,i)].push_back(i);
        }
        ll s=1;
        for(auto i:a[t+1]) s=s*m%P;
        sgt2::build(1,0,n);
        for(int i=1;i<=t;++i)
        {
            sgt2::add2(1,0,n,0);
            sgt2::add1(1,0,1);
            sort(b[i].begin(),b[i].end(),cmp);
            auto p=b[i].begin();
            for(auto j:a[i])
            {
                while(p!=b[i].end()&&p->second<j)
                {
                    sgt2::add2(1,0,p->first-1,0);
                    ++p;
                }
                sgt2::add1(1,j,sgt2::T[1].s);
                sgt2::add2(1,0,j-1,d[i]-1);
            }
            while(p!=b[i].end())
            {
                sgt2::add2(1,0,p->first-1,0);
                ++p;
            }
            s=s*sgt2::T[1].s%P;
        }
        printf("%lld\n",(s%P+P)%P);
    }();
    return 0;
}