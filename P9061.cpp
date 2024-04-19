#pragma GCC optimize("Ofast","inline")
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
const int N=10000001;
int n,m,rt,f[N];
bool h[N];
struct
{
    int x,y,t;
}a1[N];
struct
{
    int z,x,y;
}a2[N];
struct
{
    int x,y;
}a3[N];
vector<pair<int,int>> b1[N],b2[N];
namespace fhq
{
    int tot;
    struct tree
    {
        int x1,x2,k1,k2,l,r,s,h;
    }T[N];
    inline void pushup(int x)
    {
        T[x].s=T[T[x].l].s+T[T[x].r].s+1;
    }
    inline void pushdown(int x)
    {
        if(T[x].k1)
        {
            if(T[x].l) T[T[x].l].x1=T[T[x].l].k1=T[x].k1;
            if(T[x].r) T[T[x].r].x1=T[T[x].r].k1=T[x].k1;
            T[x].k1=0;
        }
        if(T[x].k2)
        {
            if(T[x].l) T[T[x].l].x2=T[T[x].l].k2=T[x].k2;
            if(T[x].r) T[T[x].r].x2=T[T[x].r].k2=T[x].k2;
            T[x].k2=0;
        }
    }
    void split(int x,int k,int &x1,int &x2)
    {
        if(x==0)
        {
            x1=x2=0;
            return;
        }
        pushdown(x);
        if(T[x].x1-T[x].x2<=k)
        {
            x1=x;
            split(T[x].r,k,T[x].r,x2);
        }
        else
        {
            x2=x;
            split(T[x].l,k,x1,T[x].l);
        }
        pushup(x);
    }
    int merge(int x1,int x2)
    {
        if(x1==0||x2==0) return x1|x2;
        if(T[x1].h<T[x2].h)
        {
            pushdown(x1);
            T[x1].r=merge(T[x1].r,x2);
            pushup(x1);
            return x1;
        }
        else
        {
            pushdown(x2);
            T[x2].l=merge(x1,T[x2].l);
            pushup(x2);
            return x2;
        }
    }
    void add(vector<pair<int,int>> k)
    {
        sort(k.begin(),k.end(),[](const pair<int,int> &a,const pair<int,int> &b){return a.first-a.second<b.first-b.second;});
        int p1=0,p2=rt;
        for(auto i:k)
        {
            int z;
            split(p2,i.first-i.second,z,p2);
            T[++tot].x1=i.first;
            T[tot].x2=i.second;
            T[tot].l=T[tot].r=0;
            T[tot].s=1;
            T[tot].h=rand();
            p1=merge(p1,merge(z,tot));
        }
        p1=merge(p1,p2);
        rt=p1;
    }
    pair<int,int> num1(int x,int k)
    {
        pair<int,int> s=make_pair(1e9,1e9);
        while(x)
        {
            pushdown(x);
            if(k<T[x].x2) x=T[x].r;
            else s=make_pair(T[x].x1,T[x].x2),x=T[x].l;
        }
        return s;
    }
    pair<int,int> num2(int x,int k)
    {
        pair<int,int> s=make_pair(1e9,1e9);
        while(x)
        {
            pushdown(x);
            if(k<T[x].x1) x=T[x].l;
            else s=make_pair(T[x].x1,T[x].x2),x=T[x].r;
        }
        return s;
    }
    int sum1(int x,int k)
    {
        int s=0;
        while(x)
        {
            pushdown(x);
            if(T[x].x2>k) s+=T[T[x].l].s+1,x=T[x].r;
            else x=T[x].l;
        }
        return s;
    }
    int sum2(int x,int k)
    {
        int s=0;
        while(x)
        {
            pushdown(x);
            if(T[x].x1>k) s+=T[T[x].r].s+1,x=T[x].l;
            else x=T[x].r;
        }
        return s;
    }
}
namespace sgt1
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]=min(T[x],k),x+=x&-x;
    }
    int sum(int x)
    {
        int s=1e9;
        while(x>=1) s=min(s,T[x]),x-=x&-x;
        return s;
    }
}
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
int main()
{
    srand(147258369);
    read(n,m);
    for(int i=1;i<=n;++i) read(a1[i].x,a1[i].y);
    for(int i=1;i<=m;++i) read(a2[i].z,a2[i].x,a2[i].y,a3[i].x,a3[i].y);

    for(int i=1;i<=m;++i)
    {
        b1[a2[i].x].push_back(make_pair(a2[i].y,i));
    }
    for(int i=1;i<=n;++i)
    {
        b2[a1[i].x].push_back(make_pair(a1[i].y,i));
    }
    for(int i=1;i<=n;++i) sgt1::T[i]=m+1;
    for(int i=n;i>=1;--i)
    {
        for(auto j:b1[i]) sgt1::add(n-j.first+1,j.second);
        for(auto j:b2[i]) a1[j.second].t=sgt1::sum(n-j.first+1);
    }
    for(int i=1;i<=n;++i) --f[a1[i].t-1];
    for(int i=m;i>=1;--i) f[i]+=f[i+1];


    for(int i=1;i<=n;++i) b1[i].clear(),b2[i].clear();
    for(int i=1;i<=n;++i)
    {
        b1[a1[i].x].push_back(make_pair(a1[i].y,a1[i].t));
    }
    for(int i=1;i<=m;++i)
    {
        b2[a3[i].x].push_back(make_pair(a3[i].y,i));
    }
    for(int i=1;i<=n;++i) sgt1::T[i]=m+1;
    for(int i=1;i<=n;++i)
    {
        for(auto j:b1[i]) sgt1::add(j.first,m-j.second+1);
        for(auto j:b2[i]) h[j.second]=m-sgt1::sum(j.first)+1>j.second;
    }

    for(int i=1;i<=m+1;++i) b1[i].clear(),b2[i].clear();
    for(int i=1;i<=n;++i)
    {
        b1[a1[i].t].push_back(make_pair(a1[i].x,1));
    }
    for(int i=1;i<=m;++i)
    {
        b2[i].push_back(make_pair(a3[i].x,i));
    }
    for(int i=1;i<=n;++i) sgt2::T[i]=0;
    for(int i=m;i>=1;--i)
    {
        for(auto j:b1[i+1]) sgt2::add(j.first,j.second);
        for(auto j:b2[i]) f[j.second]+=sgt2::sum(j.first);
    }

    for(int i=1;i<=m+1;++i) b1[i].clear(),b2[i].clear();
    for(int i=1;i<=n;++i)
    {
        b1[a1[i].t].push_back(make_pair(a1[i].y,1));
    }
    for(int i=1;i<=m;++i)
    {
        b2[i].push_back(make_pair(a3[i].y,i));
    }
    for(int i=1;i<=n;++i) sgt2::T[i]=0;
    for(int i=m;i>=1;--i)
    {
        for(auto j:b1[i+1]) sgt2::add(j.first,j.second);
        for(auto j:b2[i]) f[j.second]+=sgt2::sum(j.first);
    }

    for(int i=1;i<=n;++i) b1[i].clear(),b2[i].clear();
    for(int i=1;i<=n;++i)
    {
        b1[a1[i].x].push_back(make_pair(a1[i].y,1));
    }
    for(int i=1;i<=m;++i)
    {
        b2[a3[i].x].push_back(make_pair(a3[i].y,i));
    }
    for(int i=1;i<=n;++i) sgt2::T[i]=0;
    for(int i=n;i>=1;--i)
    {
        for(auto j:b2[i]) f[j.second]+=sgt2::sum(n-j.first);
        for(auto j:b1[i]) sgt2::add(n-j.first+1,j.second);
    }

    for(int i=1;i<=m;++i)
    {
        if(h[i]==false) f[i]=0;
    }
    
    for(int i=1;i<=m;++i) b1[i].clear();
    for(int i=1;i<=n;++i)
    {
        b1[a1[i].t].push_back(make_pair(a1[i].x,a1[i].y));
    }
    for(int i=1;i<=m;++i)
    {
        auto l=fhq::num1(rt,a2[i].y);
        if(l.first!=1e9&&l.first<=a2[i].x)
        {
            auto r=fhq::num2(rt,a2[i].x);
            int x1,x2,x3;
            fhq::split(rt,(l.first-l.second)-1,x1,x2);
            fhq::split(x2,(r.first-r.second),x2,x3);
            if(a2[i].z==1)
            {
                fhq::T[x2].x2=a2[i].y;
                fhq::T[x2].k2=a2[i].y;
            }
            else
            {
                fhq::T[x2].x1=a2[i].x;
                fhq::T[x2].k1=a2[i].x;
            }
            rt=fhq::merge(fhq::merge(x1,x2),x3);
        }
        vector<pair<int,int>> p;
        for(auto j:b1[i])
        {
            if(a2[i].z==1) j.second=max(j.second,a2[i].y);
            else j.first=max(j.first,a2[i].x);
            p.push_back(j);
        }
        fhq::add(p);
        f[i]+=max(fhq::T[rt].s-fhq::sum1(rt,a3[i].y)-fhq::sum2(rt,a3[i].x),0);
        print(f[i]);
        putchar('\n');
    }
    return 0;
}