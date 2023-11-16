#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=10001,M=301,P=1000000;
int n,m,q,s,h[P],a[N],b[N],fa[M][N],g[M][N];
vector<int> f[M][N];
int main()
{
    scanf("%d%d%d",&q,&n,&m);
    for(int i=1;i<=q;++i) b[i]=rand();
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=q;++j)
        {
            f[j][i].push_back(i);
            g[j][i]=i;
            fa[j][i]=i;
            a[i]=(a[i]+i*b[j]%P)%P;
        }
        a[i]=(a[i]%P+P)%P;
        s+=h[a[i]]*2+1;
        ++h[a[i]];
    }
    for(int i=1;i<=m;++i)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        x=fa[k][x],y=fa[k][y];
        if(x==y)
        {
            printf("%d\n",s);
            continue;
        }
        if(g[k][x]>g[k][y]) swap(x,y);
        for(int j=0;j<f[k][y].size();++j)
        {
            --h[a[f[k][y][j]]];
            s-=h[a[f[k][y][j]]]*2+1;
            a[f[k][y][j]]=(a[f[k][y][j]]-b[k]*abs(g[k][x]-g[k][y])%P)%P;
            a[f[k][y][j]]=(a[f[k][y][j]]%P+P)%P;
            s+=h[a[f[k][y][j]]]*2+1;
            ++h[a[f[k][y][j]]];
            f[k][x].push_back(f[k][y][j]);
            fa[k][f[k][y][j]]=x;
        }
        // for(int j=1;j<=n;++j)
        // {
        //     printf("%d ",a[j]);
        // }
        // printf("\n");
        f[k][y].clear();
        g[k][x]=min(g[k][x],g[k][y]);
        printf("%d\n",s);
    }
    return 0;
}