#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3000001;
const ll P=998244353;
int n,m;
ll jc[N];
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
    poly(const poly& p)
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
};
int main()
{
    scanf("%d%d",&n,&m);
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    poly a((len)n),b=((len)(n*2));
    for(int i=0;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        a[i]=a[i]*inv(((n-i)&1?-1:1)*jc[i]%P*jc[n-i]%P)%P;
    }
    for(int i=0;i<=n*2;++i) b[i]=inv(m-n+i);
    a=a*b;
    ll w=1;
    for(int i=m-n;i<=m;++i) w=w*i%P;
    for(int i=0;i<=n;++i)
    {
        printf("%lld ",(a[n+i]*w%P+P)%P);
        w=w*inv(m-n+i)%P*(m+i+1)%P;
    }
    return 0;
}