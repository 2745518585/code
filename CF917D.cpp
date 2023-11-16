#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=1e9+7;
int n,m,p=1,t[N],d[N];
ll f[N][N][2],g[N][2],h[N],C[N][N],pown[N];
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
    f[x][1][0]=f[x][1][1]=1;
    d[x]=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        for(int j=1;j<=d[x];++j) g[j][0]=f[x][j][0],g[j][1]=f[x][j][1],f[x][j][0]=f[x][j][1]=0;
        for(int j=1;j<=d[x];++j)
        {
            for(int k=1;k<=d[a[i].m];++k)
            {
                f[x][j+k][0]=(f[x][j+k][0]+g[j][0]*f[a[i].m][k][1]%P)%P;
                f[x][j+k][1]=(f[x][j+k][1]+g[j][1]*f[a[i].m][k][1]%P)%P;
                f[x][j+k-1][0]=(f[x][j+k-1][0]+g[j][0]*f[a[i].m][k][0]%P)%P;
                f[x][j+k-1][1]=(f[x][j+k-1][1]+g[j][0]*f[a[i].m][k][1]%P+g[j][1]*f[a[i].m][k][0]%P)%P;
            }
        }
        d[x]+=d[a[i].m];
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs(1,0);
    pown[0]=1;
    for(int i=1;i<=n;++i) pown[i]=pown[i-1]*n%P;
    for(int i=0;i<=n-2;++i) h[i]=pown[n-i-2]*f[1][n-i][1]%P;
    h[n-1]=1;
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    for(int i=0;i<=n-1;++i)
    {
        ll s=0;
        for(int j=i;j<=n-1;++j)
        {
            if((j-i)%2==0) s=(s+C[j][i]*h[j]%P)%P;
            else s=(s-C[j][i]*h[j]%P)%P;
        }
        printf("%lld ",(s%P+P)%P);
    }
    return 0;
}