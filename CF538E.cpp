#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,p=1,t[N],f[N][2];
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
    if((fa==0&&t[x]==0)||(fa!=0&&a[t[x]].q==0))
    {
        f[x][0]=f[x][1]=1;
        ++m;
        return;
    }
    f[x][0]=1e9,f[x][1]=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        f[x][0]=min(f[x][0],f[a[i].m][1]);
        f[x][1]+=f[a[i].m][0];
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
    }
    dfs(1,0);
    printf("%d %d",m-f[1][0]+1,f[1][1]);
    return 0;
}