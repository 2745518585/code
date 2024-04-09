#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll m,k,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%lld%lld",&n,&m,&k);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        sort(a+1,a+n+1);
        ll s=0,t=0;
        for(int i=1;i<=n;++i)
        {
            ll z=min(k,m);
            s+=(a[i]+t)*z;
            t+=z;
            k-=z;
        }
        printf("%lld\n",s);
    }
    return 0;
}