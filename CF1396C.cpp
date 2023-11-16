#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
int n;
ll f[N],m,k1,k2,k3,a[N];
int main()
{
    scanf("%d%lld%lld%lld%lld",&n,&k1,&k2,&k3,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n+1;++i) f[i]=1e18;
    f[1]=0;
    for(int i=1;i<=n;++i)
    {
        f[i+1]=min(f[i+1],f[i]+min(k1*a[i]+k3,min(k1*(a[i]+1),k2)+m*2+k1)+m);
        f[i+2]=min(f[i+2],f[i]+min(k1*(a[i]+1),k2)+m+min(k1*(a[i+1]+1),k2)+m+k1+m+k1+m);
    }
    printf("%lld",min(f[n+1]-m,f[n-1]+min(k1*(a[n-1]+1),k2)+m+k1*a[n]+k3+m+k1));
    return 0;
}