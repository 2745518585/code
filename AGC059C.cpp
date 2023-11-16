#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=1e9+7;
int n,m,a[N][N],fa[N*N],g[N][N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i==j) continue;
            g[i][j]=++m;
        }
    }
    for(int i=1;i<=m;++i) fa[i]=i;
    for(int i=1;i<=n*(n-1)/2;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x][y]=a[y][x]=i;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i==j) continue;
            for(int k=1;k<=n;++k)
            {
                if(i==k||j==k) continue;
                if(a[i][j]<a[i][k]&&a[j][k]<a[i][k])
                {
                    fa[find(g[i][j])]=find(g[k][j]);
                    fa[find(g[j][i])]=find(g[j][k]);
                }
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=i-1;++j)
        {
            if(find(g[i][j])==find(g[j][i]))
            {
                printf("0\n");
                return 0;
            }
        }
    }
    int w=0;
    for(int i=1;i<=m;++i)
    {
        if(find(i)==i) ++w;
    }
    ll s=1;
    for(int i=1;i<=w/2;++i) s=(s*2)%P;
    printf("%lld",s);
    return 0;
}