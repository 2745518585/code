#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll a[N],b[N],pow10[21];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    pow10[0]=1;
    for(int i=1;i<=15;++i) pow10[i]=pow10[i-1]*10;
    ll s=0;
    for(int i=1;i<=15;++i)
    {
        for(int j=1;j<=n;++j)
        {
            b[j]=a[j]%pow10[i];
            s+=(ll)(a[j]/pow10[i-1]%10)*n*2;
        }
        sort(b+1,b+n+1);
        for(int j=1;j<=n;++j)
        {
            int k=lower_bound(b+1,b+n+1,pow10[i]-b[j])-b;
            s-=9*(n-k+1);
        }
    }
    printf("%lld",s);
    return 0;
}