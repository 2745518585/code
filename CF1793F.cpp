#include<cstdio>
#include<algorithm>
using namespace std;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
template<typename T>
inline void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int c[129]={0},k=0;
    while(x) c[++k]=x%10,x/=10;
    for(int i=k;i;--i) putchar(c[i]+'0');
}
const int N=300001,M=1000001;
int n,m,rt,tot,a[N],c[M];
struct str
{
    int l,r,t;
}b[M];
struct tree
{
    int l,r,s;
}T[N<<4];
bool cmp(str a,str b)
{
    return a.r<b.r;
}
void pushup(int x)
{
    T[x].s=max(T[T[x].l].s,T[T[x].r].s);
}
void add(int &x,int ls,int rs,int q,int k)
{
    if(x==0)
    {
        x=++tot;
        T[x].s=T[x].l=T[x].r=0;
    }
    if(ls==rs)
    {
        T[x].s=k;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q,k);
    else add(T[x].r,z+1,rs,q,k);
    pushup(x);
}
int sum(int x,int ls,int rs,int l,int r)
{
    if(x==0||l>r) return 0;
    if(ls>=l&&rs<=r)
    {
        return T[x].s;
    }
    int z=ls+rs>>1,s=0;
    if(l<=z) s=max(s,sum(T[x].l,ls,z,l,r));
    if(r>z) s=max(s,sum(T[x].r,z+1,rs,l,r));
    return s;
}
namespace Segment_tree
{
    struct tree
    {
        int l,r,s;
    }T[N<<2];
    int a[N];
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
            T[x].s=1e9;
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
            T[x].s=min(T[x].s,k);
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
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
int main()
{
    read(n),read(m);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<=m;++i)
    {
        read(b[i].l),read(b[i].r);
        b[i].t=i;
    }
    for(int i=1;i<=m;++i) c[i]=1e9;
    sort(b+1,b+m+1,cmp);
    Segment_tree::build(1,1,n);
    int z=1;
    for(int i=1;i<=n;++i)
    {
        int x=sum(rt,0,1e9,a[i],1e9);
        while(x!=0)
        {
            Segment_tree::add(1,x,a[x]-a[i]);
            x=sum(rt,0,1e9,a[i],min((a[i]+a[x])/2,a[x]-1));
        }
        add(rt,0,1e9,a[i],i);
        while(z<=m&&b[z].r==i)
        {
            c[b[z].t]=min(c[b[z].t],Segment_tree::sum(1,b[z].l,i));
            ++z;
        }
    }
    for(int i=1;i<=n;++i) a[i]=-a[i];
    Segment_tree::build(1,1,n);
    tot=rt=0;
    z=1;
    for(int i=1;i<=n;++i)
    {
        int x=sum(rt,-1e9,0,a[i],1e9);
        while(x!=0)
        {
            Segment_tree::add(1,x,a[x]-a[i]);
            x=sum(rt,-1e9,0,a[i],min((a[i]+a[x])/2,a[x]-1));
        }
        add(rt,-1e9,0,a[i],i);
        while(z<=m&&b[z].r==i)
        {
            c[b[z].t]=min(c[b[z].t],Segment_tree::sum(1,b[z].l,i));
            ++z;
        }
    }
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",c[i]);
    }
    return 0;
}