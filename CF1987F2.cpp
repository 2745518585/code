#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2001;
int n,a[N],f[N][N],g[N];
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
        for(int i=0;i<=n+1;++i)
        {
            for(int j=0;j<=n+1;++j) f[i][j]=(i<=j?1e9:0);
        }
        for(int i=n;i>=1;--i)
        {
            if(a[i]>i||(i-a[i])%2) continue;
            for(int j=i+1;j<=n;j+=2)
            {
                for(int k=i+1;k<=j;k+=2)
                {
                    if(f[i+1][k-1]<=(i-a[i])/2)
                    {
                        f[i][j]=min(f[i][j],max(f[i+1][k-1],f[k+1][j]-(k-i+1)/2));
                    }
                }
                f[i][j]=max(f[i][j],(i-a[i])/2);
            }
        }
        for(int i=0;i<=n;++i) g[i]=0;
        for(int i=1;i<=n;++i)
        {
            g[i]=g[i-1];
            for(int j=i-1;j>=0;j-=2)
            {
                if(f[j][i]<=g[j-1]) g[i]=max(g[i],g[j-1]+(i-j+1)/2);
            }
        }
        printf("%lld\n",g[n]);
    }
    return 0;
}