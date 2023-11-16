#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m;
ll a[N];
int main()
{
    scanf("%d%d",&n,&m);
    m=n-m;
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        s+=a[i]*a[i];
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=m;++i) s+=a[i]*a[m*2-i+1]*2;
    printf("%lld\n",s);
    return 0;
}