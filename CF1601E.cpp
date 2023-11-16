#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,k,a[N];
ll d[N];
struct str
{
    int x,y,t;
    str(){}
    str(int x,int y,int t):x(x),y(y),t(t){}
};
vector<str> b[N],c[N];
namespace sgt
{
    struct tree
    {
        int l,r,s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=min(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
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
    int sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        int z=T[x].l+T[x].r>>1,s=1e9;
        if(l<=z) s=min(s,sum(x<<1,l,r));
        if(r>z) s=min(s,sum(x<<1|1,l,r));
        return s;
    }
}
struct tree
{
    int l,r,s,k,t;
    ll mk;
}T[N<<2];
void pushup(int x)
{
    T[x].s=max(T[x<<1].s,T[x<<1|1].s);
}
void maketag(int x,ll mk,int k,int t)
{
    T[x].mk+=(ll)t*T[x].k+mk;
    if(T[x].k==0) T[x].t+=t;
    if(k!=0)
    {
        T[x].k=k;
        T[x].s=k;
    }
}
void pushdown(int x)
{
    maketag(x<<1,T[x].mk,T[x].k,T[x].t);
    maketag(x<<1|1,T[x].mk,T[x].k,T[x].t);
    T[x].mk=T[x].k=T[x].t=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].mk=T[x].k=T[x].t=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,int k)
{
    if(l>r||r<1) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        maketag(x,0,k,0);
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
int find(int x,int k)
{
    if(T[x].l==T[x].r)
    {
        return T[x].l;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(T[x<<1].s>k) return find(x<<1,k);
    return find(x<<1|1,k);
}
ll sum(int x,int q)
{
    if(T[x].l==T[x].r)
    {
        return T[x].mk;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) return sum(x<<1,q);
    else return sum(x<<1|1,q);
}
void solve(int x)
{
    build(1,1,(n-x)/k+1);
    for(int i=1;(i-1)*k+x<=n;++i)
    {
        int z=sgt::sum(1,(i-2)*k+x+1,(i-1)*k+x);
        int p=min(find(1,z),i);
        // printf("%d %d %d\n",p,i-1,z);
        add(1,p,i-1,z);
        // printf("%d %d %d\n",i,i,a[(i-1)*k+x]);
        add(1,i,i,a[(i-1)*k+x]);
        maketag(1,0,0,1);
        for(auto j:c[i])
        {
            d[j.t]=sum(1,(j.x-x)/k+1);
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sgt::build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        b[(x-1)%k+1].push_back(str(x,y,i));
    }
    for(int i=1;i<=k;++i)
    {
        for(auto j:b[i]) c[(j.y-i)/k+1].push_back(j);
        solve(i);
        for(auto j:b[i]) c[(j.y-i)/k+1].clear();
    }
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",d[i]);
    }
    return 0;
}