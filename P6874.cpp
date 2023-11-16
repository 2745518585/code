#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=300001;
int n,m,a[N<<1];
ll s;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        a[i]-=abs(i-(n+1)/2);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[n+i]);
        a[n+i]-=abs(i-(n+1)/2);
    }
    sort(a+1,a+n*2+1);
    for(int i=1;i<=n*2;++i)
    {
        s+=abs(a[i]-a[n]);
    }
    printf("%lld",s);
    return 0;
}