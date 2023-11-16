#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001,M=10001;
int n,m;
double f[M][N];
int main()
{
    scanf("%d%d",&n,&m);
    f[0][0]=1;
    for(int i=1;i<=10000;++i)
    {
        for(int j=1;j<=n;++j)
        {
            f[i][j]=f[i-1][j-1]*(n-j+1)/n+f[i-1][j]*j/n;
        }
    }
    for(int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        for(int j=1;j<=10000;++j)
        {
            if(f[j][n]*2000>=x)
            {
                printf("%d\n",j);
                break;
            }
        }
    }
    return 0;
}