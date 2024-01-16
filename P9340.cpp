#include<bits/stdc++.h>
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
const int N=1000001,M=31;
int n,m,q,t,tot,s,b[N],c[N],e[N],f[N],h[N];
vector<int> a[N];
struct tree
{
    int f,d,b;
}T[N];
struct str
{
    int l,r,t;
    str() {}
    str(int l,int r,int t):l(l),r(r),t(t) {}
};
vector<str> d[N];
struct
{
    int l,r;
}g[N];
namespace ST
{
    int a[N][M],lg[N];
    void init()
    {
        for(int i=0;i<=30;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,n);++j) lg[j]=i;
        }
        for(int i=1;i<=n-1;++i) a[i][0]=c[i+1];
        for(int i=1;i<=30;++i)
        {
            for(int j=1;j<=n-1;++j)
            {
                if(j+(1<<i)-1<=n-1) a[j][i]=min(a[j][i-1],a[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int sum(int x,int y)
    {
        if(x==y) return T[b[x]].d;
        if(x>y) swap(x,y);
        --y;
        return min(a[x][lg[y-x+1]],a[y-(1<<lg[y-x+1])+1][lg[y-x+1]]);
    }
}
void dfs(int x)
{
    static int u=0;
    T[x].b=++tot;
    c[T[x].b]=u;
    u=T[x].d;
    for(auto i:a[x])
    {
        if(i==T[x].f) continue;
        T[i].f=x;
        T[i].d=T[x].d+1;
        dfs(i);
        u=min(u,T[x].d);
    }
}
bool cmp(str a,str b)
{
    return a.r>b.r;
}
void add(int x)
{
    if(h[x]==0)
    {
        int l=g[x].l,r=g[x].r;
        s+=T[x].d;
        if(l&&r) s+=ST::sum(T[l].b,T[r].b);
        if(l) s-=ST::sum(T[x].b,T[l].b);
        if(r) s-=ST::sum(T[x].b,T[r].b);
        g[l].r=x,g[r].l=x;
    }
    ++h[x];
}
void del(int x)
{
    --h[x];
    if(h[x]==0)
    {
        int l=g[x].l,r=g[x].r;
        s-=T[x].d;
        if(l&&r) s-=ST::sum(T[l].b,T[r].b);
        if(l) s+=ST::sum(T[x].b,T[l].b);
        if(r) s+=ST::sum(T[x].b,T[r].b);
        g[l].r=r,g[r].l=l;
    }
}
int main()
{
    read(n),read(t),read(m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        read(x),read(y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs(1);
    for(int i=1;i<=n;++i) b[T[i].b]=i;
    // for(int i=1;i<=n-1;++i) printf("%d %d: %d\n",b[i],b[i+1],c[i+1]);
    ST::init();
    for(int i=1;i<=t;++i) read(f[i]);
    q=sqrt(t)*2;
    for(int i=1;i<=m;++i)
    {
        int l,r;
        read(l),read(r);
        d[(l-1)/q].push_back(str(l,r,i));
    }
    for(int i=0;i<=(t-1)/q;++i)
    {
        s=0;
        for(int j=1;j<=n;++j)
        {
            g[j].l=b[T[j].b-1],g[j].r=b[T[j].b+1];
            s+=T[j].d;
        }
        g[0].r=b[1],g[0].l=b[n];
        for(int j=1;j<=n-1;++j) s-=c[j+1];
        for(int j=1;j<=n;++j) h[j]=1;
        for(int j=1;j<=t;++j) ++h[f[j]];
        for(int j=1;j<=n;++j) del(j);
        for(int j=1;j<=i*q;++j) del(f[j]);
        sort(d[i].begin(),d[i].end(),cmp);
        int r=t;
        for(auto j:d[i])
        {
            while(r>j.r) del(f[r--]);
            for(int k=i*q+1;k<=j.l-1;++k) del(f[k]);
            e[j.t]=s-ST::sum(T[g[0].l].b,T[g[0].r].b)+1;
            for(int k=j.l-1;k>=i*q+1;--k) add(f[k]);
        }
    }
    for(int i=1;i<=m;++i)
    {
        print(e[i]);
        putchar('\n');
    }
    return 0;
}