#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=101;
const ll P=1e9+7;
ll n,k;
int m;
struct matrix
{
    int m,n;
    ll a[N][N];
    matrix(int m,int n,int x=0):m(m),n(n)
    {
        for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=(x==1&&i==j);
    }
    const ll *operator[](size_t x) const {return a[x];}
    ll *operator[](size_t x) {return a[x];}
    friend matrix operator*(const matrix &a,const matrix &b)
    {
        matrix c(a.m,b.n);
        for(int i=0;i<c.m;++i) for(int j=0;j<c.n;++j) for(int k=0;k<a.n;++k) c[i][j]=(c[i][j]+(ll)a[i][k]*b[k][j]%P)%P;
        return c;
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
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%d%lld",&n,&m,&k);
        matrix a(1,m),b(m,m);
        for(int i=0;i<=m-1;++i) a[0][i]=1;
        for(int i=0;i<=m-1;++i)
        {
            for(int j=0;j<=m-1;++j)
            {
                if(abs(i-j)<=k) b[i][j]=1;
                else b[i][j]=0;
            }
        }
        a=a*qpow(b,n-1);
        ll s=(m+k)*qpow(k*2+1,n-1)%P;
        for(int i=0;i<=m-1;++i) s=(s-a[0][i])%P;
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}