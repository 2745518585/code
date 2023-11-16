#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m;
ll a[N],b[N],c[N];
struct str
{
    int x,y,k;
    str(){}
    str(int x,int y,int k):x(x),y(y),k(k){}
};
vector<str> d[N],e;
struct tree
{
    int l,r;
    ll s,t1,t2,s2;
}T[N<<2];
void pushup(tree &T,tree T1,tree T2)
{
    T.s=max(T1.s,T2.s);
    T.s2=max(T1.t1+T2.t2,max(T1.s2,T2.s2));
    T.t1=max(T1.t1,T2.t1);
    T.t2=max(T1.t2,T2.t2);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=a[l]-b[l-1];
        T[x].t1=a[l]-b[l-1];
        T[x].t2=b[l]+(c[n]-c[l-1]);
        T[x].s2=T[x].t1+T[x].t2;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
void add(int x,int q,ll k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=max(T[x].s,k);
        T[x].t1=max(T[x].t1,k);
        T[x].s2=T[x].t1+T[x].t2;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
ll sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1;
    ll s=-1e18;
    if(l<=z) s=max(s,sum(x<<1,l,r));
    if(r>z) s=max(s,sum(x<<1|1,l,r));
    return s;
}
tree sum2(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x];
    }
    int z=T[x].l+T[x].r>>1;
    tree s;
    if(l<=z&&(!(r>z))) s=sum2(x<<1,l,r);
    else if((!(l<=z))&&r>z) s=sum2(x<<1|1,l,r);
    else pushup(s,sum2(x<<1,l,r),sum2(x<<1|1,l,r));
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        a[i]+=a[i-1];
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
        b[i]+=b[i-1];
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&c[i]);
        c[i]+=c[i-1];
    }
    for(int i=1;i<=m;++i)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        d[y].push_back(str(x,y,k));
        e.push_back(str(x,y,k));
    }
    build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        ll s=-1e18;
        for(auto j:d[i])
        {
            s=max(s,sum(1,j.x,j.y)-j.k);
        }
        if(i<n) add(1,i+1,s);
    }
    ll s=-1e18;
    for(auto i:e)
    {
        s=max(s,sum2(1,i.x,i.y).s2-i.k);
    }
    printf("%lld",s);
    return 0;
}