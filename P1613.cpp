#include<cstdio>
#include<algorithm>
using namespace std;
const int N=61,K=32;
int n,m,g[N][N];
bool f[N][N][K];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
    	for(int j=1;j<=n;++j)
    	{
    		g[i][j]=1e9;
		}
	}
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        f[x][y][0]=true;
        g[x][y]=1;
    }
    for(int r=1;r<=K;++r)
    {
        for(int k=1;k<=n;++k)
        {
            for(int i=1;i<=n;++i)
            {
                for(int j=1;j<=n;++j)
                {
                    if(f[i][k][r-1]==true&&f[k][j][r-1]==true)
                    {
                        f[i][j][r]=true;
                        g[i][j]=1;
                    }
                }
            }
        }
    }
    for(int k=1;k<=n;++k)
    {
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
            }
        }
    }
    printf("%d",g[1][n]);
    return 0;
}
