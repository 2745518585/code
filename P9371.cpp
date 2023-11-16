#include<cstdio>
#include<algorithm>
#include<vector>
namespace Solve
{
    using namespace std;
    const int N=1000001;
    int n,a[N];
    vector<int> b[N];
    namespace sgt
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
    struct tree
    {
        int l,r,s1,s2,s3,s4,k1,k2;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s1=min(T[x<<1].s1,T[x<<1|1].s1);
        T[x].s2=max(T[x<<1].s2,T[x<<1|1].s2);
        T[x].s3=max(T[x<<1].s3,T[x<<1|1].s3);
        T[x].s4=min(T[x<<1].s4,T[x<<1|1].s4);
    }
    void pushdown(int x)
    {
        if(T[x].k1!=0)
        {
            T[x<<1].s1+=T[x].k1;
            T[x<<1].s3+=T[x].k1;
            T[x<<1].k1+=T[x].k1;
            T[x<<1|1].s1+=T[x].k1;
            T[x<<1|1].s3+=T[x].k1;
            T[x<<1|1].k1+=T[x].k1;
            T[x].k1=0;
        }
        if(T[x].k2!=0)
        {
            T[x<<1].s2+=T[x].k2;
            T[x<<1].s4+=T[x].k2;
            T[x<<1].k2+=T[x].k2;
            T[x<<1|1].s2+=T[x].k2;
            T[x<<1|1].s4+=T[x].k2;
            T[x<<1|1].k2+=T[x].k2;
            T[x].k2=0;
        }
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        T[x].s1=T[x].s2=T[x].s3=T[x].s4=T[x].k1=T[x].k2=0;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add1(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s1+=k;
            T[x].s3+=k;
            T[x].k1+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add1(x<<1,l,r,k);
        if(r>z) add1(x<<1|1,l,r,k);
        pushup(x);
    }
    void add2(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s2+=k;
            T[x].s4+=k;
            T[x].k2+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add2(x<<1,l,r,k);
        if(r>z) add2(x<<1|1,l,r,k);
        pushup(x);
    }
    int sum1(int x,int q)
    {
        if(T[x].l==T[x].r) return T[x].s1;
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(q<=z) return sum1(x<<1,q);
        else return sum1(x<<1|1,q);
    }
    int sum2(int x,int q)
    {
        if(T[x].l==T[x].r) return T[x].s2;
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(q<=z) return sum2(x<<1,q);
        else return sum2(x<<1|1,q);
    }
    int sum3(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s3;
        pushdown(x);
        int z=T[x].l+T[x].r>>1,s=-1e9;
        if(l<=z) s=max(s,sum3(x<<1,l,r));
        if(r>z) s=max(s,sum3(x<<1|1,l,r));
        return s;
    }
    int sum4(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s4;
        pushdown(x);
        int z=T[x].l+T[x].r>>1,s=1e9;
        if(l<=z) s=min(s,sum4(x<<1,l,r));
        if(r>z) s=min(s,sum4(x<<1|1,l,r));
        return s;
    }
    int sum(int x,int k1,int k2)
    {
        if(T[x].l==T[x].r)
        {
            return T[x].l;
        }
        pushdown(x);
        int z1=T[x<<1|1].s1-k1,z2=T[x<<1|1].s2-k2;
        if(max(z1,z2)>=0&&min(z1,z2)<=0) return sum(x<<1|1,k1,k2);
        return sum(x<<1,k1,k2);
    }
    int main(int _n,vector<int> _a)
    {
        n=_n;
        for(int i=1;i<=n;++i)
        {
            a[i]=_a[i-1];
            b[a[i]].push_back(i);
        }
        build(1,0,n);
        for(int i=1;i<=n;++i) add1(1,i,n,1),add2(1,i,n,1);
        int s=0;
        for(int i=1;i<=n;++i)
        {
            for(auto j:b[i-1]) add2(1,j,n,-2),sgt::add(j,-1);
            for(auto j:b[i]) add1(1,j,n,-2),sgt::add(j,1);
            int x=0;
            for(auto j:b[i])
            {
                int z1=sum3(1,x,j-1),z2=sum4(1,x,j-1);
                int z=sum(1,z1,z2);
                if(z>=j) s=max(s,sgt::sum(z)-sgt::sum(j-1));
            }
        }
        return s;
    }
}
int sequence(int N, std::vector<int> A)
{
    return Solve::main(N,A);
}