#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,p=0,t[100001],h[100001];
struct str
{
    int m,q;
}a[100001];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]==h[x])
        {
            printf("No");
            exit(0);
        }
        if(h[a[i].m]==-h[x]) continue;
        h[a[i].m]=-h[x];
        dfs(a[i].m);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=n;++i)
    {
        if(h[i]==0)
        {
            h[i]=1;
            dfs(i);
        }
    }
    printf("Yes");
    return 0;
}