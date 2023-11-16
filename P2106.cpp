#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=1000000007;
const int N=15;
ll n;
ll p[N][N]={{},
{-1,1,1,1,0,0,0,0,0,0,0},
{-1,1,1,1,1,0,0,0,0,0,0},
{-1,1,1,1,1,1,0,0,0,0,0},
{-1,0,1,1,1,1,1,0,0,0,0},
{-1,0,0,1,1,1,1,1,0,0,0},
{-1,0,0,0,1,1,1,1,1,0,0},
{-1,0,0,0,0,1,1,1,1,1,0},
{-1,0,0,0,0,0,1,1,1,1,1},
{-1,0,0,0,0,0,0,1,1,1,1},
{-1,0,0,0,0,0,0,0,1,1,1}};
struct matrix
{
    int m,n;
    ll a[N][N];
    friend matrix operator *(matrix a,matrix b)
    {
        matrix c;
        c.m=a.m,c.n=b.n;
        for(int i=1;i<=c.n;++i)
        {
            for(int j=1;j<=c.n;++j)
            {
                c.a[i][j]=0;
                for(int k=1;k<=a.n;++k)
                {
                    c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%P)%P;
                }
            }
        }
        return c;
    }
    void init(int x)
    {
        if(x==0)
        {
            for(int i=1;i<=m;++i)
            {
                for(int j=1;j<=n;++j)
                {
                    a[i][j]=0;
                }
            }
        }
        else if(x==1)
        {
            for(int i=1;i<=m;++i)
            {
                for(int j=1;j<=n;++j)
                {
                    a[i][j]=(i==j);
                }
            }
        }
    }
};
matrix qpow(matrix a,ll b)
{
    matrix x=a,y=a;
    x.init(1);
    while(b!=0)
    {
        if(b&1) x=x*y;
        y=y*y;
        b>>=1;
    }
    return x;
}
int main()
{
    scanf("%lld",&n);
    if(n==1)
    {
        printf("10");
        return 0;
    }
    matrix a,b;
    a.m=1,a.n=10,b.m=10,b.n=10;
    for(int i=1;i<=10;++i) a.a[1][i]=1;
    a.a[1][1]=0;
    for(int i=1;i<=10;++i)
    {
        for(int j=1;j<=10;++j)
        {
            b.a[i][j]=p[i][j];
        }
    }
    a=a*qpow(b,n-1);
    ll s=0;
    for(int i=1;i<=10;++i)
    {
        s=(s+a.a[1][i])%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}