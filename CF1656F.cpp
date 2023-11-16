#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
ll n,a[N],b[N];
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
        if(a[1]*(n-2)+b[n]>0||a[n]*(n-2)+b[n]<0)
        {
            printf("INF\n");
            continue;
        }
        ll s=-1e18;
        for(int i=1;i<=n-1;++i)
        {
            s=max(s,-(n-1)*a[i]*a[i]+(a[n]-a[i])*(b[i]-i*a[i])+(a[1]-a[i])*((b[n-1]-b[i])-(n-1-i)*a[i]));
        }
        printf("%lld\n",s);
    }
    return 0;
}