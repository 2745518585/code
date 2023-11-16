#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,q,k,a[N],c[N],d[N],e[N],f[N],o[N],g[N];
vector<int> b[N],r1[N],r2[N];
namespace sgt1
{
    struct tree
    {
        int l,r,s,t,k;
    }T[N<<2];
    void pushup(int x)
    {
        if(T[x<<1].s<=T[x<<1|1].s) T[x].s=T[x<<1].s,T[x].t=T[x<<1].t;
        else T[x].s=T[x<<1|1].s,T[x].t=T[x<<1|1].t;
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
        if(l==r)
        {
            T[x].s=T[x].t=l;
            T[x].k=0;
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s+=k;
            T[x].k+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
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
        T[x].s=min(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        if(l==r)
        {
            T[x].s=1e9;
            return;
        }
        int z=T[x].l+T[x].r>>1;
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
    int sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        int z=T[x].l+T[x].r>>1,s=1e9;
        if(l<=z) s=min(s,sum(x<<1,l,r));
        if(r>z) s=min(s,sum(x<<1|1,l,r));
        return s;
    }
}
int main()
{
    scanf("%d%d",&q,&k);
    for(int i=1;i<=q;++i)
    {
        scanf("%d",&a[i]);
        n+=a[i];
    }
    int p=0;
    for(int i=1;i<=q;++i)
    {
        if(a[i]>(n-1)/k+1)
        {
            printf("-1");
            return 0;
        }
        int z=0;
        for(int j=a[i];j>=1;--j)
        {
            c[++p]=n-(j-1)*k;
            b[n-(j-1)*k].push_back(p);
            o[p]=i;
            r1[z].push_back(p);
            z=p;
        }
    }
    // for(int i=1;i<=n;++i)
    // {
    //     for(auto j:b[i]) printf("%d ",j);printf("\n");
    // }
    p=0;
    for(int i=1;i<=n;++i)
    {
        for(auto j:b[i])
        {
            d[++p]=j;
            f[j]=p;
        }
        e[i]=p;
    }
    // for(int i=1;i<=n;++i) printf("%d ",d[i]);printf("\n");
    // for(int i=1;i<=n;++i) printf("%d ",e[i]);printf("\n");
    // for(int i=1;i<=n;++i) printf("%d ",f[i]);printf("\n");
    sgt1::build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        sgt1::add(1,i,n,-(int)b[i].size());
        // printf("add %d %d %d\n",i,n,-(int)b[i].size());
    }
    sgt2::build(1,1,n);
    for(auto i:r1[0]) sgt2::add(1,f[i],i);
    for(int i=1;i<=n;++i)
    {
        for(auto j:r2[i]) sgt2::add(1,f[j],j);
        int x=sgt2::sum(1,1,e[sgt1::T[1].t]);
        // printf("%d %d %d\n",sgt1::T[1].s,sgt1::T[1].t,x);
        // printf("%d %d\n",i,x);
        if(x>n||sgt1::T[1].s<0)
        {
            printf("-1");
            return 0;
        }
        sgt1::add(1,1,c[x]-1,-1);
        // printf("add %d %d %d\n",1,c[x]-1,-1);
        sgt1::add(1,i,i,1e9);
        // printf("add %d %d %d\n",i,i,1e9);
        sgt2::add(1,f[x],1e9);
        for(auto j:r1[x]) r2[i+k].push_back(j);
        g[i]=o[x];
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d ",g[i]);
    }
    return 0;
}