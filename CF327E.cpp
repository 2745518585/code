#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=24;
const ll P=1e9+7;
int n,m,a[N+1],b[N+1],h[1<<N];
ll f[1<<N],g[1<<N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    scanf("%d",&m);
    b[1]=b[2]=-1;
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n;++i) h[1<<(i-1)]=i;
    f[0]=1;
    g[0]=0;
    for(int i=1;i<=(1<<n)-1;++i)
    {
        g[i]=g[i-(i&-i)]+a[h[i&-i]];
        if(g[i]==b[1]||g[i]==b[2]) continue;
        for(int x=i;x;x^=(x&-x))
        {
            f[i]=(f[i]+f[i^(x&-x)])%P;
        }
    }
    printf("%lld",f[(1<<n)-1]);
    return 0;
}