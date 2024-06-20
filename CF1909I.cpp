// LUOGU_RID: 160735486
#pragma GCC optimize("Ofast","inline")
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=998244353,P2=1e9+7;
int n;
ll p,jc[N<<1],ivjc[N<<1],f1[N][N],f2[N][N],g[N<<1];
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
ll qpow(ll x,ll y,ll P=::P)
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
        for(int i=0;i<=n;++i) printf("%lld ",a[i]);
        printf("\n");
    }
    friend poly operator+(const poly &a,const poly &b)
    {
        poly c;
        c.resize(max(a.n,b.n));
        for(int i=0;i<=c.n;++i) c[i]=(a[i]+b[i])%P;
        return c;
    }
    friend poly operator-(const poly &a,const poly &b)
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
void solve(int n,int m,ll *f)
{
    poly p1,p2;
    p1.resize(n),p2.resize(m);
    for(int i=0;i<=n;++i)
    {
        p1[i]=f[i]*jc[n-i-1]%P*jc[m+i+1]%P;
    }
    for(int i=0;i<=m;++i)
    {
        p2[i]=ivjc[i]*ivjc[m-i]%P;
    }
    poly p=p1*p2;
    ll s=0;
    for(int i=0;i<=n+m;++i)
    {
        g[i+m]=(g[i+m]+p[i]*jc[m]%P*ivjc[n-i-1]%P*ivjc[i+1]%P+P)%P;
    }
}
int main()
{
    scanf("%d%lld",&n,&p);
    f1[0][0]=f2[0][0]=1;
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<=n;++j)
        {
            f1[i][j]%=P,f2[i][j]%=P;
            if(f1[i][j])
            {
                if(i%2==0)
                {
                    f1[i+1][j+1]+=f1[i][j]*(j+2)%P;
                    f1[i+1][j+2]+=f1[i][j]*(i-j-1)%P;
                }
                else
                {
                    if(j>0) f1[i+1][j-1]+=f1[i][j]*j%P;
                    f1[i+1][j]+=f1[i][j]*(i-j+1)%P;
                }
            }
            if(f2[i][j])
            {
                if(i%2==0)
                {
                    if(j>0) f2[i+1][j-1]+=f2[i][j]*j%P;
                    f2[i+1][j]+=f2[i][j]*(i-j+1)%P;
                }
                else
                {
                    f2[i+1][j+1]+=f2[i][j]*(j+2)%P;
                    f2[i+1][j+2]+=f2[i][j]*(i-j-1)%P;
                }
            }
        }
    }
    jc[0]=1;
    for(int i=1;i<=n*2;++i) jc[i]=jc[i-1]*i%P;
    ivjc[n*2]=inv(jc[n*2]);
    for(int i=n*2;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    ll s=0;
    for(int i=3;i<=n+1;++i)
    {
        for(int j=0;j<=n-1;++j) g[j]=0;
        if(i%2==0)
        {
            solve(i-2,n-i+2,f1[i-2]);
        }
        else
        {
            solve(i-2,n-i+2,f2[i-2]);
        }
        for(int j=0;j<=n-1;++j)
        {
            s=(s+g[j]*qpow(p,(ll)i*n+j,P2)%P2)%P2;
        }
    }
    printf("%lld",(s%P2+P2)%P2);
    return 0;
}