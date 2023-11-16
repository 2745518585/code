#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,p=1,t[N],f[N],f2[N],g[N],g2[N];
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
    f[x]=f2[x]=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        if(f[a[i].m]+max(f2[a[i].m]-1,0)==0) ++f2[x];
        f[x]+=f[a[i].m]+max(f2[a[i].m]-1,0);
    }
}
void dfs2(int x,int fa)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        g[a[i].m]=g[x]+max(g2[x]-1,0)+f[x]-(f[a[i].m]+max(f2[a[i].m]-1,0));
        g2[a[i].m]=(g[x]+max(g2[x]-1,0)==0&&x!=1)+f2[x]-(f[a[i].m]+max(f2[a[i].m]-1,0)==0);
        dfs2(a[i].m,x);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        if(n==1)
        {
            printf("0\n");
            continue;
        }
        p=1;
        for(int i=1;i<=n;++i) t[i]=0;
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            road(x,y);
            road(y,x);
        }
        dfs(1,0);
        g[1]=0;
        dfs2(1,0);
        int s=1e9;
        for(int i=1;i<=n;++i)
        {
            int u=g[i]+max(g2[i]-1,0);
            s=min(s,f[i]+u+max(f2[i]+(u==0&&i!=1)-1,0)+1);
        }
        printf("%d\n",s);
    }
    return 0;
}