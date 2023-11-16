#include<cstdio>
#include<algorithm>
using namespace std;
const int N=61;
int n,f[N][N][N][N];
char a[N][N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",a[i]+1);
        for(int j=1;j<=n;++j)
        {
            if(a[i][j]=='#') f[i][i][j][j]=1;
            else f[i][i][j][j]=0;
        }
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=i;j<=n;++j)
        {
            for(int k=n;k>=1;--k)
            {
                for(int l=k;l<=n;++l)
                {
                    if(i==j&&k==l) continue;
                    f[i][j][k][l]=max(j-i+1,l-k+1);
                    for(int o=i;o<=j-1;++o)
                    {
                        f[i][j][k][l]=min(f[i][j][k][l],f[i][o][k][l]+f[o+1][j][k][l]);
                    }
                    for(int o=k;o<=l-1;++o)
                    {
                        f[i][j][k][l]=min(f[i][j][k][l],f[i][j][k][o]+f[i][j][o+1][l]);
                    }
                }
            }
        }
    }
    printf("%d",f[1][n][1][n]);
    return 0;
}