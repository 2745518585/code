#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10001;
int n,a[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        a[i]=abs(a[i]);
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        int x1=0,x2=0;
        for(int j=1;j<=i-1;++j) x1+=a[j]<a[i];
        for(int j=i+1;j<=n;++j) x2+=a[j]<a[i];
        s+=min(x1,x2);
    }
    printf("%lld",s);
    return 0;
}