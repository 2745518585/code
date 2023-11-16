#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3001;
const ll P=1e9+7;
int n,m,p=1,t[N],d[N];
ll f[N][N],g[N],g1[N][N],g2[N][N],C[N][N];
struct road
{
    int m,q,w;
}a[N<<1];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void dfs(int x,int fa)
{
    for(int i=0;i<=n+1;++i) f[x][i]=g1[x][i]=g2[x][i]=0;
    f[x][1]=1;
    d[x]=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        for(int j=0;j<=d[x]+d[a[i].m];++j) g[j]=f[x][j],f[x][j]=0;
        if(a[i].w==0)
        {
            for(int j=1;j<=d[x];++j)
            {
                for(int k=0;k<=d[a[i].m];++k)
                {
                    f[x][j+k]=(f[x][j+k]+g[j]*g1[a[i].m][k]%P*C[j+k-1][j-1]%P*C[d[x]+d[a[i].m]-j-k][d[x]-j]%P)%P;
                }
            }
        }
        else
        {
            for(int j=1;j<=d[x];++j)
            {
                for(int k=0;k<=d[a[i].m];++k)
                {
                    f[x][j+k]=(f[x][j+k]+g[j]*g2[a[i].m][k+1]%P*C[j+k-1][j-1]%P*C[d[x]+d[a[i].m]-j-k][d[x]-j]%P)%P;
                }
            }
        }
        d[x]+=d[a[i].m];
    }
    for(int i=1;i<=d[x];++i) g1[x][i]=(g1[x][i-1]+f[x][i])%P;
    for(int i=d[x];i>=1;--i) g2[x][i]=(g2[x][i+1]+f[x][i])%P;
}
void init()
{
    C[0][0]=1;
    for(int i=1;i<=2000;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=2000;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
}
int main()
{
    init();
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        p=1;
        for(int i=1;i<=n;++i) t[i]=0;
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            char z[10];
            scanf("%d%s%d",&x,z,&y);
            ++x,++y;
            if(z[0]=='>')
            {
                road(x,y,0);
                road(y,x,1);
            }
            else
            {
                road(x,y,1);
                road(y,x,0);
            }
        }
        dfs(1,0);
        printf("%lld\n",g1[1][n]);
    }
    return 0;
}