#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,p=1,t[N],b[N],s,r;
bool g[N],h[N];
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
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[i]) continue;
        if(h[a[i].m]==true)
        {
            ++s;
            if(r==0)
            {
                ++s;
                if(b[a[i].m]==a[i^1].m) r=a[i].m;
                else r=a[i^1].m;
            }
            if(b[a[i].m]==a[i^1].m) b[a[i].m]=r;
            else b[a[i^1].m]=r;
            g[i]=g[i^1]=true;
            continue;
        }
        dfs(a[i].m,x);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        road(i,b[i]);
        road(b[i],i);
        if(b[i]==i) r=i;
    }
    for(int i=1;i<=n;++i)
    {
        if(h[i]==0) dfs(i,0);
    }
    printf("%d\n",s-1);
    for(int i=1;i<=n;++i)
    {
        printf("%d ",b[i]);
    }
    return 0;
}