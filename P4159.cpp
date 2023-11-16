#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=2009;
const int N=101;
int n,m;
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
int sum(int x,int y)
{
    return (x-1)*9+y;
}
int main()
{
    scanf("%d%d",&n,&m);
    matrix a,b;
    a.size(1,sum(n,9)),b.size(sum(n,9),sum(n,9));
    a.init0(),b.init0();
    for(int i=1;i<=n;++i)
    {
        char z[N];
        scanf("%s",z+1);
        for(int j=1;j<=n;++j)
        {
            if(z[j]!='0') b.a[sum(i,1)][sum(j,z[j]-'0')]=1;
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=8;++j)
        {
            b.a[sum(i,j+1)][sum(i,j)]=1;
        }
    }
    a.a[1][1]=1;
    a=a*qpow(b,m);
    printf("%lld",a.a[1][sum(n,1)]);
    return 0;
}