#include<cstdio>
#include<algorithm>
using namespace std;
const int N=61;
int n,q,k1,k2,a[N],b[N],f[N][N][N][N],g[N][N];
int main()
{
    scanf("%d%d%d",&n,&k1,&k2);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    q=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            g[i][j]=1e9;
            for(int k=1;k<=q;++k)
            {
                for(int l=1;l<=q;++l) f[i][j][k][l]=1e9;
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(b+1,b+q+1,a[i])-b;
        for(int j=1;j<=a[i];++j)
        {
            for(int k=a[i];k<=q;++k) f[i][i][j][k]=0;
        }
        g[i][i]=k1;
    }
    for(int l=2;l<=n;++l)
    {
        for(int i=1,j=i+l-1;j<=n;++i,++j)
        {
            for(int o=1;o<=q;++o)
            {
                for(int p=o;p<=q;++p)
                {
                    for(int k=i;k<=j-1;++k)
                    {
                        f[i][j][o][p]=min(f[i][j][o][p],f[i][k][o][p]+g[k+1][j]);
                        f[i][j][o][p]=min(f[i][j][o][p],g[i][k]+f[k+1][j][o][p]);
                        f[i][j][o][p]=min(f[i][j][o][p],f[i][k][o][p]+f[k+1][j][o][p]);
                    }
                    g[i][j]=min(g[i][j],f[i][j][o][p]+k1+k2*(b[p]-b[o])*(b[p]-b[o]));
                }
            }
        }
    }
    printf("%d",g[1][n]);
    return 0;
}