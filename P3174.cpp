#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,p=1,t[N],f[N],g[N],s;
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
    f[x]=1,g[x]=1;
    int u=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        ++u;
        dfs(a[i].m,x);
        if(f[a[i].m]>f[x]) g[x]=f[x],f[x]=f[a[i].m];
        else if(f[a[i].m]>g[x]) g[x]=f[a[i].m];
    }
    f[x]+=u;
    s=max(s,f[x]+g[x]+(fa!=0)-1);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs(1,0);
    printf("%d",s);
    return 0;
}