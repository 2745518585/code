#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=300001;
const ll P=998244353;
int n;
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
    poly copy()
    {
        poly x;
        x.resize(n);
        for(int i=0;i<=n;++i) x.a[i]=a[i];
        return x;
    }
    poly(){}
    poly(int x)
    {
        resize(0);
        a[0]=x;
    }
    ll operator[](size_t x)
    {
        if(x<=n) return a[x];
        return 0;
    }
    void print()
    {
        for(int i=0;i<=n;++i) printf("%lld ",(a[i]%P+P)%P);
        printf("\n");
    }
    friend poly operator+(poly a,poly b)
    {
        poly c;
        c.resize(max(a.n,b.n));
        for(int i=0;i<=c.n;++i) c.a[i]=(a[i]+b[i])%P;
        return c;
    }
    friend poly operator-(poly a,poly b)
    {
        poly c;
        c.resize(max(a.n,b.n));
        for(int i=0;i<=c.n;++i) c.a[i]=(a[i]-b[i]+P)%P;
        return c;
    }
    void NTT(int n,int u)
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
    }
    friend poly operator*(poly a,poly b)
    {
        a=a.copy();
        b=b.copy();
        int p=1,t=a.n+b.n;
        while(p<=t) p<<=1;
        a.NTT(p,1);
        b.NTT(p,1);
        poly c;
        c.resize(p);
        for(int i=0;i<=p;++i) c.a[i]=a[i]*b[i]%P;
        c.NTT(p,-1);
        c.resize(t);
        for(int i=0;i<=c.n;++i) c.a[i]=c[i]*inv(p)%P;
        return c;
    }
    poly getinv(int n)
    {
        if(n==0) return poly(inv(a[0])).resize(n);
        poly x=getinv(n/2),y=((*this).copy()).resize(n);
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
}a;
int main()
{
    scanf("%d",&n);
    a.resize(n-1);
    for(int i=0;i<=a.n;++i)
    {
        scanf("%lld",&a.a[i]);
    }
    poly b=a.getinv();
    b.print();
    return 0;
}