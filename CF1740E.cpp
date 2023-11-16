#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,p=1,t[N],f[N],g[N];
struct road
{
    int m,q;
}a[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x)
{
    f[x]=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        dfs(a[i].m);
        f[x]=max(f[x],f[a[i].m]+1);
        g[x]+=max(f[a[i].m],g[a[i].m]);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        road(x,i);
    }
    dfs(1);
    printf("%d",max(f[1],g[1]));
    return 0;
}