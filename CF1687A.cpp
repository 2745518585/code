#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
ll n,m,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&m);
        ll w=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
            w+=a[i];
        }
        if(m>=n)
        {
            printf("%lld\n",w+(m-n)*n+n*(n-1)/2);
            continue;
        }
        w=0;
        for(int i=1;i<=m;++i) w+=a[i];
        ll s=w;
        for(int i=m+1;i<=n;++i)
        {
            w+=a[i]-a[i-m];
            s=max(s,w);
        }
        printf("%lld\n",s+m*(m-1)/2);
    }
    return 0;
}