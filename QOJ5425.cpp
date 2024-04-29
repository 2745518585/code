#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,b1[N],b2[N];
namespace fhq
{
    int tot;
    struct tree
    {
        int k,l,r,s,h,f;
    }T[N];
    void pushup(int x)
    {
        T[x].s=T[T[x].l].s+T[T[x].r].s+1;
        if(T[x].l) T[T[x].l].f=x;
        if(T[x].r) T[T[x].r].f=x;
        T[x].f=0;
    }
    void split(int x,int k,int &x1,int &x2)
    {
        if(x==0)
        {
            x1=x2=0;
            return;
        }
        if(T[x].k<=k)
        {
            x1=x;
            split(T[x].r,k,T[x].r,x2);
        }
        else
        {
            x2=x;
            split(T[x].l,k,x1,T[x].l);
        }
        pushup(x);
    }
    int merge(int x1,int x2)
    {
        if(x1==0||x2==0) return x1|x2;
        if(T[x1].h<T[x2].h)
        {
            T[x1].r=merge(T[x1].r,x2);
            pushup(x1);
            return x1;
        }
        else
        {
            T[x2].l=merge(x1,T[x2].l);
            pushup(x2);
            return x2;
        }
    }
    void add(int &rt,int k)
    {
        int x1,x2;
        split(rt,k,x1,x2);
        T[++tot].k=k;
        T[tot].l=T[tot].r=T[tot].f=0;
        T[tot].s=1;
        T[tot].h=rand();
        rt=merge(merge(x1,tot),x2);
    }
    int sum(int x,int k)
    {
        if(x==0) return 0;
        if(k<=T[T[x].l].s) return sum(T[x].l,k);
        else if(k<=T[T[x].l].s+1) return x;
        else return sum(T[x].r,k-T[T[x].l].s-1);
    }
}
namespace sgt1
{
    int chkmin(int x,int y)
    {
        return b1[x]<b1[y]?x:y;
    }
    int chkmax(int x,int y)
    {
        return b2[x]>b2[y]?x:y;
    }
    struct tree
    {
        int l,r,s1,s2;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s1=chkmin(T[x<<1].s1,T[x<<1|1].s1);
        T[x].s2=chkmax(T[x<<1].s2,T[x<<1|1].s2);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        if(l==r)
        {
            T[x].s1=T[x].s2=l;
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int q)
    {
        if(T[x].l==T[x].r) return;
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q);
        else add(x<<1|1,q);
        pushup(x);
    }
    int sum1(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s1;
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s=chkmin(s,sum1(x<<1,l,r));
        if(r>z) s=chkmin(s,sum1(x<<1|1,l,r));
        return s;
    }
    int sum2(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s2;
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s=chkmax(s,sum2(x<<1,l,r));
        if(r>z) s=chkmax(s,sum2(x<<1|1,l,r));
        return s;
    }
}
namespace sgt2
{
    struct tree
    {
        int l,r,s0,s1,k;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s0=T[x<<1].s0+T[x<<1|1].s0;
        T[x].s1=T[x<<1].s1+T[x<<1|1].s1;
    }
    void maketag(int x,int k)
    {
        if(k==1) T[x].s1=T[x].s0,T[x].s0=0;
        else if(k>1) T[x].s0=T[x].s1=0;
        T[x].k+=k;
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        maketag(x<<1,T[x].k);
        maketag(x<<1|1,T[x].k);
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        T[x].s0=T[x].s1=T[x].k=0;
        if(l==r)
        {
            T[x].s0=1;
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int l,int r,int k)
    {
        if(l>r) return;
        if(T[x].l>=l&&T[x].r<=r)
        {
            maketag(x,k);
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
}
ll sum(ll x)
{
    return x*(x-1)/2;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        if(n==1)
        {
            for(int i=1;i<=m;++i)
            {
                scanf("%*d%*d");
                printf("0\n");
            }
            continue;
        }
        fhq::tot=0;
        int rt=0;
        for(int i=1;i<=n-1;++i) fhq::add(rt,i);
        for(int i=1;i<=n-1;++i)
        {
            b1[i]=i-1;
            b2[i]=i+1;
        }
        b1[0]=b1[1]=n+1;
        b2[0]=b2[n-1]=0;
        sgt1::build(1,1,n-1);
        sgt2::build(1,1,n-1);
        ll s=sum(n-1);
        for(int i=1;i<=m;++i)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            if(l>r) swap(l,r);
            if(l<r)
            {
                --r;
                auto solve=[&](int x)
                {
                    // printf(" %d %d %d\n",x,b1[x],b2[x]);
                    int rt=x;
                    while(fhq::T[rt].f) rt=fhq::T[rt].f;
                    s-=sum(fhq::T[rt].s);
                    int x1,x2,x3;
                    fhq::split(rt,l-1,x1,x2);
                    fhq::split(x2,r,x2,x3);
                    int p1=fhq::sum(x1,fhq::T[x1].s),p2=fhq::sum(x2,1),p3=fhq::sum(x2,fhq::T[x2].s),p4=fhq::sum(x3,1);
                    x1=fhq::merge(x1,x3);
                    s+=sum(fhq::T[x1].s)+sum(fhq::T[x2].s);
                    b2[p1]=(p4?p4:0);
                    b1[p2]=n+1;
                    b2[p3]=0;
                    b1[p4]=(p1?p1:n+1);
                    if(p1) sgt1::add(1,p1);
                    if(p2) sgt1::add(1,p2);
                    if(p3) sgt1::add(1,p3);
                    if(p4) sgt1::add(1,p4);
                };
                int x=sgt1::sum1(1,l,r);
                while(b1[x]<l)
                {
                    solve(x);
                    x=sgt1::sum1(1,l,r);
                }
                x=sgt1::sum2(1,l,r);
                while(b2[x]>r)
                {
                    solve(x);
                    x=sgt1::sum2(1,l,r);
                }
                sgt2::add(1,l,r,1);
            }
            int w0=sgt2::T[1].s0,w1=sgt2::T[1].s1;
            // printf("%lld %d %d\n",s,w0,w1);
            printf("%lld\n",(s-sum(w0))+((ll)w0*(n+i-2)-sum(w0))+(w1));
        }
    }
    return 0;
}