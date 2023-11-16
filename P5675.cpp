#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=1e9+7;
int n,a[N];
ll f[N],g[N];
ll solve(int x)
{
    for(int i=0;i<=500;++i) f[i]=0;
    f[0]=1;
    for(int i=1;i<=n;++i)
    {
        if(i==x) continue;
        for(int j=0;j<=500;++j) g[j]=f[j];
        for(int j=0;j<=500;++j)
        {
            f[j^a[i]]=(f[j^a[i]]+g[j])%P;
        }
    }
    ll s=0;
    for(int i=a[x];i<=500;++i) s=(s+f[i])%P;
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    ll s=0;
    for(int i=1;i<=n;++i) s=(s+solve(i))%P;
    printf("%lld",s);
    return 0;
}