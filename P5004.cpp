#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
const int N=21;
ll m,n;
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
int main()
{
    scanf("%lld%lld",&m,&n);
    matrix a,b;
    a.size(1,n+1),b.size(n+1,n+1);
    a.init0(),b.init0();
    for(int i=1;i<=n+1;++i) a.a[1][i]=1;
    b.a[1][1]=b.a[1][n+1]=1;
    for(int i=1;i<=n;++i) b.a[i+1][i]=1;
    a=a*qpow(b,m-n);
    ll s=0;
    for(int i=1;i<=n+1;++i) s=(s+a.a[1][i])%P;
    printf("%lld",s);
    return 0;
}