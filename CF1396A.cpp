#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
ll n,a[N];
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    if(n==1)
    {
        printf("%d %d\n%lld\n1 1\n0\n1 1\n0",1,1,-a[1]);
        return 0;
    }
    printf("%d %d\n",1,n);
    for(int i=1;i<=n;++i)
    {
        printf("%lld ",-a[i]*n);
    }
    printf("\n%d %d\n",2,n);
    for(int i=2;i<=n;++i)
    {
        printf("%lld ",a[i]*(n-1));
    }
    printf("\n%d %d\n",1,1);
    printf("%lld",a[1]*(n-1));
    return 0;
}