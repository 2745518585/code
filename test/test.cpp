#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=998244353;
int n;
ll f[N];
int main()
{
    for(int i=4;i<=1000000;++i)
    {
        f[i]=f[i-1]+i-2;
    }
    ll w=0;
    for(int i=1;i<=1000000;++i)
    {
        f[i]=(f[i]+w)%P;
        w=(w+f[i]*i)%P;
    }
    for(int i=1;i<=1000000;++i) f[i]=(f[i]+f[i-1])%P;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("%lld\n",((f[n]+(n-1))%P+P)%P);
    }
    return 0;
}