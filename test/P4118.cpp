#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
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
constexpr int N=200001,M=700;
int n,m,q,a[N],d[N];
ll g[N];
struct qry
{
    int z,l,r,k;
}b[N];
struct str
{
    ll s,ls,rs,w;
    str() {}
    str(ll s,ll ls,ll rs,ll w):s(s),ls(ls),rs(rs),w(w) {}
    friend str operator+(const str &a,const str &b)
    {
        return str(max(a.rs+b.ls,max(a.s,b.s)),max(a.ls,a.w+b.ls),max(b.rs,b.w+a.rs),a.w+b.w);
    }
}f[N];
struct pt
{
    ll x,y;
    pt():x(0),y(0) {}
    pt(ll x,ll y):x(x),y(y) {}
    friend pt operator+(const pt &a,const pt &b)
    {
        return pt(a.x+b.x,a.y+b.y);
    }
    friend pt operator-(const pt &a,const pt &b)
    {
        return pt(a.x-b.x,a.y-b.y);
    }
    friend ll operator^(const pt &a,const pt &b)
    {
        return a.x*b.y-a.y*b.x;
    }
};
struct poly
{
    int n;
    ll k;
    pt *p=NULL;
    void resize(int x)
    {
        if(p==NULL) p=new pt[x+10];
        n=k=0;
    }
    void solve()
    {
        if(k==0) return;
        for(int i=1;i<=n;++i) p[i].y+=p[i].x*k;
        k=0;
    }
    void set(const poly &a,const pt &x)
    {
        n=a.n,k=a.k;
        for(int i=1;i<=n;++i)
        {
            p[i].x=a.p[i].x+x.x;
            p[i].y=a.p[i].y+x.y-x.x*k;
        }
    }
    void merge(poly &a,poly &b)
    {
        if(a.k!=b.k) a.solve(),b.solve();
        n=a.n+b.n;
        k=a.k;
        int x=0,x1=0,x2=0;
        while(x1<a.n||x2<b.n)
        {
            ++x;
            if(x1<a.n&&(x2==b.n||((a.p[x1]-a.p[x1+1])^(b.p[x2]-b.p[x2+1]))<=0)) ++x1,p[x]=p[x-1]+(a.p[x1]-a.p[x1-1]);
            else ++x2,p[x]=p[x-1]+(b.p[x2]-b.p[x2-1]);
        }
    }
    void max(poly &a)
    {
        if(k!=a.k) solve(),a.solve();
        static pt z[N];
        int x=0,x1=0,x2=0;
        while(x1<n||x2<a.n)
        {
            if(x1<n&&(x2==a.n||p[x1+1].x<=a.p[x2+1].x))
            {
                z[++x]=p[++x1];
                if(x2<a.n&&z[x].x==a.p[x2+1].x) z[x].y=std::max(z[x].y,a.p[++x2].y);
            }
            else z[++x]=a.p[++x2];
        }
        n=0;
        for(int i=1;i<=x;++i)
        {
            while(n>0&&((p[n-1]-p[n])^(p[n]-z[i]))>0) --n;
            p[++n]=z[i];
        }
    }
    ll sum()
    {
        auto sum=[&](int x)
        {
            return k*p[x].x+p[x].y;
        };
        int l=0,r=n;
        while(l<r)
        {
            int z=l+r>>1;
            if(sum(z)>sum(z+1)) r=z;
            else l=z+1;
        }
        return sum(l);
    }
};
namespace sgt
{
    int a[N];
    struct tree
    {
        int x,l,r;
        ll k,w;
        poly s,ls,rs;
    }T[M<<2];
    void pushup(int x)
    {
        T[x].w=T[x<<1].w+T[x<<1|1].w;
        T[x].s.merge(T[x<<1].rs,T[x<<1|1].ls);
        T[x].s.max(T[x<<1].s);
        T[x].s.max(T[x<<1|1].s);
        T[x].ls.set(T[x<<1|1].ls,pt(T[x<<1].r-T[x<<1].l+1,T[x<<1].w));
        T[x].ls.max(T[x<<1].ls);
        T[x].rs.set(T[x<<1].rs,pt(T[x<<1|1].r-T[x<<1|1].l+1,T[x<<1|1].w));
        T[x].rs.max(T[x<<1|1].rs);
    }
    void maketag(int x,ll k)
    {
        T[x].w+=k*(T[x].r-T[x].l+1);
        T[x].s.k+=k;
        T[x].ls.k+=k;
        T[x].rs.k+=k;
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
        T[x].k=0;
        T[x].s.resize(r-l+1);
        T[x].ls.resize(r-l+1);
        T[x].rs.resize(r-l+1);
        T[x].w=0;
        if(l==r)
        {
            T[x].s.n=T[x].ls.n=T[x].rs.n=1;
            T[x].s.p[1]=T[x].ls.p[1]=T[x].rs.p[1]=pt(1,a[l]);
            T[x].w=a[l];
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
            maketag(x,k);
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
    str sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return str(T[x].s.sum(),T[x].ls.sum(),T[x].rs.sum(),T[x].w);
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(r<=z) return sum(x<<1,l,r);
        else if(l>z) return sum(x<<1|1,l,r);
        else return sum(x<<1,l,r)+sum(x<<1|1,l,r);
    }
}
void sort()
{
    constexpr int K=8,Q=(1<<K)-1;
    static int p[N],h1[Q+1],h2[Q+1],h3[Q+1],h4[Q+1];
    memset(h1,0,sizeof(h1));
    memset(h2,0,sizeof(h2));
    memset(h3,0,sizeof(h3));
    memset(h4,0,sizeof(h4));
    for(int i=1;i<=q;++i)
    {
        ++h1[g[d[i]]&Q];
        ++h2[(g[d[i]]>>K)&Q];
        ++h3[(g[d[i]]>>(K*2))&Q];
        ++h4[(g[d[i]]>>(K*3))&Q];
        p[i]=d[i];
    }
    for(int i=1;i<=Q;++i)
    {
        h1[i]+=h1[i-1];
        h2[i]+=h2[i-1];
        h3[i]+=h3[i-1];
        h4[i]+=h4[i-1];
    }
    for(int i=q;i>=1;--i) d[h1[g[p[i]]&Q]--]=p[i];
    for(int i=q;i>=1;--i) p[h2[(g[d[i]]>>K)&Q]--]=d[i];
    for(int i=q;i>=1;--i) d[h3[(g[p[i]]>>(K*2))&Q]--]=p[i];
    for(int i=q;i>=1;--i) p[h4[(g[d[i]]>>(K*3))&Q]--]=d[i];
    int x=0,y=0;
    for(int i=1;i<=q;++i) y+=(g[p[i]]<0);
    for(int i=1;i<=q;++i)
    {
        if(g[p[i]]<0) d[++x]=p[i];
        else d[++y]=p[i];
    }
}
int main()
{
    read(n,m);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<=m;++i)
    {
        read(b[i].z);
        if(b[i].z==1) read(b[i].l,b[i].r,b[i].k);
        else if(b[i].z==2) read(b[i].l,b[i].r);
    }
    for(int i=0;i<=n/M;++i)
    {
        for(int j=0;j<=M-1;++j) sgt::a[j]=a[i*M+j];
        sgt::build(1,0,M-1);
        int l=i*M,r=(i+1)*M-1;
        q=0;
        for(int j=0;j<=m;++j) g[j]=0;
        ll w=0;
        auto solve=[&]()
        {
            sort();
            int x0=0,x1=0,x2=0;
            for(int j=1;j<=q;++j)
            {
                auto sum=[&](const poly &p,int x)
                {
                    return (g[d[j]]-w+p.k)*p.p[x].x+p.p[x].y;
                };
                while(x0+1<=sgt::T[1].s.n&&sum(sgt::T[1].s,x0)<sum(sgt::T[1].s,x0+1)) ++x0;
                while(x1+1<=sgt::T[1].ls.n&&sum(sgt::T[1].ls,x1)<sum(sgt::T[1].ls,x1+1)) ++x1;
                while(x2+1<=sgt::T[1].rs.n&&sum(sgt::T[1].rs,x2)<sum(sgt::T[1].rs,x2+1)) ++x2;
                f[d[j]]=f[d[j]]+str(sum(sgt::T[1].s,x0),sum(sgt::T[1].ls,x1),sum(sgt::T[1].rs,x2),sgt::T[1].w+(g[d[j]]-w)*M);
            }
            q=w=0;
        };
        for(int j=1;j<=m;++j)
        {
            if(b[j].z==1)
            {
                if((b[j].l>=l&&b[j].l<=r)||(b[j].r>=l&&b[j].r<=r))
                {
                    if(q>0) solve();
                    sgt::add(1,max(b[j].l-l,0),min(b[j].r-l,M-1),b[j].k);
                }
                else if(b[j].l<l&&b[j].r>r)
                {
                    sgt::maketag(1,b[j].k);
                    w+=b[j].k;
                }
            }
            else if(b[j].z==2)
            {
                if((b[j].l>=l&&b[j].l<=r)||(b[j].r>=l&&b[j].r<=r))
                {
                    f[j]=f[j]+sgt::sum(1,max(b[j].l-l,0),min(b[j].r-l,M-1));
                }
                else if(b[j].l<l&&b[j].r>r)
                {
                    d[++q]=j;
                    g[j]=w;
                }
            }
        }
        if(q>0) solve();
    }
    for(int i=1;i<=m;++i)
    {
        if(b[i].z==2)
        {
            print(f[i].s);
            putchar('\n');
        }
    }
    return 0;
}