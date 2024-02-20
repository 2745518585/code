#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=100001;
int n,m,a[N];
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
struct str
{
    vector<pair<int,int>> f1,f2;
    ll s;
    str() {}
    str(int x)
    {
        f1.clear(),f2.clear();
        f1.push_back(make_pair(x,1));
        f2.push_back(make_pair(x,1));
        if(x>1) s=1;
        else s=0;
    }
    friend str operator+(const str &a,const str &b)
    {
        str c;
        c.s=a.s+b.s;
        int x=-1;
        for(int i=a.f2.size()-1;i>=0;--i)
        {
            while(x+1<b.f1.size()&&gcd(a.f2[i].first,b.f1[x+1].first)>1) ++x;
            if(x>=0) c.s+=(ll)(a.f2[i].second-(i>0?a.f2[i-1].second:0))*b.f1[x].second;
        }
        c.f1=a.f1;
        for(auto i:b.f1)
        {
            i.second+=a.f1.back().second;
            int z=gcd(c.f1.back().first,i.first);
            if(z==c.f1.back().first) c.f1.back().second=i.second;
            else c.f1.push_back(make_pair(z,i.second));
        }
        c.f2=b.f2;
        for(auto i:a.f2)
        {
            i.second+=b.f2.back().second;
            int z=gcd(c.f2.back().first,i.first);
            if(z==c.f2.back().first) c.f2.back().second=i.second;
            else c.f2.push_back(make_pair(z,i.second));
        }
        return c;
    }
};
namespace sgt
{
    struct tree
    {
        int l,r;
        str s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=T[x<<1].s+T[x<<1|1].s;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        if(l==r)
        {
            T[x].s=a[l];
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int q,int k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=k;
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
        pushup(x);
    }
    str sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        int z=T[x].l+T[x].r>>1;
        str s;
        if(r<=z) s=sum(x<<1,l,r);
        else if(l>z) s=sum(x<<1|1,l,r);
        else s=sum(x<<1,l,r)+sum(x<<1|1,l,r);
        return s;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sgt::build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            sgt::add(1,x,k);
        }
        else if(z==2)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%lld\n",sgt::sum(1,l,r).s);
        }
    }
    return 0;
}