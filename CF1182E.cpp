#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
const int N=11;
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
                    c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%(P-1))%(P-1);
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
ll qpow2(ll a,ll b)
{
    ll x=1,y=a;
    while(b!=0)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
ll n,f1,f2,f3,t,s=1;
int main()
{
    scanf("%lld%lld%lld%lld%lld",&n,&f1,&f2,&f3,&t);
    matrix a,b;
    a.m=1,a.n=3,b.m=3,b.n=3;
    b.a[1][1]=0,b.a[1][2]=0,b.a[1][3]=1;
    b.a[2][1]=1,b.a[2][2]=0,b.a[2][3]=1;
    b.a[3][1]=0,b.a[3][2]=1,b.a[3][3]=1;
    a.a[1][1]=1,a.a[1][2]=0,a.a[1][3]=0;
    a=a*qpow(b,n-1);
    s=s*qpow2(f1,a.a[1][1])%P;
    a.a[1][1]=0,a.a[1][2]=1,a.a[1][3]=0;
    a=a*qpow(b,n-1);
    s=s*qpow2(f2,a.a[1][1])%P;
    a.a[1][1]=0,a.a[1][2]=0,a.a[1][3]=1;
    a=a*qpow(b,n-1);
    s=s*qpow2(f3,a.a[1][1])%P;
    a.m=1,a.n=5,b.m=5,b.n=5;
    b.a[1][1]=0,b.a[1][2]=0,b.a[1][3]=1,b.a[1][4]=0,b.a[1][5]=0;
    b.a[2][1]=1,b.a[2][2]=0,b.a[2][3]=1,b.a[2][4]=0,b.a[2][5]=0;
    b.a[3][1]=0,b.a[3][2]=1,b.a[3][3]=1,b.a[3][4]=0,b.a[3][5]=0;
    b.a[4][1]=0,b.a[4][2]=0,b.a[4][3]=2,b.a[4][4]=1,b.a[4][5]=0;
    b.a[5][1]=0,b.a[5][2]=0,b.a[5][3]=0,b.a[5][4]=1,b.a[5][5]=1;
    a.a[1][1]=0,a.a[1][2]=0,a.a[1][3]=0,a.a[1][4]=1,a.a[1][5]=1;
    a=a*qpow(b,n-1);
    s=s*qpow2(t,a.a[1][1])%P;
    printf("%lld",s);
    return 0;
}