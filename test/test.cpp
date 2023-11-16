#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
ll b[N],c[N],d[N],f[N],g[N];
ll sum(int x)
{
    if(x==0) return 0;
    return (x&-x)-1;
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
            scanf("%d",&a[i]);
        }
        sort(a+1,a+n+1);
        for(int i=1;i<=n;++i) b[i]=b[i-1]+a[i];
        for(int i=1;i<=n;++i) c[i]=c[i-1]+sum(i-1);
        for(int i=1;i<=n;++i) d[i]=c[i*2]-c[i];
        for(int i=1;i<=n;++i) f[i]=1e18;
        f[1]=0;
        ll s=1e18;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j) g[j]=f[j],f[j]=1e18;
            for(int j=1;j<=n;++j)
            {
                if(g[j]>s) continue;
                for(int k=0;k<=j;++k)
                {
                    f[j+k]=min(f[j+k],g[j]+d[k]+b[n-j+k]);
                }
            }
            s=min(s,f[n]);
        }
        printf("%lld\n",s);
    }
    return 0;
}