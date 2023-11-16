#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001;
int n,m,a[N],b[N],f[N][N];
int sum(int x,int y)
{
    return abs(a[x]-a[y])+abs(b[x]-b[y]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i],&b[i]);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=m;++j)
        {
            f[i][j]=1e9;
        }
    }
    f[1][0]=0;
    for(int i=1;i<=n-1;++i)
    {
        for(int j=0;j<=m;++j)
        {
            for(int k=0;k<=min(n-i-1,m-j);++k)
            {
                f[i+k+1][j+k]=min(f[i+k+1][j+k],f[i][j]+sum(i,i+k+1));
            }
        }
    }
    printf("%d",f[n][m]);
    return 0;
}