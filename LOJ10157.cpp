#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1501;
int n,p=1,t[N],f[N][3],b[N];
bool h[N];
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
    f[x][1]=b[x];
    f[x][2]=0;
    int s=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        f[x][2]+=min(f[a[i].m][0],f[a[i].m][1]);
        f[x][1]+=min(f[a[i].m][0],min(f[a[i].m][1],f[a[i].m][2]));
        if(f[a[i].m][1]<f[a[i].m][0])
        {
            f[x][0]+=f[a[i].m][1];
            ++s;
        }
        else f[x][0]+=f[a[i].m][0];
    }
    if(s==0)
    {
        int w=1e9;
        for(int i=t[x];i!=0;i=a[i].q)
        {
            w=min(w,f[a[i].m][1]-f[a[i].m][0]);
        }
        f[x][0]+=w;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x,q;
        scanf("%d",&x);
        scanf("%d%d",&b[x],&q);
        for(int j=1;j<=q;++j)
        {
            int y;
            scanf("%d",&y);
            road(x,y);
            h[y]=true;
        }
    }
    int r;
    for(int i=1;i<=n;++i)
    {
        if(!h[i])
        {
            r=i;
            break;
        }
    }
    dfs(r,0);
    printf("%d",min(f[r][0],f[r][1]));
    return 0;
}