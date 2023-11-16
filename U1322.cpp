#include<cstdio>
using namespace std;
const int N=100001;
int n,m,p=0,t[N],g[N],f[N];
bool h[N];
struct str
{
    int m,q;
}a[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
bool dfs(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]==true) continue;
        h[a[i].m]=true;
        if(g[a[i].m]==0||dfs(g[a[i].m]))
        {
            g[a[i].m]=x;
            return true;
        }
    }
    return false;
}
int main()
{
    scanf("%d%d",&n,&m);
    while(true)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x==-1&&y==-1) break;
        road(x,y);
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=n+1;j<=m;++j) h[j]=false;
        if(dfs(i)) ++s;
    }
    printf("%d\n",s);
    for(int i=n+1;i<=m;++i)
    {
        f[g[i]]=i;
    }
    for(int i=1;i<=n;++i)
    {
        if(f[i]!=0) printf("%d %d\n",i,f[i]);
    }
    return 0;
}