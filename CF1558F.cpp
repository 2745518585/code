#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],b[N],c[N];
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
        if(T[x].k==0) return;
        T[x<<1].s+=T[x].k;
        T[x<<1].k+=T[x].k;
        T[x<<1|1].s+=T[x].k;
        T[x<<1|1].k+=T[x].k;
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        T[x].s=-1e9;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add1(int x,int l,int r,int k)
    {
        if(l>r) return;
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s+=k;
            T[x].k+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add1(x<<1,l,r,k);
        if(r>z) add1(x<<1|1,l,r,k);
        pushup(x);
    }
    void add2(int x,int q,int k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add2(x<<1,q,k);
        else add2(x<<1|1,q,k);
        pushup(x);
    }
}
namespace sgt2
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]+=k,x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
    }
}
int sum(int x,int y)
{
    if(x==y) return 0;
    return y-x+(y%2);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            b[a[i]]=i;
        }
        c[n]=n;
        for(int i=n-1;i>=1;--i)
        {
            c[i]=min(c[i+1],b[i+1]-1);
        }
        sgt1::build(1,1,n);
        for(int i=1;i<=n;++i) sgt2::T[i]=0;
        int s=0,t=0;
        for(int i=1;i<=n;++i)
        {
            int x=sgt2::sum(b[i]-1)+1;
            sgt2::add(b[i],1);
            sgt1::add1(1,b[i]+1,n,-2);
            sgt1::add2(1,b[i],sum(x,b[i])-x);
            while(t<c[i])
            {
                ++t;
                sgt1::add2(1,t,-1e9);
            }
            // printf("%d %d %d\n",b[i],sum(x,b[i])-x,sgt1::T[1].s);
            s=max(s,sgt1::T[1].s+i);
        }
        printf("%d\n",s);
    }
    return 0;
}