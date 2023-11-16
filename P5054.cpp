#include<bits/stdc++.h>
using namespace std;
const int N=1001;
int n,m,p=1,t[N],b[N],f[N][N],g[N][N];
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
    for(int i=1;i<=m;++i) f[x][i]=g[x][i]=b[x];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        for(int j=m;j>=0;--j)
        {
            for(int k=1;k<=j;++k)
            {
                if(k>=2) f[x][j]=max(f[x][j],f[x][j-k]+f[a[i].m][k-2]);
                g[x][j]=max(g[x][j],f[x][j-k]+g[a[i].m][k-1]);
                if(k>=2) g[x][j]=max(g[x][j],g[x][j-k]+f[a[i].m][k-2]);
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs(1,0);
    int s=0;
    for(int i=0;i<=m;++i)
    {
        s=max(s,g[1][i]);
    }
    printf("%d",s);
    return 0;
}