#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
const int N=1000001,M=121;
int n,m,p,b2[N];
struct matrix
{
    int m,n;
    ll a[M][M];
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
    scanf("%d%d%d",&n,&m,&p);
    matrix a,b,c;
    a.m=1,a.n=p,b.m=b.n=p,c.m=c.n=p;
    for(int i=1;i<=p;++i) a.a[1][i]=0;
    for(int i=1;i<=p;++i)
    {
        for(int j=1;j<=p;++j) b.a[i][j]=0;
    }
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++a.a[1][x%p+1];
    }
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        b2[i]=x;
        ++b.a[1][x%p+1];
    }
    for(int i=1;i<=p-1;++i)
    {
        for(int j=1;j<=p;++j)
        {
            b.a[i+1][j%p+1]+=b.a[i][j];
        }
    }
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++c.a[1][(x+b2[i])%p+1];
    }
    for(int i=1;i<=p-1;++i)
    {
        for(int j=1;j<=p;++j)
        {
            c.a[i+1][j%p+1]+=c.a[i][j];
        }
    }
    a=a*qpow(b,m-2)*c;
    printf("%lld",a.a[1][1]);
    return 0;
}