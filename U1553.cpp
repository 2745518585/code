#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001,M=1000001;
int n,m,q=0,p=1,t[N],b[N],c[N];
bool d[N];
struct road
{
    int m,q;
}a[M];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int fa,int r)
{
    b[x]=c[x]=++q;
    int s=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(b[a[i].m]==0)
        {
            dfs(a[i].m,x,r);
            c[x]=min(c[x],c[a[i].m]);
            ++s;
            if(c[a[i].m]>=b[x]&&x!=r)
            {
                d[x]=true;
            }
        }
        c[x]=min(c[x],b[a[i].m]);
    }
    if(x==r&&s>=2) d[x]=true;
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
        if(b[i]==0)
        {
            dfs(i,0,i);
        }
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        if(d[i]==true) ++s;
    }
    printf("%d\n",s);
    for(int i=1;i<=n;++i)
    {
        if(d[i]==true)
        {
            printf("%d ",i);
        }
    }
    return 0;
}