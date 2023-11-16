#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001;
int n,a[N],b[N],f[N][N],g[N][N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        g[i][i]=i;
    }
    for(int i=1;i<=n;++i)
    {
        b[i]=b[i-1]+a[i];
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=i+1;j<=n;++j)
        {
            f[i][j]=1e9;
            for(int k=g[i][j-1];k<=g[i+1][j];++k)
            {
                if(f[i][k]+f[k+1][j]+b[j]-b[i-1]<f[i][j])
                {
                    f[i][j]=f[i][k]+f[k+1][j]+b[j]-b[i-1];
                    g[i][j]=k;
                }
            }
        }
    }
    printf("%d",f[1][n]);
    return 0;
}