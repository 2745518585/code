#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=6001;
int n;
ll f[N],P;
int main()
{
    scanf("%d%lld",&n,&P);
    f[0]=1;
    for(int i=1;i<=n;++i)
    {
        int x=min(i,n/2+1)-max(n/2-(n-i),0);
        for(int j=x;j<=n-1;++j) f[j]=(f[j]+f[j-x])%P;
    }
    ll s=0;
    for(int i=0;i<=n-1;++i) s=(s+f[i])%P;
    printf("%lld",s);
    return 0;
}