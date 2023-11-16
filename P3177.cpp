#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001;
int n,m,p=1,t[N],b[N];
ll f[N][N],g[N];
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
    b[x]=1;
    for(int i=0;i<=m;++i) f[x][i]=-1e9;
    f[x][0]=f[x][1]=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        for(int j=0;j<=min(b[x],m);++j) g[j]=f[x][j];
        for(int j=0;j<=min(b[x],m);++j)
        {
            for(int k=0;k<=min(b[a[i].m],m-j);++k)
            {
                f[x][j+k]=max(f[x][j+k],g[j]+f[a[i].m][k]+(ll)a[i].w*((ll)k*(m-k)+(ll)(b[a[i].m]-k)*((n-m)-(b[a[i].m]-k))));
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
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    dfs(1,0);
    printf("%lld",f[1][m]);
    return 0;
}