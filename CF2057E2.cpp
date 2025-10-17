#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=401;
int n,m,q,f[N][N][N],g[N][N],fa[N];
bool h[N];
struct str
{
    int x,y,w;
}p[N*N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&q);
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j) g[i][j]=1e9;
        }
        for(int i=1;i<=m;++i)
        {
            int x,y,w;
            scanf("%d%d%d",&x,&y,&w);
            g[x][y]=g[y][x]=1;
            p[i]=(str){x,y,w};
        }
        for(int i=1;i<=n;++i) g[i][i]=0;
        for(int k=1;k<=n;++k)
        {
            for(int i=1;i<=n;++i)
            {
                for(int j=1;j<=n;++j) g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
            }
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                for(int k=0;k<=n;++k) f[i][j][k]=1e9;
            }
        }
        sort(p+1,p+m+1,[](str a,str b){return a.w<b.w;});
        for(int i=1;i<=n;++i) fa[i]=i;
        for(int i=1;i<=m;++i)
        {
            int x=p[i].x,y=p[i].y;
            if(find(x)==find(y)) continue;
            g[x][y]=g[y][x]=0;
            for(int j=1;j<=n;++j)
            {
                for(int k=1;k<=n;++k)
                {
                    g[j][k]=min(g[j][k],min(g[j][x]+g[y][k],g[j][y]+g[x][k]));
                    f[j][k][g[j][k]]=min(f[j][k][g[j][k]],p[i].w);
                }
            }
            fa[find(x)]=find(y);
        }
        for(int i=1;i<=q;++i)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            printf("%d ",f[x][y][k-1]);
        }
        printf("\n");
    }
    return 0;
}