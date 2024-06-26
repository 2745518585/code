#include<cstdio>
#include<algorithm>
#include<bitset>
using namespace std;
typedef long long ll;
const int N=50001;
int n,k,a[N],b[N];
bitset<N> f[N],g[N];
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[a[i]]=i;
    }
    for(int i=n-1;i>=1;--i)
    {
        f[i]=f[i+1];
        f[i][b[i+1]]=1;
    }
    for(int i=1;i<=n;++i) f[i]=f[i]>>b[i];
    ll s=0;
    for(int i=k;i<=n;i+=k)
    {
        g[i]=f[a[i]];
        for(int j=i-1;j>=i-k+1;--j) g[j]=g[j+1]&f[a[j]];
        bitset<N> p=f[a[i]];
        for(int j=i;j<=min(i+k-1,n);++j)
        {
            p=p&f[a[j]];
            s+=(g[j-k+1]&p).count();
        }
    }
    printf("%lld",s);
    return 0;
}