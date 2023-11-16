#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
struct Segment_tree
{
    struct tree
    {
        int l,r,k;
        ll s;
    }T[N<<2];
    int a[N];
    void pushup(int x)
    {
        T[x].s=T[x<<1].s+T[x<<1|1].s;
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        T[x<<1].k+=T[x].k;
        T[x<<1].s+=(T[x<<1].r-T[x<<1].l+1)*T[x].k;
        T[x<<1|1].k+=T[x].k;
        T[x<<1|1].s+=(T[x<<1|1].r-T[x<<1|1].l+1)*T[x].k;
        T[x].k=0;
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
    void change(int x,int q,int k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(q<=z) change(x<<1,q,k);
        else change(x<<1|1,q,k);
        pushup(x);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].k+=k;
            T[x].s+=(T[x].r-T[x].l+1)*k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
    ll num(int x,int q)
    {
        if(T[x].l==T[x].r)
        {
            return T[x].s;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        ll s=0;
        if(q<=z) return num(x<<1,q);
        else return num(x<<1|1,q);
    }
    ll sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        ll s=0;
        if(l<=z) s+=sum(x<<1,l,r);
        if(r>z) s+=sum(x<<1|1,l,r);
        return s;
    }
};
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    Segment_tree T;
    T.build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        T.change(1,i,x);
    }
    for(int i=1;i<=m;++i)
    {
        int z,x,y;
        scanf("%d%d%d",&z,&x,&y);
        if(z==1)
        {
            int k;
            scanf("%d",&k);
            T.add(1,x,y,k);
        }
        else
        {
            printf("%lld\n",T.sum(1,x,y));
        }
    }
    return 0;
}