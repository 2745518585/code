#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int m,n,k,a1[N],a2[N],b1[N],b2[N];
vector<int> c1[N],c2[N];
namespace sgt1
{
    int T[N],n;
    void add(int x,int k)
    {
        while(x<=2e5) T[x]=max(T[x],k),x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s=max(s,T[x]),x-=x&-x;
        return s;
    }
}
namespace sgt2
{
    struct tree
    {
        int l,r,s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=max(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r,int *a)
    {
        T[x].l=l,T[x].r=r;
        if(l==r)
        {
            T[x].s=a[l];
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z,a);
        build(x<<1|1,z+1,r,a);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s=max(s,sum(x<<1,l,r));
        if(r>z) s=max(s,sum(x<<1|1,l,r));
        return s;
    }
}
namespace sgt3
{
    struct tree
    {
        int l,r;
        ll s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=T[x<<1].s+T[x<<1|1].s;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        T[x].s=0;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int q,ll k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s+=k;
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
        pushup(x);
    }
    ll sum(int x,int l,int r)
    {
        if(l>r||r<T[x].l||l>T[x].r) return 0;
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        int z=T[x].l+T[x].r>>1;
        ll s=0;
        if(l<=z) s+=sum(x<<1,l,r);
        if(r>z) s+=sum(x<<1|1,l,r);
        return s;
    }
}
int main()
{
    scanf("%d%d%d",&m,&n,&k);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&a1[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a2[i]);
    }
    a1[0]=a1[m+1]=a2[0]=a2[n+1]=k+1;
    sgt2::build(1,0,m+1,a1);
    for(int i=1;i<=2e5;++i) sgt1::T[i]=0;
    for(int i=1;i<=m;++i)
    {
        b1[i]=sgt2::sum(1,sgt1::sum(a1[i]),i);
        sgt1::add(a1[i],i);
    }
    for(int i=1;i<=2e5;++i) sgt1::T[i]=0;
    for(int i=m;i>=1;--i)
    {
        b1[i]=min(b1[i],sgt2::sum(1,i,m-sgt1::sum(a1[i]-1)+1));
        sgt1::add(a1[i],m-i+1);
    }
    sgt2::build(1,0,n+1,a2);
    for(int i=1;i<=2e5;++i) sgt1::T[i]=0;
    for(int i=1;i<=n;++i)
    {
        b2[i]=sgt2::sum(1,sgt1::sum(a2[i]),i);
        sgt1::add(a2[i],i);
    }
    for(int i=1;i<=2e5;++i) sgt1::T[i]=0;
    for(int i=n;i>=1;--i)
    {
        b2[i]=min(b2[i],sgt2::sum(1,i,n-sgt1::sum(a2[i]-1)+1));
        sgt1::add(a2[i],n-i+1);
    }
    for(int i=1;i<=m;++i)
    {
        c1[min(b1[i],k+1)].push_back(i);
    }
    for(int i=1;i<=n;++i)
    {
        c2[max(k-a2[i],0)].push_back(i);
    }
    sgt3::build(1,1,k);
    ll s=0;
    for(int i=k+1;i>=0;--i)
    {
        for(auto j:c2[i])
        {
            s+=sgt3::sum(1,k-b2[j]+1,k-a2[j]);
        }
        for(auto j:c1[i])
        {
            if(a1[j]<=k) sgt3::add(1,a1[j],1);
        }
    }
    printf("%lld",s);
    return 0;
}