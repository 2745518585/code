#include<cstdio>
#include<algorithm>
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
const int N=3000001;
const ll P=998244353;
int n,m;
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
    return (x%P+P)%P;
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
    poly(const poly &p)
    {
        if(this!=&p)
        {
            delete[] a,a=NULL;
            n=p.n;
            a=new ll[n+1];
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
            a=new ll[n+1];
            for(int i=0;i<=n;++i) a[i]=p[i];
        }
        return *this;
    }
    ll &operator[](size_t x) {return a[x];}
    const ll &operator[](size_t x) const {return a[x];}
    void print()
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
        static int d[N];
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
                    a[k+i]=a[k]-q;
                    if(a[k+i]<0) a[k+i]+=P;
                    a[k]=a[k]+q;
                    if(a[k]>=P) a[k]-=P;
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
    poly getinv(int n)
    {
        if(n==0) return poly(inv(a[0])).resize(n);
        poly x=getinv(n/2),y=*this;
        y.resize(n);
        int p=1;
        while(p<=n*2) p<<=1;
        x.NTT(p,1);
        y.NTT(p,1);
        for(int i=0;i<=p;++i)
        {
            x.a[i]=(2-y[i]*x[i]%P+P)*x[i]%P;
        }
        x.NTT(p,-1);
        x.resize(n);
        for(int i=0;i<=n;++i) x.a[i]=x[i]*inv(p)%P;
        return x;
    }
    poly getinv()
    {
        return getinv(n);
    }
};
poly check(const poly &a,const poly &b,poly rb)
{
    if(a.n<b.n) return a;
    poly ra=a;
    for(int i=0;i<=a.n/2;++i) swap(ra[i],ra[a.n-i]);
    poly w=(ra.resize(a.n-b.n)*rb.resize(a.n-b.n)).resize(a.n-b.n);
    for(int i=0;i<=w.n/2;++i) swap(w[i],w[w.n-i]);
    return (a-b*w.resize(b.n-1)).resize(b.n-1);
}
poly qpow(const poly &a,ll b,const poly &P)
{
    poly rP=P;
    for(int i=0;i<=P.n/2;++i) swap(rP[i],rP[P.n-i]);
    rP=rP.getinv();
    poly x=1,y=a;
    while(b)
    {
        if(b&1) x=check(x*y,P,rP);
        y=check(y*y,P,rP);
        b>>=1;
    }
    return x;
}
int main()
{
    scanf("%d%d",&n,&m);
    poly a((len)(m-1)),b((len)m);
    for(int i=m-1;i>=0;--i) scanf("%lld",&b[i]);
    for(int i=0;i<=m-1;++i) scanf("%lld",&a[i]);
    b[m]=-1;
    poly p=qpow({0,1},n,b);
    ll s=0;
    for(int i=0;i<=m-1;++i)
    {
        s=(s+a[i]*p[i]%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}