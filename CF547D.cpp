#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,b1[N],b2[N],d[N];
struct point
{
    int x,y,t;
}a[N];
bool cmp(point a,point b)
{
    return a.x<b.x;
}
bool cmp2(point a,point b)
{
    return a.y<b.y;
}
void dfs(int x)
{
    if(d[b1[x]]==-1)
    {
        d[b1[x]]=d[x]^1;
        dfs(b1[x]);
    }
    if(d[b2[x]]==-1)
    {
        d[b2[x]]=d[x]^1;
        dfs(b2[x]);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].t=i;
    }
    sort(a+1,a+n+1,cmp);
    int x=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i].x!=a[i-1].x) x=0;
        if(x==0) x=i;
        else
        {
            b1[a[x].t]=a[i].t,b1[a[i].t]=a[x].t;
            x=0;
        }
    }
    sort(a+1,a+n+1,cmp2);
    x=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i].y!=a[i-1].y) x=0;
        if(x==0) x=i;
        else
        {
            b2[a[x].t]=a[i].t,b2[a[i].t]=a[x].t;
            x=0;
        }
    }
    for(int i=1;i<=n;++i) d[i]=-1;
    for(int i=1;i<=n;++i)
    {
        if(d[i]==-1)
        {
            d[i]=0;
            dfs(i);
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(d[i]==0) printf("r");
        else printf("b");
    }
    return 0;
}