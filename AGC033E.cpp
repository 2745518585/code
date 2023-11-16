#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,m,k=1e9;
char a[N];
ll f[N],g[N];
int main()
{
    scanf("%d%d%s",&n,&m,a+1);
    int x=0;
    for(int i=1;i<=m;++i)
    {
        if(a[i]!=a[1])
        {
            if(x==0) k=min(k,i-x+1);
            else if((i-x)%2==0) k=min(k,i-x);
            x=i;
        }
    }
    if(x==0)
    {
        f[0]=g[0]=1;
        for(int i=1;i<=n;++i)
        {
            f[i]=g[i-2];
            g[i]=(g[i-1]+f[i])%P;
        }
        ll s=f[n]+1;
        for(int i=2;i<=n;++i) s=(s+f[n-i]*(i-1)%P)%P;
        printf("%lld\n",s%P);
        return 0;
    }
    if(n%2!=0)
    {
        printf("0\n");
        return 0;
    }
    n/=2,k/=2;
    f[0]=g[0]=1;
    for(int i=1;i<=n;++i)
    {
        f[i]=((g[i-1]-(i-k-1>=0?g[i-k-1]:0))%P+P)%P;
        g[i]=(g[i-1]+f[i])%P;
    }
    ll s=f[n];
    for(int i=1;i<=k;++i) s=(s+f[n-i]*(i*2-1)%P)%P;
    printf("%lld",(s%P+P)%P);
    return 0;
}