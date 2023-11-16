#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,s,p=1,t[N],f[N][2];
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
    int w=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        ++w;
    }
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        s=max(s,f[x][0]+max(f[a[i].m][0],f[a[i].m][1])+(w-2)+(fa!=0));
        s=max(s,f[x][1]+f[a[i].m][0]+1);
        f[x][0]=max(f[x][0],max(f[a[i].m][0],f[a[i].m][1]));
        f[x][1]=max(f[x][1],f[a[i].m][0]);
    }
    f[x][0]+=w-1;
    f[x][1]+=1;
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
    printf("%d",s);
    return 0;
}