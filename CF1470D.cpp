#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,p=1,t[N],h[N];
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
void dfs(int x)
{
    if(h[x]==1)
    {
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(h[a[i].m]==1)
            {
                h[x]=-1;
                break;
            }
        }
    }
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]!=0) continue;
        h[a[i].m]=-h[x];
        dfs(a[i].m);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        p=1;
        for(int i=1;i<=n;++i) t[i]=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            road(x,y);
            road(y,x);
        }
        for(int i=1;i<=n;++i) h[i]=0;
        h[1]=1;
        dfs(1);
        bool u=false;
        for(int i=1;i<=n;++i)
        {
            if(h[i]==0)
            {
                u=true;
                break;
            }
        }
        if(u)
        {
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        int s=0;
        for(int i=1;i<=n;++i) if(h[i]==1) ++s;
        printf("%d\n",s);
        for(int i=1;i<=n;++i)
        {
            if(h[i]==1)
            {
                printf("%d ",i);
            }
        }
        printf("\n");
    }
    return 0;
}