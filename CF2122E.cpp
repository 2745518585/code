#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=601;
const ll P=998244353;
int n,m,a[N],b[N];
ll f[2][N*N],g[2][N*N];
bool check(int x)
{
    return x>=1&x<=m;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
        }
        for(int i=0;i<=1;++i)
        {
            for(int j=0;j<=m*m;++j) f[i][j]=g[i][j]=0;
        }
        if(a[1]==-1) f[1][m]=m;
        else f[1][m]=1;
        for(int i=1;i<=n;++i)
        {
            int t=i&1;
            for(int j=0;j<=m*m;++j) f[t^1][j]=0;
        }
        printf("%lld\n",(f[n+1][m]%P+P)%P);
    }
    return 0;
}