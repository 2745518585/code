#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T> inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
template<typename T,typename ...O> inline void read(T &x,O &...o) {read(x),read(o...);}
template<typename T> inline void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int c[129]={0},k=0;
    while(x) c[++k]=x%10,x/=10;
    for(int i=k;i;--i) putchar(c[i]+'0');
}
template<typename T,typename ...O> inline void print(T x,O ...o) {print(x),putchar(' '),print(o...);}
const int N=1000001;
int n,m,a[N],e[N];
struct qry
{
    int l,r,t;
}b[N];
vector<int> c[N],d[N];
struct str
{
    int x,w;
    str() {}
    str(int x,int w):x(x),w(w) {}
    friend bool operator<(str a,str b)
    {
        return a.w<b.w;
    }
};
struct sgt
{
    struct tree
    {
        int l,r,k;
        str s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=max(T[x<<1].s,T[x<<1|1].s);
    }
    void pushdown(int x)
    {
        T[x<<1].s.w+=T[x].k;
        T[x<<1].k+=T[x].k;
        T[x<<1|1].s.w+=T[x].k;
        T[x<<1|1].k+=T[x].k;
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        T[x].s=str(0,-1e9);
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int q,str k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
        pushup(x);
    }
    void add2(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s.w+=k;
            T[x].k+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add2(x<<1,l,r,k);
        if(r>z) add2(x<<1|1,l,r,k);
        pushup(x);
    }
    str sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        str s(0,-1e9);
        if(l<=z) s=max(s,sum(x<<1,l,r));
        if(r>z) s=max(s,sum(x<<1|1,l,r));
        return s;
    }
}T,T0,T1,T2;
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
void del(int x)
{
    T.add(1,x,str(0,-1e9));
    T1.add(1,b[x].l,str(0,-1e9));
    T2.add(1,b[x].r,str(0,-1e9));
    int l=T1.sum(1,1,b[x].l).x,r=T2.sum(1,b[x].r,n).x;
    int p=T0.sum(1,1,b[r].l-1).x;
    while(p!=0&&b[p].r>b[l].r)
    {
        c[b[p].l].pop_back();
        if(!c[b[p].l].empty()) T0.add(1,b[p].l,str(c[b[p].l].back(),b[c[b[p].l].back()].r));
        else T0.add(1,b[p].l,str(0,-1e9));
        T.add(1,p,str(p,sgt2::sum(b[p].r)-sgt2::sum(b[p].l-1)));
        T1.add(1,b[p].l,str(p,b[p].r));
        T2.add(1,b[p].r,str(p,n-b[p].l+1));
        p=T0.sum(1,1,b[p].l-1).x;
    }
}
bool cmp(qry x,qry y)
{
    if(x.l!=y.l) return x.l<y.l;
    return x.r>y.r;
}
int main()
{
    read(n,m);
    for(int i=1;i<=n;++i)
    {
        read(a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        read(b[i].l,b[i].r);
        b[i].t=i;
    }
    b[0].l=n+1,b[0].r=0;
    sort(b+1,b+m+1,cmp);
    T.build(1,1,m);
    T1.build(1,1,n);
    T2.build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        if(T1.sum(1,1,b[i].l).w>=b[i].r)
        {
            c[b[i].l].push_back(i);
        }
        else
        {
            T.add(1,i,str(i,b[i].r-b[i].l+1));
            T1.add(1,b[i].l,str(i,b[i].r));
            T2.add(1,b[i].r,str(i,n-b[i].l+1));
        }
    }
    T0.build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        reverse(c[i].begin(),c[i].end());
        if(!c[i].empty()) T0.add(1,i,str(c[i].back(),b[c[i].back()].r));
    }
    for(int i=1;i<=n;++i) sgt2::add(i,1);
    for(int i=1;i<=n;++i) d[min(a[i],n)].push_back(i);
    for(int i=n;i>=0;--i)
    {
        for(auto j:d[i])
        {
            int l=T2.sum(1,j,n).x,r=T1.sum(1,1,j).x;
            if(b[l].l>j) continue;
            T.add2(1,l,r,-1);
            sgt2::add(j,-1);
        }
        while(T.T[1].s.w>=i)
        {
            e[b[T.T[1].s.x].t]=i;
            del(T.T[1].s.x);
        }
    }
    for(int i=1;i<=m;++i)
    {
        print(e[i]);
        putchar('\n');
    }
    return 0;
}