#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100001,M=101;
const ll P=1e9+7;
int n,m,p=1,t[N],b[N],f[N][M][2][2],g[M][2][2];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int fa)
{
    b[x]=1;
    f[x][0][0][0]=1;
    f[x][1][1][0]=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        for(int j=0;j<=m;++j)
        {
            g[j][0][0]=f[x][j][0][0];
            f[x][j][0][0]=0;
            g[j][0][1]=f[x][j][0][1];
            f[x][j][0][1]=0;
            g[j][1][0]=f[x][j][1][0];
            f[x][j][1][0]=0;
            g[j][1][1]=f[x][j][1][1];
            f[x][j][1][1]=0;
        }
        for(int j=0;j<=min(b[x],m);++j)
        {
            for(int k=0;k<=min(b[a[i].m],m-j);++k)
            {
                f[x][j+k][0][0]=((ll)f[x][j+k][0][0]+(ll)g[j][0][0]*(ll)f[a[i].m][k][0][1]%P)%P;
                f[x][j+k][0][1]=((ll)f[x][j+k][0][1]+(ll)g[j][0][0]*(ll)f[a[i].m][k][1][1]%P+(ll)g[j][0][1]*((ll)f[a[i].m][k][0][1]+(ll)f[a[i].m][k][1][1])%P)%P;
                f[x][j+k][1][0]=((ll)f[x][j+k][1][0]+(ll)g[j][1][0]*((ll)f[a[i].m][k][0][0]+(ll)f[a[i].m][k][0][1])%P)%P;
                f[x][j+k][1][1]=((ll)f[x][j+k][1][1]+(ll)g[j][1][0]*((ll)f[a[i].m][k][1][0]+(ll)f[a[i].m][k][1][1])%P+(ll)g[j][1][1]*((ll)f[a[i].m][k][0][0]+(ll)f[a[i].m][k][1][0]+(ll)f[a[i].m][k][0][1]+(ll)f[a[i].m][k][1][1])%P)%P;
            }
        }
        b[x]+=b[a[i].m];
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs(1,0);
    printf("%lld\n",((ll)f[1][m][0][1]+(ll)f[1][m][1][1])%P);
    return 0;
}