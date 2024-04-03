#pragma GCC optimize("Ofast","inline")
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
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
const int N=1000001,M=31;
int n,m,tot,e[N];
ll b[N];
vector<int> a[N];
namespace ST
{
    int lg[N];
    ll a[N][M];
    int check(int x,int y)
    {
        return b[x]>b[y]?x:y;
    }
    void init()
    {
        for(int i=1;i<=n;++i) a[i][0]=e[i];
        for(int i=0;i<=20;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,n);++j) lg[j]=i;
        }
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j+(1<<i)-1<=n) a[j][i]=check(a[j][i-1],a[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int sum(int x,int y)
    {
        if(x>y) swap(x,y);
        return check(a[x][lg[y-x+1]],a[y-(1<<lg[y-x+1])+1][lg[y-x+1]]);
    }
}
struct tree
{
    int f,s,d,t,z,b;
}T[N];
struct str
{
    int x,y,t;
    str() {}
    str(int x,int y):x(x),y(y),t(ST::sum(T[x].b,T[y].b)) {}
    friend bool operator<(str x,str y)
    {
        return b[x.t]<b[y.t];
    }
};
priority_queue<str> Q1;
priority_queue<ll> Q2;
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(auto i:a[x])
    {
        if(i==T[x].f) continue;
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
    if(T[x].z) dfs2(T[x].z,t);
    for(auto i:a[x])
    {
        if(i==T[x].f||i==T[x].z) continue;
        dfs2(i,i);
    }
}
void solve(int x,int y)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>T[T[y].t].d)
        {
            Q1.push(str(T[x].t,x));
            x=T[T[x].t].f;
        }
        else
        {
            Q1.push(str(T[y].t,y));
            y=T[T[y].t].f;
        }
    }
    Q1.push(str(x,y));
}
int main()
{
    read(n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        read(x,y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for(int i=1;i<=n;++i) read(b[i]);
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=n;++i) e[T[i].b]=i;
    ST::init();
    read(m);
    ll las=0;
    for(int i=1;i<=m;++i)
    {
        int x,y,k;
        read(x,y,k);
        x=(x^las)%n+1,y=(y^las)%n+1;
        while(!Q1.empty()) Q1.pop();
        while(!Q2.empty()) Q2.pop();
        solve(x,y);
        for(int i=1;i<=k&&!Q1.empty();++i)
        {
            auto [x,y,t]=Q1.top();
            Q2.push(b[t]);
            Q1.pop();
            if(T[x].d>T[y].d) swap(x,y);
            if(T[x].d<T[t].d) Q1.push(str(x,T[t].f));
            if(T[t].d<T[y].d) Q1.push(str(T[t].z,y));
        }
        while(Q2.size()<k) Q2.push(0);
        ll s=0;
        static ll z[11];
        for(int i=1;i<=k;++i) z[i]=Q2.top(),Q2.pop();
        for(int i=62;i>=0;--i)
        {
            if((z[k]&(1ll<<i))!=0) s|=(1ll<<i);
            else
            {
                for(int j=1;j<=k;++j)
                {
                    z[j]&=(~(1ll<<i));
                    Q2.push(z[j]);
                }
                sort(z+1,z+k+1);
                int p=0;
                for(int j=1;j<=k&&!Q1.empty();++j)
                {
                    auto [x,y,t]=Q1.top();
                    if(b[t]<z[j]) break;
                    Q2.push(b[t]);
                    Q1.pop();
                    if(T[x].d>T[y].d) swap(x,y);
                    if(T[x].d<T[t].d) Q1.push(str(x,T[t].f));
                    if(T[t].d<T[y].d) Q1.push(str(T[t].z,y));
                }
                for(int j=1;j<=k;++j) z[j]=Q2.top(),Q2.pop();
            }
        }
        print(las=s);
        putchar('\n');
    }
    return 0;
}