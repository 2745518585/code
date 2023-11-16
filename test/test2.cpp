#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=51;
int n,a[N];
ll b[N],f[N][N][N][N],g[N][N][N][N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        sort(a+1,a+n+1);
        for(int i=1;i<=n;++i) b[i]=b[i-1]+a[i];
        memset(f,0x3f,sizeof(f));
        memset(g,0x3f,sizeof(g));
        for(int i=1;i<=n;++i) f[i][i][0][0]=g[i][i][0][0]=0;
        for(int i=n;i>=1;--i)
        {
            for(int j=i;j<=n;++j)
            {
                for(int o=j-i;o>=1;--o)
                {
                    for(int p=o;p<=j-i;++p)
                    {
                        for(int k=i;k<=j-1;++k)
                        {
                            for(int q=o;q<=p;++q)
                            {
                                if(g[i][k][q-1][p-1]+f[k+1][j][o-1][q-1]+((1<<(q-1))-1)+(b[j]-b[i-1])<=1e18) printf("%d %d %d %d: %d %d %lld %lld %lld\n",i,j,o,p,k,q,g[i][k][q-1][p-1],f[k+1][j][o-1][q-1],g[i][k][q-1][p-1]+f[k+1][j][o-1][q-1]+((1<<(q-1))-1)+(b[j]-b[i-1]));
                                f[i][j][o][p]=min(f[i][j][o][p],g[i][k][q-1][p-1]+f[k+1][j][o-1][q-1]+((1<<(q-1))-1)+(b[j]-b[i-1]));
                            }
                        }
                        g[i][j][o][p]=min(f[i][j][o][p],g[i][j][o+1][p]);
                    }
                }
                for(int p=0;p<=j-i;++p) g[i][j][0][p]=min(g[i][j][0][p],g[i][j][1][p]);
            }
        }
        ll s=1e18;
        for(int i=0;i<=n-1;++i)
        {
            for(int j=i;j<=n-1;++j) s=min(s,f[1][n][i][j]);
        }
        printf("%lld\n",s);
    }
    return 0;
}