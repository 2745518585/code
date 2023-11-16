#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int N=500001;
int n,m,q,a[N],a1[N],b[N],c[N],c2[N],d1[N],d2[N],sa[N],rk[N],he[N];
vector<pair<int,int>> e[N];
namespace st
{
    int b[N][21],lg[N];
    void init(int n,int *a)
    {
        for(int i=0;i<=19;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,n);++j) lg[j]=i;
        }
        for(int i=1;i<=n;++i) b[i][0]=a[i];
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n-(1<<i)+1;++j) b[j][i]=min(b[j][i-1],b[j+(1<<(i-1))][i-1]);
        }
    }
    int sum(int x,int y)
    {
        ++x;
        return min(b[x][lg[y-x]],b[y-(1<<lg[y-x])+1][lg[y-x]]);
    }
}
struct tree
{
    int l,r,s,k;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    if(T[x<<1].s) T[x<<1].k+=T[x].k;
    if(T[x<<1|1].s) T[x<<1|1].k+=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s=T[x].k=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add1(int x,int q,int k)
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
void add2(int x,int l,int r)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        if(T[x].s) ++T[x].k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add2(x<<1,l,r);
    if(r>z) add2(x<<1|1,l,r);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r) return T[x].s;
    int z=T[x].l+T[x].r>>1,s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
void check(int x)
{
    if(T[x].l==T[x].r)
    {
        d2[a1[sa[T[x].l]]]+=T[x].k;
        return;
    }
    pushdown(x);
    check(x<<1);
    check(x<<1|1);
}
void init(int n,int *a)
{
    static int x1[N],x2[N],h[N];
    int m=20000;
    for(int i=1;i<=n;++i)
    {
        int z=a[i];
        if(a[i]==-1) z=++m;
        ++h[z];
        x1[i]=z;
    }
    for(int i=1;i<=m;++i) h[i]+=h[i-1];
    for(int i=n;i>=1;--i) sa[h[x1[i]]--]=i;
    for(int r=1;r<=n;r<<=1)
    {
        int p=0;
        for(int i=n-r+1;i<=n;++i) x2[++p]=i;
        for(int i=1;i<=n;++i) if(sa[i]>r) x2[++p]=sa[i]-r;
        for(int i=1;i<=m;++i) h[i]=0;
        for(int i=1;i<=n;++i) ++h[x1[i]];
        for(int i=1;i<=m;++i) h[i]+=h[i-1];
        for(int i=n;i>=1;--i) sa[h[x1[x2[i]]]--]=x2[i],x2[i]=0;
        swap(x1,x2);
        p=0;
        x1[sa[1]]=++p;
        for(int i=2;i<=n;++i)
        {
            if(x2[sa[i]]==x2[sa[i-1]]&&x2[sa[i]+r]==x2[sa[i-1]+r]) x1[sa[i]]=p;
            else x1[sa[i]]=++p;
        }
        if(p==n) break;
        m=p;
    }
    for(int i=1;i<=n;++i) rk[sa[i]]=i;
    int p=0;
    for(int i=1;i<=n;++i)
    {
        if(rk[i]==1) continue;
        if(p>=1) --p;
        int j=sa[rk[i]-1];
        while(i+p<=n&&j+p<=n&&(a[i+p]==a[j+p]&&a[i+p]!=-1)) ++p;
        he[rk[i]]=p;
    }
}
int find1(int x,int k)
{
    int l=1,r=x;
    while(l<r)
    {
        int z=l+r>>1;
        if(st::sum(z,x)>=k) r=z;
        else l=z+1;
    }
    return l;
}
int find2(int x,int k)
{
    int l=x,r=m;
    while(l<r)
    {
        int z=l+r+1>>1;
        if(st::sum(x,z)>=k) l=z;
        else r=z-1;
    }
    return l;
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i)
    {
        int k;
        scanf("%d",&k);
        for(int j=1;j<=k;++j)
        {
            scanf("%d",&a[m+j]);
            ++a[m+j];
            a1[m+j]=i;
        }
        m+=k;
        a[++m]=-1;
        scanf("%d",&k);
        for(int j=1;j<=k;++j)
        {
            scanf("%d",&a[m+j]);
            ++a[m+j];
            a1[m+j]=i;
        }
        m+=k;
        a[++m]=-1;
    }
    for(int i=1;i<=q;++i)
    {
        int k;
        scanf("%d",&k);
        c[i]=m+1;
        c2[i]=k;
        for(int j=1;j<=k;++j)
        {
            scanf("%d",&a[m+j]);
            ++a[m+j];
        }
        m+=k;
        a[++m]=-1;
    }
    init(m,a);
    st::init(m,he);
    build(1,1,m);
    for(int i=1;i<=q;++i)
    {
        int z1=find1(rk[c[i]],c2[i]),z2=find2(rk[c[i]],c2[i]);
        e[z2].push_back(make_pair(z1,i));
    }
    for(int i=1;i<=m;++i)
    {
        if(a1[sa[i]]!=0)
        {
            add1(1,i,1);
            if(b[a1[sa[i]]]) add1(1,b[a1[sa[i]]],0);;
            b[a1[sa[i]]]=i;
        }
        for(auto j:e[i])
        {
            d1[j.second]=sum(1,j.first,i);
            add2(1,j.first,i);
        }
    }
    for(int i=1;i<=q;++i)
    {
        printf("%d\n",d1[i]);
    }
    check(1);
    for(int i=1;i<=n;++i)
    {
        printf("%d ",d2[i]);
    }
    return 0;
}