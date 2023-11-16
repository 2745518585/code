#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=21;
ll m,P;
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
                    c.a[i][j]=(c.a[i][j]+(__int128_t)a.a[i][k]*b.a[k][j]%P)%P;
                }
            }
        }
        return c;
    }
    void size(int x,int y) {m=x,n=y;}
    void init0()
    {
        for(int i=1;i<=m;++i) for(int j=1;j<=n;++j) a[i][j]=0;
    }
    void init1()
    {
        for(int i=1;i<=m;++i) for(int j=1;j<=n;++j) a[i][j]=(i==j);
    }
};
matrix qpow(matrix a,ll b)
{
    matrix x=a,y=a;
    x.init1();
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
        if(b&1) x=(__int128_t)x*y%P;
        y=(__int128_t)y*y%P;
        b>>=1;
    }
    return x;
}
int main()
{
    scanf("%lld%lld",&m,&P);
    ++m;
    matrix a,b;
    a.size(1,2),b.size(2,2);
    a.init0(),b.init0();
    a.a[1][1]=a.a[1][2]=1;
    b.a[1][1]=b.a[1][2]=b.a[2][1]=1;
    a=a*qpow(b,m-1);
    printf("%lld",(qpow2(a.a[1][1]+a.a[1][2]-m-1,m)%P+P)%P);
    return 0;
}