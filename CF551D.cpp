#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3;
ll n,k,l,P;
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
ll qpow2(ll a,ll b)
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
    scanf("%lld%lld%lld%lld",&n,&k,&l,&P);
    matrix a,b;
    a.size(1,2),b.size(2,2);
    a.a[1][1]=1,a.a[1][2]=0;
    b.a[1][1]=1,b.a[1][2]=1,b.a[2][1]=1,b.a[2][2]=0;
    a=a*qpow(b,n);
    ll s=1,x=(a.a[1][1]+a.a[1][2])%P,y=(qpow2(2,n)-x+P)%P;
    if(l!=64&&(k>>l)!=0)
    {
        printf("0");
        return 0;
    }
    for(int i=0;i<=l-1;++i)
    {
        if((k&(1ll<<i))==0) s=s*x%P;
        else s=s*y%P;
    }
    printf("%lld",s%P);
    return 0;
}