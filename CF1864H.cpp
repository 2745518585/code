#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=101,M=60;
const ll P=998244353;
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
struct matrix
{
    int m,n;
    ll a[N][N];
    matrix() {}
    matrix(int m,int n):m(m),n(n)
    {
        for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=0;
    }
    void init()
    {
        for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i][j]=(i==j);
    }
    ll *operator[](size_t x) {return a[x];}
    friend matrix operator*(matrix a,matrix b)
    {
        matrix c(a.m,b.n);
        for(int i=0;i<c.m;++i)
        {
            for(int j=0;j<c.n;++j)
            {
                for(int k=0;k<a.n;++k)
                {
                    c[i][j]=(c[i][j]+a[i][k]*b[k][j]%P)%P;
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
                printf("%lld ",a[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}a[N],b[N];
ll ivpow2[N];
matrix solve(ll n,matrix *a)
{
    matrix s=matrix(1,M+2);
    for(int i=0;i<=M;++i) s[0][i]=2;
    s[0][M+1]=-1;
    for(int i=M;i>=0;--i)
    {
        if(n&(1ll<<i)) s=s*a[i];
    }
    return s;
}
int main()
{
    ivpow2[0]=1;
    for(int i=1;i<=M+10;++i) ivpow2[i]=ivpow2[i-1]*inv(2)%P;
    matrix w(M+2,M+2);
    w.init();
    for(int i=0;i<=M;++i)
    {
        a[i]=matrix(M+2,M+2);
        for(int j=0;j<=i;++j)
        {
            for(int k=j;k<=i;++k)
            {
                a[i][k][j]=ivpow2[k-j+1];
                if(j==0) a[i][k][M+1]=(a[i][k][M+1]+ivpow2[k-j+1])%P;
            }
        }
        for(int j=i+1;j<=M;++j) a[i][j][j]=1;
        a[i][M+1][M+1]=1;
        a[i]=w*a[i];
        w=a[i]*w;
    }
    w.init();
    for(int i=0;i<=M;++i)
    {
        b[i]=matrix(M+2,M+2);
        for(int j=0;j<=i;++j)
        {
            for(int k=j;k<=i;++k)
            {
                b[i][k][j]=ivpow2[k-j+1];
                if(j==0) b[i][k][M+1]=(b[i][k][M+1]+ivpow2[k-j+2])%P;
            }
        }
        for(int j=i+1;j<=M;++j) b[i][j][j]=1;
        b[i][M+1][M+1]=1;
        b[i]=w*b[i];
        w=b[i]*w;
    }
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll n;
        scanf("%lld",&n);
        if(n==1)
        {
            printf("0\n");
            continue;
        }
        if(n==2)
        {
            printf("1\n");
            continue;
        }
        ll s=solve(n,a)[0][M+1],x=solve(n-1,b)[0][M+1],y=solve(n/2,b)[0][M+1];
        s=(s+x-y)%P;
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}