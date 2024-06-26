#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=8001;
const ll P=998244353;
int n,m,d[N];
ll jc[N],ivjc[N],pw[N],iv[N],ivm[N];
vector<int> a[N];
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
ll qpow(ll x,ll y)
{
    ll a=1,b=x;
    while(y!=0)
    {
        if(y&1) a=a*b%P;
        b=b*b%P;
        y>>=1;
    }
    return a;
}
struct len
{
    int l;
    len(int l):l(l) {}
};
struct poly
{
    int n=-1;
    ll *a=NULL;
    poly resize(int _n)
    {
        ll *_a=new ll[_n+1];
        for(int i=0;i<=min(n,_n);++i) _a[i]=a[i];
        for(int i=min(n,_n)+1;i<=_n;++i) _a[i]=0;
        n=_n;
        if(a!=NULL) delete[] a;
        a=_a;
        return *this;
    }
    poly(){}
    poly(len l)
    {
        resize(l.l);
    }
    poly(initializer_list<ll> p)
    {
        resize(p.size()-1);
        int l=0;
        for(auto i:p) a[l++]=i;
    }
    poly(int x)
    {
        resize(0);
        a[0]=x;
    }
    poly(const poly& p)
    {
        if(this!=&p)
        {
            delete[] a,a=NULL;
            n=p.n;
            a=new ll[n+2];
            for(int i=0;i<=n;++i) a[i]=p[i];
        }
    }
    ~poly()
    {
        if(a!=NULL) delete[] a,a=NULL;
    }
    poly& operator=(const poly& p)
    {
        if(this!=&p)
        {
            delete[] a,a=NULL;
            n=p.n;
            a=new ll[n+2];
            for(int i=0;i<=n;++i) a[i]=p[i];
        }
        return *this;
    }
    ll &operator[](size_t x) {return a[x];}
    const ll &operator[](size_t x) const {return a[x];}
    void print() const
    {
        for(int i=0;i<=n;++i) printf("%lld ",(a[i]%P+P)%P);
        printf("\n");
    }
    friend poly operator+(const poly &a,const poly &b)
    {
        poly c;
        c.resize(max(a.n,b.n));
        for(int i=0;i<=c.n;++i) c[i]=((i<=a.n?a[i]:0)+(i<=b.n?b[i]:0))%P;
        return c;
    }
    friend poly operator-(const poly &a,const poly &b)
    {
        poly c;
        c.resize(max(a.n,b.n));
        for(int i=0;i<=c.n;++i) c[i]=((i<=a.n?a[i]:0)-(i<=b.n?b[i]:0)+P)%P;
        return c;
    }
    poly NTT(int n,int u)
    {
        resize(n);
        int p=0;
        while((1<<p)<n) ++p;
        static int d[N<<2];
        for(int i=0;i<n;++i)
        {
            d[i]=(d[i>>1]>>1)|((i&1)<<(p-1));
        }
        for(int i=0;i<n;++i)
        {
            if(i<d[i]) swap(a[i],a[d[i]]);
        }
        for(int i=1;i<n;i<<=1)
        {
            int t=qpow(3,(P-1)/(i*2));
            if(u==-1) t=inv(t);
            for(int j=0;j<n;j+=i*2)
            {
                ll w=1;
                for(int k=j;k<i+j;++k)
                {
                    ll q=w*a[k+i]%P;
                    a[k+i]=(a[k]-q)%P;
                    a[k]=(a[k]+q)%P;
                    w=w*t%P;
                }
            }
        }
        return *this;
    }
    friend poly operator*(poly a,poly b)
    {
        int p=1;
        while(p<=a.n+b.n) p<<=1;
        a.NTT(p,1);
        b.NTT(p,1);
        poly c((len)p);
        for(int i=0;i<=p;++i) c[i]=a[i]*b[i]%P;
        c.NTT(p,-1).resize(a.n+b.n);
        ll w=inv(p);
        for(int i=0;i<=c.n;++i) c[i]=c[i]*w%P;
        return c;
    }
}f[N],g[N];
ll lag(const poly &x,ll k)
{
    if(k>=0&&k<=x.n) return x[k];
    ll s=0,w=1;
    for(int i=0;i<=x.n;++i) w=w*(k-i)%P;
    ll z[2]={inv(1),inv(-1)};
    for(int i=0;i<=x.n;++i)
    {
        ll w1=w*inv(k-i)%P,w2=ivjc[i]*ivjc[x.n-i]%P*z[(x.n-i)&1]%P;
        s=(s+x[i]*w1%P*w2%P)%P;
    }
    return s;
}
poly mov(const poly &x,int m)
{
    int p=0;
    if(m<=x.n)
    {
        p=x.n-m+1;
        m=x.n+1;
    }
    poly a((len)x.n),b=((len)(x.n*2));
    ll z[2]={inv(1),inv(-1)};
    for(int i=0;i<=x.n;++i)
    {
        a[i]=x[i]*z[(x.n-i)&1]%P*ivjc[i]%P*ivjc[x.n-i]%P;
    }
    for(int i=0;i<=x.n*2;++i) b[i]=ivm[x.n-i+(::m-m)];
    a=a*b;
    ll w=1;
    for(int i=m-x.n;i<=m;++i) w=w*i%P;
    for(int i=0;i<=x.n;++i)
    {
        a[i]=(a[x.n+i]*w%P+P)%P;
        w=w*ivm[x.n-i+(::m-m)]%P*(m+i+1)%P;
    }
    a.resize(x.n);
    for(int i=x.n;i>=0;--i)
    {
        if(i>=p) a[i]=a[i-p];
        else a[i]=x[x.n+i-p+1];
    }
    return a;
}
void dfs(int x,int fa)
{
    d[x]=1;
    f[x].resize(n+2);
    for(int i=0;i<=min(f[x].n,m-1);++i) f[x][i]=1;
    ll w=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x);
        poly p((len)(n+2));
        ll z=0;
        for(int j=0;j<=p.n;++j)
        {
            z=(z+f[i][j])%P;
            p[j]=f[x][j]*z%P;
            if(j>0) p[j]=(p[j]+p[j-1])%P;
        }
        w=(lag(p,m-1)+w*pw[d[i]]%P)%P;
        f[x]=(f[x]*g[i]).resize(n+2);
        d[x]+=d[i];
    }
    g[x]=mov(f[x],m-f[x].n);
    for(int i=0;i<=g[x].n/2;++i) swap(g[x][i],g[x][g[x].n-i]);
    g[x][0]=w;
}
int main()
{
    scanf("%d%d",&n,&m);
    jc[0]=1;
    for(int i=1;i<=n*3;++i) jc[i]=jc[i-1]*i%P;
    ivjc[n*3]=inv(jc[n*3]);
    for(int i=n*3;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    pw[0]=1;
    for(int i=1;i<=n*3;++i) pw[i]=pw[i-1]*m%P;
    for(int i=0;i<=n*3;++i) iv[i]=inv(i);
    for(int i=0;i<=n*3;++i) ivm[i]=inv(m-i);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs(1,0);
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        poly p((len)(n+2));
        for(int j=0;j<=p.n;++j)
        {
            p[j]=g[i][j]*j%P;
            if(j>0) p[j]=(p[j]+p[j-1])%P;
        }
        s=(s+lag(p,m)*pw[n-d[i]]%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}