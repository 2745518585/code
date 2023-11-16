#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=801,M=4;
int n,m;
ll f[N][N][M];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        ++f[x][y][1];
        ++f[y][x][1];
    }
    for(int r=2;r<=3;++r)
    {
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(f[i][j][r-1]==0) continue;
                for(int k=1;k<=n;++k) f[i][k][r]+=f[i][j][r-1]*f[j][k][1];
            }
        }
    }
    ll s=0,w=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            s+=f[i][j][2]*f[j][i][3];
            w+=f[i][j][1]*f[i][j][1]*f[j][j][3];
            w-=f[i][j][1]*f[i][j][1]*f[i][j][1]*f[i][j][2];
        }
    }
    printf("%lld",(s-w*5)/10);
    return 0;
}