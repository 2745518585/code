#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001;
int n,r,b[N],t[N],p=1,f[N];
struct road
{
    int m,q,w;
}a[N];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void dfs(int x,int fa)
{
    if(a[t[x]].m==fa&&a[t[x]].q==0)
    {
        f[x]=1e9;
        return;
    }
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        f[x]+=min(f[a[i].m],a[i].w);
    }
}
int main()
{
    scanf("%d%d",&n,&r);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    dfs(r,0);
    printf("%d",f[r]);
}