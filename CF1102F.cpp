#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=17,M=10001;
int m,n,a[N][M],f[1<<N][N][N],g[N][N],g2[N][N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            g[i][j]=1e9;
            for(int k=1;k<=m;++k) g[i][j]=min(g[i][j],abs(a[i][k]-a[j][k]));
            g2[i][j]=1e9;
            for(int k=1;k<=m-1;++k) g2[i][j]=min(g2[i][j],abs(a[i][k]-a[j][k+1]));
        }
    }
    if(n==1)
    {
        printf("%d",g2[1][1]);
        return 0;
    }
    if(n==2)
    {
        printf("%d",max(min(g[1][2],g2[2][1]),min(g[2][1],g2[1][2])));
        return 0;
    }
    for(int i=1;i<=n;++i) f[1<<(i-1)][i][i]=1e9;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if((i&(1<<(j-1)))==0) continue;
            for(int k=1;k<=n;++k)
            {
                if((i&(1<<(k-1)))==0) continue;
                for(int l=1;l<=n;++l)
                {
                    if((i&(1<<(l-1)))!=0) continue;
                    if((i|(1<<(l-1)))!=(1<<n)-1) f[i|(1<<(l-1))][j][l]=max(f[i|(1<<(l-1))][j][l],min(f[i][j][k],g[k][l]));
                    else f[i|(1<<(l-1))][j][l]=max(f[i|(1<<(l-1))][j][l],min(f[i][j][k],min(g[k][l],g2[l][j])));
                }
            }
        }
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            s=max(s,f[(1<<n)-1][i][j]);
        }
    }
    printf("%d",s);
    return 0;
}