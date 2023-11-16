#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=1e9+7;
int m,n;
ll f[N];
int main()
{
    int k;
    scanf("%d",&k);
    for(int i=1;i<=k;++i)
    {
        int x;
        scanf("%d",&x);
        if(x==1) ++m;
        else ++n;
    }
    f[0]=f[1]=1;
    for(int i=2;i<=m;++i) f[i]=((i-1)*f[i-2]%P+f[i-1])%P;
    ll s=f[m];
    for(int i=1;i<=n;++i) s=s*(m+n-i+1)%P;
    printf("%lld",s);
    return 0;
}