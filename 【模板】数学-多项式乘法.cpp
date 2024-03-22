#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
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
    poly(int x)
    {
        resize(0);
        a[0]=x;
    }
    ll &operator[](size_t x) {return a[x];}
    void print()
    {
        for(int i=0;i<=n;++i) printf("%lld ",a[i]);
        printf("\n");
    }
    friend poly operator+(poly a,poly b)
    {
        poly c;
        c.resize(max(a.n,b.n));
        for(int i=0;i<=c.n;++i) c[i]=(a[i]+b[i])%P;
        return c;
    }
    friend poly operator-(poly a,poly b)
    {
        poly c;
        c.resize(max(a.n,b.n));
        for(int i=0;i<=c.n;++i) c[i]=(a[i]-b[i]+P)%P;
        return c;
    }
    friend poly NTT(int n,poly a,int u)
    {
        a.resize(n);
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
        return a;
    }
    friend poly operator*(poly a,poly b)
    {
        int p=1;
        while(p<=a.n+b.n) p<<=1;
        a=NTT(p,a,1);
        b=NTT(p,b,1);
        poly c;
        c.resize(p);
        for(int i=0;i<=p;++i) c[i]=a[i]*b[i]%P;
        c=NTT(p,c,-1);
        c.resize(a.n+b.n);
        for(int i=0;i<=c.n;++i) c[i]=c[i]*inv(p)%P;
        return c;
    }
};
int main()
{
    poly a,b;
    scanf("%d%d",&m,&n);
    a.resize(m),b.resize(n);
    for(int i=0;i<=m;++i) scanf("%lld",&a.a[i]);
    for(int i=0;i<=n;++i) scanf("%lld",&b.a[i]);
    poly c=a*b;
    for(int i=0;i<=m+n;++i)
    {
        printf("%lld ",(c[i]%P+P)%P);
    }
    return 0;
}