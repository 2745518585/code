#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
ll f[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<=n;++i) f[i]=1e18;
    f[1]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=i-1;j>=max(i-n/a[i],0);--j)
        {
            f[i]=min(f[i],f[j]+(ll)(i-j)*(i-j)*a[i]);
            if(a[j]<=a[i]) break;
        }
        for(int j=i+1;j<=min(i+n/a[i],n);++j)
        {
            f[j]=min(f[j],f[i]+(ll)(j-i)*(j-i)*a[i]);
            if(a[j]<=a[i]) break;
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%lld ",f[i]);
    }
    return 0;
}