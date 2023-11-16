#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1501;
int n,p=1,t[N],f[N][2];
bool b[N];
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
void dfs(int x,int fa)
{
    f[x][0]=0;
    f[x][1]=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        f[x][1]+=min(f[a[i].m][0],f[a[i].m][1]);
        f[x][0]+=f[a[i].m][1];
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x,q;
        scanf("%d%d",&x,&q);
        for(int j=1;j<=q;++j)
        {
            int y;
            scanf("%d",&y);
            road(x+1,y+1);
            b[y+1]=true;
        }
    }
    int r;
    for(int i=1;i<=n;++i)
    {
        if(!b[i])
        {
            r=i;
            break;
        }
    }
    dfs(r,0);
    printf("%d",min(f[r][0],f[r][1]));
    return 0;
}