#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=21,M=100001;
const ll P=998244353;
int n,m,q,b[M][N];
ll L,a[N][N],d1[N],d2[N],pa[N][N][N],pd1[N][N],pd2[N][N],jc[N],ivjc[N];
ll qpow(ll a,ll b)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
struct poly
{
    int n=-1;
    ll *a=NULL;
    void resize(int _n)
    {
        n=_n;
        if(a!=NULL) delete[] a;
        a=new ll[n+1];
        for(int i=0;i<=n;++i) a[i]=0;
    }
    poly() {}
    poly(ll x):n(0)
    {
        if(a!=NULL) delete[] a;
        a=new ll[n+1];
        a[0]=x;
    }
    poly(const vector<ll> &x):n(x.size()-1)
    {
        if(a!=NULL) delete[] a;
        a=new ll[n+1];
        for(int i=0;i<=n;++i) a[i]=x[i];
    }
    poly(const poly& x)
    {
        if(this!=&x)
        {
            n=x.n;
            delete[] a,a=new ll[n+1];
            for(int i=0;i<=n;++i) a[i]=x[i];
        }
    }
    ~poly()
    {
        if(a!=NULL) delete[] a,a=NULL;
    }
    poly& operator=(const poly& x)
    {
        if(this!=&x)
        {
            n=x.n;
            delete[] a,a=new ll[n+1];
            for(int i=0;i<=n;++i) a[i]=x[i];
        }
        return *this;
    }
    ll &operator[](size_t pos) {return a[pos];}
    ll operator[](size_t pos) const {return a[pos];}
    ll operator()(ll x)
    {
        ll s=0,w=1;
        for(int i=0;i<=n;++i) s=(s+w*a[i]%P)%P,w=w*x%P;
        return s;
    }
    poly operator()(poly x)
    {
        poly s,w=1;
        for(int i=0;i<=n;++i) s=s+w*a[i],w=w*x;
        return s;
    }
    friend poly operator+(const poly &a,const poly &b)
    {
        poly c;
        c.resize(max(a.n,b.n));
        for(int i=0;i<=c.n;++i)
        {
            c[i]=((i<=a.n?a[i]:0)+(i<=b.n?b[i]:0))%P;
        }
        return c;
    }
    friend poly operator*(const poly &a,const poly &b)
    {
        poly c;
        c.resize(a.n+b.n);
        for(int i=0;i<=a.n;++i)
        {
            for(int j=0;j<=b.n;++j) c[i+j]=(c[i+j]+a[i]*b[j])%P;
        }
        return c;
    }
}f[N],pf[N][N],g[N];
void init()
{
    jc[0]=1;
    for(int i=1;i<=20;++i) jc[i]=jc[i-1]*i%P;
    ivjc[20]=inv(jc[20]);
    for(int i=20;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    static poly p1[N],p2[N];
    static int p[N];
    for(int k=0;k<=10;++k)
    {
        for(int i=0;i<=k+1;++i)
        {
            if(i) p[i]=p[i-1];
            p[i]=(p[i]+qpow(i,k))%P;
            if(i==0&&k!=0) p[0]=0;
        }
        p1[0]=poly({0,1});
        p2[k+2]=1;
        for(int i=1;i<=k+1;++i)
        {
            p1[i]=p1[i-1]*poly({-i,1});
        }
        for(int i=k+1;i>=0;--i)
        {
            p2[i]=p2[i+1]*poly({-i,1});
        }
        poly s=p2[1]*p[0]*ivjc[k+1]*(((k+1)&1)?-1:1);
        for(int i=1;i<=k+1;++i)
        {
            s=s+p1[i-1]*p2[i+1]*p[i]*ivjc[i]*ivjc[k+1-i]*(((k+1-i)&1)?-1:1);
        }
        g[k]=s;
    }
}
poly sum(const poly &a)
{
    poly s;
    for(int i=0;i<=a.n;++i) s=s+g[i]*a[i];
    return s;
}
void check1(int x,int i,int j)
{
    if(i==0) d1[j]=max(d1[j],d2[x]-a[j][x]+(j<i));
    else if(j==0) d2[i]=min(d2[i],d2[x]-a[i][x]-(j<i));
    else a[j][i]=min(a[j][i],a[j][x]-a[i][x]-(j<i));
}
void check2(int x,int i,int j)
{
    if(i==0) d2[j]=min(d2[j],d1[x]+a[x][j]-(j<i));
    else if(j==0) d1[i]=max(d1[i],d1[x]+a[x][i]+(j<i));
    else a[i][j]=min(a[i][j],a[x][j]-a[x][i]-(j<i));
}
void check3(int x,int i,int j)
{
    if(i==0) d2[j]=min(d2[j],d2[x]+a[x][j]);
    else if(j==0) d1[i]=max(d1[i],d1[x]-a[i][x]);
    else if(i!=0&&j!=0) a[i][j]=min(a[i][j],a[x][j]+a[i][x]);
}
ll dfs(int x)
{
    if(d1[x]>d2[x]||a[x][x]<0) return 0;
    f[x]=sum(f[x]);
    if(x==1)
    {
        return f[1](d2[1]%P)-f[1]((d1[1]-1)%P)%P;
    }
    for(int i=1;i<=n;++i) pd1[x][i]=d1[i],pd2[x][i]=d2[i],pf[x][i]=f[i];
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) pa[x][i][j]=a[i][j];
    }
    ll s=0;
    for(int t=0;t<=x-1;++t)
    {
        for(int i=1;i<=n;++i) d1[i]=pd1[x][i],d2[i]=pd2[x][i],f[i]=pf[x][i];
        for(int j=0;j<=x-1;++j)
        {
            if(j!=t) check1(x,t,j);
        }
        for(int j=0;j<=x-1;++j) check3(x,t,j);
        if(t==0) f[x-1]=f[x-1]*f[x](d2[x]%P);
        else
        {
            f[t]=f[t]*f[x](poly({a[t][x]%P,1}));
        }
        s=(s+dfs(x-1))%P;
        for(int i=1;i<=n;++i) a[t][i]=pa[x][t][i],a[i][t]=pa[x][i][t];
    }
    for(int t=0;t<=x-1;++t)
    {
        for(int i=1;i<=n;++i) d1[i]=pd1[x][i],d2[i]=pd2[x][i],f[i]=pf[x][i];
        for(int j=0;j<=x-1;++j)
        {
            if(j!=t) check2(x,t,j);
        }
        for(int j=0;j<=x-1;++j) check3(x,j,t);
        if(t==0) f[x-1]=f[x-1]*f[x]((d1[x]-1)%P);
        else
        {
            f[t]=f[t]*f[x](poly({(-a[x][t]-1)%P,1}));
        }
        s=(s-dfs(x-1))%P;
        for(int i=1;i<=n;++i) a[t][i]=pa[x][t][i],a[i][t]=pa[x][i][t];
    }
    return s;
}
int popc(int x)
{
    int s=0;
    while(x) x^=x&-x,++s;
    return s;
}
int main()
{
    scanf("%d%d%lld",&n,&m,&L);
    init();
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) a[i][j]=1e15;
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        a[y][x]=min(a[y][x],w);
    }
    for(int i=1;i<=n;++i) d1[i]=0,d2[i]=L,f[i]=1;
    printf("%lld",(dfs(n)%P+P)%P);
    return 0;
}