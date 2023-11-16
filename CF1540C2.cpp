#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
const int N=201;
const ll P=1e9+7;
int n,m,b[N],c[N],b2[N],c2[N];
ll f[N][N*N],g[N][N*N];
map<int,ll> Map;
int main()
{
    scanf("%d",&n);
    ll w=1;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&c[i]);
        w=(w*(c[i]+1))%P;
    }
    for(int i=2;i<=n;++i)
    {
        scanf("%d",&b[i]);
        b[i]+=b[i-1];
    }
    for(int i=1;i<=n;++i) b2[i]=b2[i-1]+b[i];
    int mn=-b2[n]/n-1,mx=100-b2[n]/n+1;
    scanf("%d",&m);
    while(m--)
    {
        int x;
        scanf("%d",&x);
        if(x>mx) 
        {
            printf("0\n");
            continue;
        }
        if(x<mn)
        {
            printf("%lld\n",(w%P+P)%P);
            continue;
        }
        if(Map.count(x))
        {
            printf("%lld\n",Map[x]);
            continue;
        }
        for(int i=1;i<=n;++i)
        {
            b2[i]=b2[i-1]+b[i]+x;
            c2[i]=c2[i-1]+c[i];
        }
        f[0][0]=g[0][0]=1;
        for(int i=1;i<=n;++i)
        {
            for(int j=max(b2[i],0);j<=c2[i];++j)
            {
                f[i][j]=(g[i-1][min(j,c2[i-1])]-(j>c[i]?g[i-1][min(j-c[i]-1,c2[i-1])]:0));
            }
            for(int j=0;j<=max(b2[i],0)-1;++j) g[i][j]=0;
            for(int j=max(b2[i],0);j<=c2[i];++j) g[i][j]=((j>0?g[i][j-1]:0)+f[i][j])%P;
        }
        ll s=0;
        for(int i=max(b2[n],0);i<=c2[n];++i) s=(s+f[n][i])%P;
        printf("%lld\n",(s%P+P)%P);
        Map[x]=(s%P+P)%P;
    }
    return 0;
}