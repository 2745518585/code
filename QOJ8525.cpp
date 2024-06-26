#include<cstdio>
#include<algorithm>
#include<vector>
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
const int N=2000001;
int n,m,c[N],e[N],p[N];
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
    friend bool operator<(const pt &a,const pt &b)
    {
        if(a.x!=b.x) return a.x<b.x;
        return a.y<b.y;
    }
}a[N];
struct str
{
    ll a,b,w;
    ll operator()(const pt &p)
    {
        return a*p.x+b*p.y;
    }
}d[N];
vector<pt> b[N];
vector<pt> solve(const vector<pt> &a)
{
    vector<pt> p;
    for(auto i:a)
    {
        while(p.size()>0&&p.back().x==i.x&&p.back().y<=i.y) p.pop_back();
        while(p.size()>1&&((p[p.size()-2]-p[p.size()-1])^(p[p.size()-1]-i))>=0) p.pop_back();
        p.push_back(i);
    }
    return p;
}
vector<pt> merge(const vector<pt> &a,const vector<pt> &b)
{
    vector<pt> p;
    p.push_back(pt(0,a[0].y+b[0].y));
    int x1=0,x2=0;
    while(x1+1<a.size()||x2+1<b.size())
    {
        if(x1+1<a.size()&&(x2+1==b.size()||((a[x1]-a[x1+1])^(b[x2]-b[x2+1]))<=0)) ++x1,p.push_back(p.back()+(a[x1]-a[x1-1]));
        else ++x2,p.push_back(p.back()+(b[x2]-b[x2-1]));
    }
    return p;
}
vector<pt> max(const vector<pt> &a,const vector<pt> &b)
{
    vector<pt> p;
    p.push_back(pt(0,max(a[0].y,b[0].y)));
    int x1=0,x2=0;
    while(x1+1<a.size()||x2+1<b.size())
    {
        if(x1+1<a.size()&&(x2+1==b.size()||a[x1+1].x<=b[x2+1].x))
        {
            p.push_back(a[++x1]);
            if(x2+1<b.size()&&p.back().x==b[x2+1].x) p.back().y=std::max(p.back().y,b[++x2].y);
        }
        else p.push_back(b[++x2]);
    }
    return solve(p);
}
bool find(const vector<pt> &p,int &t,str k)
{
    while(t+1<p.size()&&k(p[t])<=k(p[t+1])) ++t;
    return k(p[t])>=k.w;
}
namespace sgt
{
    struct tree
    {
        int l,r,ts,tw;
        vector<pt> s,w;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].w=merge(T[x<<1].w,T[x<<1|1].w);
        T[x].s=max(merge(T[x<<1].s,T[x<<1|1].w),T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        if(l==r)
        {
            T[x].s={pt(0,0),a[l]};
            T[x].w={pt(0,0)};
            for(auto i:b[l]) T[x].w.push_back(i);
            T[x].s=solve(T[x].s);
            T[x].w=solve(T[x].w);
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    int sum(int x,int r,str &k)
    {
        if(T[x].r<=r&&!find(T[x].s,T[x].ts,k))
        {
            find(T[x].w,T[x].tw,k);
            k.w-=k(T[x].w[T[x].tw]);
            return 0;
        }
        if(T[x].l==T[x].r) return T[x].l;
        int z=T[x].l+T[x].r>>1;
        if(r>z)
        {
            int p=sum(x<<1|1,r,k);
            if(p) return p;
        }
        return sum(x<<1,r,k);
    }
}
bool cmp(int x,int y)
{
    if(d[x].a*d[y].b==d[y].a*d[x].b) return d[x].a+d[x].b>d[y].a+d[y].b;
    return d[x].a*d[y].b<d[y].a*d[x].b;
}
int main()
{
    read(n);
    for(int i=1;i<=n;++i)
    {
        if(i>1)
        {
            int k;
            read(k);
            for(int j=1;j<=k;++j)
            {
                ll x,y;
                read(x,y);
                b[i].push_back(pt(x,y));
            }
            sort(b[i].begin(),b[i].end());
        }
        read(a[i].x,a[i].y);
    }
    read(m);
    for(int i=1;i<=m;++i)
    {
        read(c[i],d[i].a,d[i].b,d[i].w);
    }
    for(int i=1;i<=m;++i) p[i]=i;
    sort(p+1,p+m+1,cmp);
    sgt::build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        e[p[i]]=sgt::sum(1,c[p[i]],d[p[i]]);
    }
    for(int i=1;i<=m;++i)
    {
        if(e[i]==0) printf("-1\n");
        else printf("%d\n",e[i]);
    }
    return 0;
}