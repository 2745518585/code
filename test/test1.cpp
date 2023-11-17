#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll a[N],b[N],d[N],f[N],g[N];
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
        for(int i=0;i<=n;++i) f[i]=g[i]=1e18;
        f[1]=0;
        for(int i=0;i<=n;++i)
        {
            for(int j=0;j<=n;++j) g[j]=f[j],f[j]=1e18;
            for(int j=1;j<=n;++j)
            {
                g[j*2]=min(g[j*2],g[j]+b[n-i]);
                f[j-1]=min(f[j-1],g[j]+d[j]);
            }
        }
        printf("%lld\n",g[0]-(n-1));
    }
    return 0;
}