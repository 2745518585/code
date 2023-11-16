#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=501,M=51;
int m,n,k,tot=1,t[N],a1[N][N],a2[N][N],f[N][N][M];
int main()
{
    scanf("%d%d%d",&m,&n,&k);
    if(k%2==1)
    {
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                printf("-1 ");
            }
            printf("\n");
        }
        return 0;
    }
    k/=2;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int l=1;l<=k;++l)
            {
                f[i][j][l]=1e9;
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=2;j<=n;++j)
        {
            scanf("%d",&a1[i][j]);
        }
    }
    for(int i=2;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a2[i][j]);
        }
    }
    for(int l=1;l<=k;++l)
    {
        for(int i=1;i<=m;++i)
        {
            for(int j=2;j<=n;++j)
            {
                f[i][j-1][l]=min(f[i][j-1][l],f[i][j][l-1]+a1[i][j]);
                f[i][j][l]=min(f[i][j][l],f[i][j-1][l-1]+a1[i][j]);
            }
        }
        for(int i=2;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                f[i-1][j][l]=min(f[i-1][j][l],f[i][j][l-1]+a2[i][j]);
                f[i][j][l]=min(f[i][j][l],f[i-1][j][l-1]+a2[i][j]);
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            printf("%d ",f[i][j][k]*2);
        }
        printf("\n");
    }
    return 0;
}