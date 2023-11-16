#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=501,M=21;
const ll P=1e9+7;
int n,m;
ll a[N];
struct sum
{
    ll f[N][M][M][3],f2[N][M],g[N][N];
    int b[N],t;
    void abc(ll &a,ll b)
    {
        a=(a+b)%P;
    }
    void clear()
    {
        for(int i=0;i<=n+1;++i)
        {
            for(int j=0;j<=t+1;++j)
            {
                for(int k=0;k<=t+1;++k) f[i][j][k][0]=f[i][j][k][1]=f[i][j][k][2]=0;
            }
        }
        for(int i=0;i<=n+1;++i)
        {
            for(int j=0;j<=t+1;++j) f2[i][j]=0;
        }
    }
    void check(int x)
    {
        for(int i=0;i<=t+1;++i)
        {
            for(int j=0;j<=t+1;++j)
            {
                abc(f[x][i][j][0],f[x+1][i][j][0]);
                abc(f[x][i][j][1],f[x+1][i][j][1]);
                abc(f[x][i][j][2],f[x+1][i][j][2]);
            }
        }
        for(int i=1;i<=t;++i)
        {
            for(int j=i;j<=t;++j)
            {
                if(a[x]<=b[i]) abc(f[x][i+1][j][0],f[x+1][i][j][0]);
                else abc(f[x][i+1][j][1],f[x+1][i][j][0]);
                if(a[x]==b[j]) abc(f[x][i][j-1][0],f[x+1][i][j][0]);
                else if(a[x]<b[j]) abc(f[x][i][j-1][2],f[x+1][i][j][0]);
                if(a[x]<=b[i]-1) abc(f[x][i+1][j][0],f[x+1][i][j][1]);
                else abc(f[x][i+1][j][1],f[x+1][i][j][1]);
                if(a[x]==b[j]) abc(f[x][i][j-1][1],f[x+1][i][j][1]);
                else if(a[x]<b[j]) abc(f[x][i][j-1][2],f[x+1][i][j][1]);
                abc(f[x][i+1][j][2],f[x+1][i][j][2]);
                abc(f[x][i][j-1][2],f[x+1][i][j][2]);
            }
        }
        for(int i=0;i<=t;++i)
        {
            abc(f2[x][i],f2[x+1][i]);
            abc(f2[x][i+1],f2[x+1][i]*2);
        }
    }
    void solve(ll x)
    {
        while(x)
        {
            b[++t]=x%10;
            x/=10;
        }
        for(int i=1;i<=n;++i)
        {
            clear();
            f[i+1][1][t][0]=1;
            f2[i+1][0]=1;
            for(int j=i;j>=1;--j)
            {
                check(j);
                for(int k=0;k<=t-1;++k) abc(g[j][i],f2[j][k]);
                for(int k=1;k<=t+1;++k) abc(g[j][i],f[j][k][k-1][0]+f[j][k][k-1][2]);
            }
        }
    }
}Sum1,Sum2;
int main()
{
    ll l,r;
    scanf("%d%lld%lld",&n,&l,&r);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    Sum1.solve(l-1);
    Sum2.solve(r);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%lld\n",(Sum2.g[x][y]-Sum1.g[x][y]%P+P)%P);
    }
    return 0;
}