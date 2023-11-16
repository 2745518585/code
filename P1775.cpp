#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[1001],b[1001],f[1001][1001];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=b[i-1]+a[i];
        f[i][i]=0;
    }
    for(int i=1;i<=n-1;++i)
    {
        for(int j=1;j<=n;++j)
        {
            f[j][i+j]=1e9;
            for(int k=j;k<i+j;++k)
            {
                f[j][i+j]=min(f[j][i+j],f[j][k]+f[k+1][i+j]+b[i+j]-b[j-1]);
            }
        }
    }
    printf("%d",f[1][n]);
    return 0;
}