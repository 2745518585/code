#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001;
int n,m,p=1,s=1e9,t[N],b[N],fa[N],f1[N],f2[N],f3[N],g1[N],g2[N],g3[N];
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
void dfs0(int x)
{
    f3[x]=b[x];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa[x]) continue;
        fa[a[i].m]=x;
        dfs0(a[i].m);
        f3[x]+=f3[a[i].m];
        f2[x]+=f2[a[i].m]+f3[a[i].m]*a[i].w;
        f1[x]+=f1[a[i].m]+2*f3[a[i].m]*a[i].w*f2[a[i].m]+a[i].w*a[i].w;
    }
}
void dfs(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa[x]) continue;
        dfs(a[i].m);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        m+=b[i];
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    
}