#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
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
const int N=200001;
int n,m,q1,q2,q3,b1[N],b2[N],b3[N],rt[N],f[N];
vector<int> d[N],e[N];
struct
{
    int x1,y1,x2,y2;
}a[N];
struct str
{
    int l,r,t;
};
vector<str> c1[N],c2[N];
struct str2
{
    int x,k;
};
vector<str2> c3[N];
namespace sgt1
{
    struct tree
    {
        int l,r;
        vector<int> s;
    }T[N<<2];
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        T[x].s.push_back(0);
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
    }
    void add(int x,int l,int r,int k,int t)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            if(k==1) T[x].s.push_back(t);
            else T[x].s.pop_back();
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k,t);
        if(r>z) add(x<<1|1,l,r,k,t);
    }
    int sum(int x,int q)
    {
        if(q==0) return 0;
        if(T[x].l==T[x].r) return T[x].s.back();
        int z=T[x].l+T[x].r>>1,s=0;
        if(q<=z) s=sum(x<<1,q);
        else s=sum(x<<1|1,q);
        if(s==0) s=T[x].s.back();
        return s;
    }
}
namespace sgt2
{
    int tot;
    struct tree
    {
        int l,r,s;
    }T[N<<3];
    void pushup(int x)
    {
        T[x].s=T[T[x].l].s+T[T[x].r].s;
    }
    void add(int &x,int ls,int rs,int q)
    {
        if(x==0) x=++tot;
        if(ls==rs)
        {
            T[x].s=1;
            return;
        }
        int z=ls+rs>>1;
        if(q<=z) add(T[x].l,ls,z,q);
        else add(T[x].r,z+1,rs,q);
        pushup(x);
    }
    int merge(int x1,int x2,int ls,int rs)
    {
        if(x1==0||x2==0) return x1+x2;
        if(ls==rs)
        {
            T[x1].s=T[x1].s|T[x2].s;
            return x1;
        }
        int z=ls+rs>>1;
        T[x1].l=merge(T[x1].l,T[x2].l,ls,z);
        T[x1].r=merge(T[x1].r,T[x2].r,z+1,rs);
        pushup(x1);
        return x1;
    }
}
void dfs(int x)
{
    for(auto i:e[x]) sgt2::add(rt[x],1,q3,i);
    for(auto i:d[x])
    {
        dfs(i);
        rt[x]=sgt2::merge(rt[x],rt[i],1,q3);
    }
    f[x]=sgt2::T[rt[x]].s;
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=n;++i)
    {
        read(a[i].x1),read(a[i].y1),read(a[i].x2),read(a[i].y2);
        b1[++q1]=a[i].x1,b1[++q1]=a[i].x2+1;
        b2[++q2]=a[i].y1,b2[++q2]=a[i].y2+1;
    }
    sort(b1+1,b1+q1+1);
    sort(b2+1,b2+q2+1);
    q1=unique(b1+1,b1+q1+1)-b1-1;
    q2=unique(b2+1,b2+q2+1)-b2-1;
    for(int i=1;i<=n;++i)
    {
        a[i].x1=lower_bound(b1+1,b1+q1+1,a[i].x1)-b1;
        a[i].x2=lower_bound(b1+1,b1+q1+1,a[i].x2+1)-b1-1;
        a[i].y1=lower_bound(b2+1,b2+q2+1,a[i].y1)-b2;
        a[i].y2=lower_bound(b2+1,b2+q2+1,a[i].y2+1)-b2-1;
        c1[a[i].x1].push_back({a[i].y1,a[i].y2,i});
        c2[a[i].x2+1].push_back({a[i].y1,a[i].y2,i});
    }
    for(int i=1;i<=m;++i)
    {
        int x,y,k;
        read(x),read(y),read(k);
        x=upper_bound(b1+1,b1+q1+1,x)-b1-1;
        y=upper_bound(b2+1,b2+q2+1,y)-b2-1;
        c3[x].push_back({y,k});
        b3[++q3]=k;
    }
    sort(b3+1,b3+q3+1);
    q3=unique(b3+1,b3+q3+1)-b3-1;
    sgt1::build(1,1,q2);
    for(int i=1;i<=q1;++i)
    {
        for(auto j:c2[i])
        {
            sgt1::add(1,j.l,j.r,-1,j.t);
        }
        for(auto j:c1[i])
        {
            int z=sgt1::sum(1,j.l);
            d[z].push_back(j.t);
            sgt1::add(1,j.l,j.r,1,j.t);
        }
        for(auto j:c3[i])
        {
            j.k=lower_bound(b3+1,b3+q3+1,j.k)-b3;
            int z=sgt1::sum(1,j.x);
            if(z) e[z].push_back(j.k);
        }
    }
    dfs(0);
    for(int i=1;i<=n;++i)
    {
        print(f[i]);
        putchar('\n');
    }
    return 0;
}