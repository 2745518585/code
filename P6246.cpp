#include<cstdio>
#include<algorithm>
using namespace std;
const int N=500001,M=1000001;
int n,m,a[N],b[N],f[N][M],g[N][M],h[N][N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=b[i-1]+a[i];
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=i;j<=n;++j)
        {
            int k=i+j>>1;
            h[i][j]=(k-i+1)*a[k]-(b[k]-b[i-1])+(b[j]-b[k])-(j-k)*a[k];
        }
    }
    for(int i=0;i<=m;++i)
    {
        for(int j=0;j<=n;++j)
        {
            f[i][j]=1e9;
        }
    }
    f[0][0]=0;
    for(int i=1;i<=m;++i)
    {
        g[i][n+1]=n;
        for(int j=n;j>=1;--j)
        {
            for(int k=g[i-1][j];k<=g[i][j+1];++k)
            {
                if(f[i-1][k]+h[k+1][j]<f[i][j])
                {
                    f[i][j]=f[i-1][k]+h[k+1][j];
                    g[i][j]=k;
                }
            }
        }
    }
    printf("%d",f[m][n]);
    return 0;
}