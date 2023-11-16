#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=201;
const ll P=998244353;
int n,m,a[N],b[N];
ll f[N][N][N],g[N][N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    return (x%P+P)%P;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&m);
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&a[i]);
        }
        n=a[1];
        for(int i=1;i<=m-1;++i)
        {
            scanf("%d",&b[i]);
        }
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=a[i];++j)
            {
                for(int k=1;k<=n;++k) f[k][i][j]=0;
            }
        }
        for(int i=1;i<=n;++i) f[i][1][i]=1;
        for(int i=1;i<=m-1;++i)
        {
            for(int j=1;j<=b[i];++j)
            {
                int x,y;
                scanf("%d%d",&x,&y);
                for(int k=1;k<=n;++k) f[k][i+1][y]=(f[k][i+1][y]+f[k][i][x])%P;
            }
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                g[i][j]=f[i][m][j];
            }
        }
        ll s=1;
        for(int i=1;i<=n;++i)
        {
            if(!g[i][i])
            {
                s=-s;
                for(int j=i;j<=n;++j)
                {
                    if(g[j][i]!=0)
                    {
                        swap(g[i],g[j]);
                        break;
                    }
                }
            }
            for(int j=i+1;j<=n;++j)
            {
                ll z=g[j][i]*inv(g[i][i])%P;
                for(int k=i;k<=n;++k)
                {
                    g[j][k]=(g[j][k]-g[i][k]*z%P+P)%P;
                }
            }
        }
        for(int i=1;i<=n;++i) s=(s*g[i][i])%P;
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}