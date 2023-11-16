#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001,P=1e9+7;
int n,f1[N],f2[N];
ll a[N],b[N],s;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&a[i],&b[i]);
        f1[i]=f2[i]=i;
    }
    for(int i=2;i<=n;++i)
    {
        while(f1[i]>1&&a[i]-a[f1[i]-1]<=b[i])
        {
            b[i]=max(b[i],b[f1[i]-1]-(a[i]-a[f1[i]-1]));
            f1[i]=f1[f1[i]-1];
        }
    }
    for(int i=n-1;i>=1;--i)
    {
        while(f2[i]<n&&a[f2[i]+1]-a[i]<=b[i])
        {
            f1[i]=min(f1[i],f1[f2[i]+1]);
            f2[i]=f2[f2[i]+1];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        s=(s+(ll)i*(f2[i]-f1[i]+1))%P;
    }   
    printf("%lld",s);
    return 0;
}
