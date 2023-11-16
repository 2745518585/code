#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int m;
ll n,f[N][11],g[N][11];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%d",&n,&m);
        if(m>2)
        {
            if(n%2==0) printf("%lld\n",((n/2)%P)*((n/2+1)%P)%P);
            else printf("%lld\n",((n+1)/2%P)*((n+1)/2%P)%P);
            continue;
        }
        if(m==1)
        {
            printf("%lld\n",n%P);
            continue;
        }
        g[61][0]=1;
        for(int i=60;i>=0;--i)
        {
            for(int j=0;j<=m;++j) f[i][j]=g[i][j]=0;
            for(int j=0;j<=m;++j)
            {
                int x=j*2+((n&(1ll<<i))!=0);
                for(int k=max(x-m,0);k<=min(x,m);++k)
                {
                    if(k%2==1)
                    {
                        f[i][x-k]=(f[i][x-k]+f[i+1][j]+g[i+1][j]*((1ll<<i)%P)%P)%P;
                        g[i][x-k]=(g[i][x-k]+g[i+1][j])%P;
                    }
                    else
                    {
                        f[i][x-k]=(f[i][x-k]+f[i+1][j])%P;
                        g[i][x-k]=(g[i][x-k]+g[i+1][j])%P;
                    }
                }
            }
        }
        printf("%lld\n",f[0][0]);
    }
    return 0;
}