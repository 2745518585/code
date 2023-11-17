#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=5001;
int n;
ll a[N],d[N],b[N],f[N][N];
ll sum(int x)
{
    if(x==0) return 0;
    return (x&-x);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        sort(a+1,a+n+1);
        for(int i=1;i<=n;++i) b[i]=b[i-1]+a[i];
        for(int i=0;i<=n;++i) d[i]=sum(i-1);
        for(int i=0;i<=n;++i)
        {
            for(int j=0;j<=n;++j) f[i][j]=1e18;
        }
        f[0][1]=0;
        for(int i=0;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                f[i][j*2]=min(f[i][j*2],f[i][j]+b[n-i]);
                f[i+1][j-1]=min(f[i+1][j-1],f[i][j]+d[j]);
            }
        }
        printf("%lld\n",f[n][0]-(n-1));
    }
    return 0;
}