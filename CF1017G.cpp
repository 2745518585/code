#include<cstdio>
#include<algorithm>
#include<vector>
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
const int N=1000001;
int n,m,tot;
vector<int> a[N];
struct tree
{
    int f,s,d,t,z,b,bm;
}T[N];
struct str
{
    int s,rs;
    str() {}
    str(int s,int rs):s(s),rs(rs) {}
};
str operator+(str a,str b)
{
    str c;
    c.rs=max(a.rs+b.s,b.rs);
    c.s=a.s+b.s;
    return c;
}
namespace sgt
{
    struct tree
    {
        int l,r,k;
        str s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=T[x<<1].s+T[x<<1|1].s;
    }
    void pushdown(int x)
    {
        if(!T[x].k) return;
        T[x<<1].s=str(-(T[x<<1].r-T[x<<1].l+1),-1);
        T[x<<1|1].s=str(-(T[x<<1|1].r-T[x<<1|1].l+1),-1);
        T[x<<1].k=T[x<<1|1].k=1;
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        T[x].k=0;
        if(l==r)
        {
            T[x].s=str(-1,-1);
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
            T[x].s.s+=k;
            T[x].s.rs+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
        pushup(x);
    }
    void add2(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s=str(-(T[x].r-T[x].l+1),-1);
            T[x].k=true;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add2(x<<1,l,r);
        if(r>z) add2(x<<1|1,l,r);
        pushup(x);
    }
    str sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        str s;
        if(r<=z) s=sum(x<<1,l,r);
        else if(l>z) s=sum(x<<1|1,l,r);
        else s=sum(x<<1,l,r)+sum(x<<1|1,l,r);
        return s;
    }
}
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(auto i:a[x])
    {
        T[i].f=x;
        dfs1(i);
        T[x].s+=T[i].s;
        if(T[i].s>T[T[x].z].s) T[x].z=i;
    }
}
void dfs2(int x,int t)
{
    T[x].b=++tot;
    T[x].t=t;
    if(T[x].z!=0) dfs2(T[x].z,t);
    for(auto i:a[x])
    {
        if(i==T[x].z) continue;
        dfs2(i,i);
    }
    T[x].bm=tot;
}
int query(int x)
{
    vector<pair<int,int>> p;
    while(x)
    {
        p.push_back(make_pair(T[T[x].t].b,T[x].b));
        x=T[T[x].t].f;
    }
    reverse(p.begin(),p.end());
    str s(0,0);
    for(auto i:p)
    {
        s=s+sgt::sum(1,i.first,i.second);
    }
    return s.rs;
}
int main()
{
    read(n),read(m);
    for(int i=2;i<=n;++i)
    {
        int x;
        read(x);
        a[x].push_back(i);
    }
    dfs1(1);
    dfs2(1,1);
    sgt::build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z,x;
        read(z),read(x);
        if(z==1)
        {
            sgt::add(1,T[x].b,1);
        }
        else if(z==2)
        {
            sgt::add2(1,T[x].b,T[x].bm);
            int z=query(x);
            sgt::add(1,T[x].b,-(z+1));
        }
        else if(z==3)
        {
            if(query(x)>=0) puts("black");
            else puts("white");
        }
    }
    return 0;
}