#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
const int N=101;
int n,m,k,tot;
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
                for(int j=1;j<=n;++j) a[i][j]=0;
            }
        }
        else if(x==1)
        {
            for(int i=1;i<=m;++i)
            {
                for(int j=1;j<=n;++j) a[i][j]=(i==j);
            }
        }
    }
}a,b,c;
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
    scanf("%d%d%d%d",&n,&m,&k,&tot);
    a.m=1,a.n=tot,b.m=b.n=c.m=c.n=tot;
    a.a[1][1]=1;
    for(int i=0;i<=tot-1;++i)
    {
        b.a[i+1][(i*10)%tot+1]=1;
    }
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        for(int j=0;j<=tot-1;++j)
        {
            ++c.a[j+1][(j+x)%tot+1];
        }
    }
    a=a*qpow(b*c,m);
    printf("%lld",a.a[1][k+1]);
    return 0;
}