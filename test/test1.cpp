#pragma GCC optimize("Ofast","inline")
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=21,M=100001;
const ll P=998244353;
int n,m,q,b[M][N];
ll L,a[N][N],c[N][N],d1[N],d2[N],jc[N],ivjc[N];
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
}f[N],g[N];
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
void dfs(int x)
{
    static int c[N];
    if(x==0)
    {
        ++q;
        for(int i=1;i<=n;++i) b[q][i]=c[i];
        return;
    }
    for(c[x]=0;c[x]<=x-1;++c[x]) dfs(x-1);
}
void check1(int x,int i,int j)
{
    if(i==0) d1[j]=max(d1[j],d2[x]-c[j][x]+(j<i));
    else if(j==0) d2[i]=min(d2[i],d2[x]-c[i][x]-(j<i));
    else c[j][i]=min(c[j][i],c[j][x]-c[i][x]-(j<i));
}
void check2(int x,int i,int j)
{
    if(i==0) d2[j]=min(d2[j],d1[x]+c[x][j]-(j<i));
    else if(j==0) d1[i]=max(d1[i],d1[x]+c[x][i]+(j<i));
    else c[i][j]=min(c[i][j],c[x][j]-c[x][i]-(j<i));
}
void check3(int x,int i,int j)
{
    if(i==0) d2[j]=min(d2[j],d2[x]+c[x][j]);
    else if(j==0) d1[i]=max(d1[i],d1[x]-c[i][x]);
    else if(i!=0&&j!=0) c[i][j]=min(c[i][j],c[x][j]+c[i][x]);
}
ll solve(int p,int t)
{
    for(int i=1;i<=n;++i) d1[i]=0,d2[i]=L,f[i]=1;
    ll w=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) c[i][j]=a[i][j];
    }
    for(int i=n;i>=2;--i)
    {
        if((p&(1<<(i-1)))==0)
        {
            for(int j=0;j<=i-1;++j)
            {
                if(j!=b[t][i]) check1(i,b[t][i],j);
            }
            for(int j=0;j<=i-1;++j) check3(i,b[t][i],j);
            if(b[t][i]==0) w=w*sum(f[i])(d2[i]%P)%P;
            else
            {
                f[b[t][i]]=f[b[t][i]]*sum(f[i])(poly({c[b[t][i]][i]%P,1}));
            }
        }
        else
        {
            for(int j=0;j<=i-1;++j)
            {
                if(j!=b[t][i]) check2(i,b[t][i],j);
            }
            for(int j=0;j<=i-1;++j) check3(i,j,b[t][i]);
            if(b[t][i]==0) w=w*sum(f[i])((d1[i]-1)%P)%P;
            else
            {
                f[b[t][i]]=f[b[t][i]]*sum(f[i])(poly({(-c[i][b[t][i]]-1)%P,1}));
            }
        }
        if(d1[i]>d2[i]||c[i][i]<0) return 0;
    }
    if(d1[1]>d2[1]||c[1][1]<0) return 0;
    f[1]=sum(f[1]);
    if((p&1)==0) return w*f[1](d2[1]%P)%P;
    else return w*f[1]((d1[1]-1)%P)%P;
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
    dfs(n);
    ll s=0;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        ll w=0;
        for(int j=1;j<=q;++j)
        {
            w=(w+solve(i,j))%P;
        }
        if(popc(i)%2==0) s=(s+w)%P;
        else s=(s-w)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}