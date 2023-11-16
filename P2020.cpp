#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
ll n,k,P,b1[N],b2[N],c1[N],c2[N],d[N];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%k+k)%k;
    ll x,y;
    exgcd(a,k,x,y);
    return (x%k+k)%k;
}
struct matrix
{
    int m,n;
    ll a[3][3];
    matrix(){}
    matrix(int _m,int _n,int x)
    {
        m=_m,n=_n;
        if(x==0) for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=0;
        if(x==1) for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=i==j;
    }
    matrix(initializer_list<initializer_list<ll>> _a)
    {
        m=0;
        for(auto i:_a) {n=0;for(auto j:i) a[m][n++]=j; ++m;}
    }
    ll *operator[](size_t x) {return a[x];}
    friend matrix operator*(matrix a,matrix b)
    {
        matrix c(a.m,b.n,0);
        for(int i=0;i<c.m;++i)
        {
            for(int j=0;j<c.n;++j)
            {
                for(int k=0;k<a.n;++k)
                {
                    c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%P)%P;
                }
            }
        }
        return c;
    }
    void print()
    {
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<n;++j)
            {
                printf("%d ",a[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
};
matrix qpow(matrix a,ll b)
{
    matrix x(a.m,a.n,1),y=a;
    while(b)
    {
        if(b&1) x=x*y;
        y=y*y;
        b>>=1;
    }
    return x;
}
int main()
{
    scanf("%lld%lld%lld",&n,&k,&P);
    ll x1=1,x2=1;
    for(ll i=0;i<=k-1;++i) d[i]=gcd(i,k);
    for(ll i=3;i<=k*6;++i)
    {
        ll x3=(x1+x2)%k;
        x1=x2,x2=x3;
        if(d[x2]==1)
        {
            ll z=inv(x2);
            if(b1[z]==0) b1[z]=i,b2[z]=x1;
        }
    }
    x1=1;
    ll q1=0,q2=0,t1=0,t2=0;
    matrix p1({{0,1,0},{1,1,0},{0,0,1}}),p2({{0,1,0},{1,1,0},{0,1,1}}),p({{1,0,-1}});
    while(true)
    {
        if(c1[x1]!=0)
        {
            t1=q2-c2[x1];
            t2=q1-c1[x1];
            break;
        }
        if(b1[x1]==0)
        {
            t1=1;
            t2=0;
            break;
        }
        if(q2+b1[x1]>n)
        {
            t1=1e18;
            t2=0;
            break;
        }
        c1[x1]=q1;
        c2[x1]=q2;
        ++q1;
        q2+=b1[x1];
        p=p*qpow(p1,b1[x1]-1)*p2;
        x1=x1*b2[x1]%k;
    }
    matrix p0(3,3,1);
    if(t2==0) p0=p0*qpow(p1,t1);
    else
    {
        ll z=x1;
        while(true)
        {
            p0=p0*qpow(p1,b1[z]-1)*p2;
            z=z*b2[z]%k;
            if(z==x1) break;
        }
    }
    p=p*qpow(p0,(n-q2)/t1);
    q2+=(n-q2)/t1*t1;
    while(true)
    {
        if(q2+b1[x1]>=n) break;
        q2+=b1[x1];
        p=p*qpow(p1,b1[x1]-1)*p2;
        x1=x1*b2[x1]%k;
    }
    p=p*qpow(p1,n-q2);
    printf("%lld",(p[0][1]%P+P)%P);
    return 0;
}