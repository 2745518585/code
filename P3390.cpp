#include<cstdio>
using namespace std;
const int p=1e9+7;
int n;
long long k,a[101][101],b[101][101],c[101][101];
void ab()
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            c[i][j]=a[i][j];
            a[i][j]=0;
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=1;k<=n;++k)
            {
                a[i][j]=(a[i][j]+(b[i][k]*c[k][j])%p)%p;
            }
        }
    }
}
void bb()
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            c[i][j]=b[i][j];
            b[i][j]=0;
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=1;k<=n;++k)
            {
                b[i][j]=(b[i][j]+(c[i][k]*c[k][j])%p)%p;
            }
        }
    }
}
void abc(long long x)
{
    while(x!=0)
    {
        if(x%2==1) ab();
        bb();
        x/=2;
    }
}
int main()
{
    scanf("%d%lld",&n,&k);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%lld",&b[i][j]);
        }
    }
    for(int i=1;i<=n;++i) a[i][i]=1;
    abc(k);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            printf("%lld ",a[i][j]%p);
        }
        printf("\n");
    }
    return 0;
}