#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll b[11],a[N],f[N][11];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
int main()
{
    scanf("%d%lld%lld%lld",&n,&b[1],&b[2],&b[4]);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=0;i<=7;++i)
    {
        ll w=1;
        for(int j=1;j<=3;++j)
        {
            if(i&(1<<(j-1)))
            {
                w=w*b[(1<<(j-1))]/gcd(w,b[(1<<(j-1))]);
            }
        }
        b[i]=w;
        // printf("%d %lld\n",i,w);
    }
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<=7;++j) f[i][j]=1e18;
    }
    f[0][0]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=7;++j)
        {
            for(int k=0;k<=7;++k)
            {
                if(j&k) continue;
                f[i][j|k]=min(f[i][j|k],f[i-1][j]+(-a[i]%b[k]+b[k])%b[k]);
            }
        }
    }
    printf("%lld\n",f[n][7]);
    return 0;
}