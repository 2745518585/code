#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,p=1,t[N],l[N],f[N];
bool u,v;
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
void dfs(int x,int fa,int w)
{
    if(l[x]==1)
    {
        if(w%2==0) u=true;
        else v=true;
    }
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x,w^1);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
        ++l[x],++l[y];
    }
    dfs(1,0,0);
    if(u&&v) printf("%d ",3);
    else printf("%d ",1);
    for(int i=1;i<=n;++i)
    {
        if(l[i]!=1) continue;
        for(int j=t[i];j!=0;j=a[j].q) ++f[a[j].m];
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        if(f[i]>1) s+=f[i]-1;
    }
    printf("%d",n-s-1);
    return 0;
}