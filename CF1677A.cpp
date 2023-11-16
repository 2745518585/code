#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5101;
int n,a[N],g1[N][N],g2[N][N];
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
        for(int i=1;i<=n;++i)
        {
            g1[i][0]=0;
            for(int j=1;j<=n;++j)
            {
                g1[i][j]=g1[i][j-1]+(a[j]<=i);
            }
        }
        for(int i=1;i<=n;++i)
        {
            g2[i][n+1]=0;
            for(int j=n;j>=1;--j)
            {
                g2[i][j]=g2[i][j+1]+(a[j]<=i);
            }
        }
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            for(int j=i+1;j<=n;++j)
            {
                s+=(ll)g1[a[j]-1][i-1]*g2[a[i]-1][j+1];
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}