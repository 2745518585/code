#include<cstdio>
using namespace std;
const int N=100001;
int n,m,p=0,t[N],g[N];
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
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(y,x);
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) h[j]=false;
        if(dfs(i)) ++s;
    }
    for(int i=1;i<=n;++i)
    {
        if(g[i]==0)
        {
            printf("Mirko\n");
            continue;
        }
        for(int j=1;j<=n;++j) h[j]=false;
        h[i]=true;
        if(dfs(g[i])==false) printf("Slavko\n");
        else g[i]=0,printf("Mirko\n");
    }
    return 0;
}