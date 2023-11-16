#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2001,M=1000001;
int n,m,f[N][N],d[M];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) f[i][i]=m+1;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        f[x][y]=max(f[x][y],i);
    }
    for(int k=n;k>=1;--k)
    {
        for(int i=1;i<=n;++i)
        {
            int j=1;
            for(;j+3<=n;j+=4)
            {
                f[i][j]=max(f[i][j],min(f[i][k],f[k][j]));
                f[i][j+1]=max(f[i][j+1],min(f[i][k],f[k][j+1]));
                f[i][j+2]=max(f[i][j+2],min(f[i][k],f[k][j+2]));
                f[i][j+3]=max(f[i][j+3],min(f[i][k],f[k][j+3]));
            }
            for(;j<=n;++j)
            {
                f[i][j]=max(f[i][j],min(f[i][k],f[k][j]));
            }
        }
        for(int i=k;i<=n;++i)
        {
            ++d[min(f[i][k],f[k][i])];
        }
    }
    for(int i=m;i>=1;--i) d[i]+=d[i+1];
    for(int i=1;i<=m+1;++i)
    {
        printf("%d ",d[i]);
    }
    return 0;
}