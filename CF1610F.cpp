#include<cstdio>
#include<algorithm>
using namespace std;
const int N=3000001;
int n,m,p=1,t[N],l1[N],l2[N],b[N];
bool h[N];
struct road
{
    int m,q,k;
}a[N];
void road(int x,int y,int k)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].k=k;
}
void dfs(int x)
{
    for(int i=t[x];i!=0;i=t[x])
    {
        t[x]=a[i].q;
        if(h[i]) continue;
        h[i]=h[i^1]=true;
        b[abs(a[i].k)]=(a[i].k<0)+1;
        dfs(a[i].m);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        if(w==1)
        {
            ++l1[x],++l1[y];
            road(x,y,i);
            road(y,x,-i);
        }
        else
        {
            ++l2[x],++l2[y];
            road(x+n,y+n,i);
            road(y+n,x+n,-i);
        }
    }
    int w=0;
    for(int i=1;i<=n;++i)
    {
        if(l1[i]%2==1) ++w;
    }
    for(int i=1;i<=n;++i)
    {
        if(l1[i]%2==1&&l2[i]%2==1)
        {
            road(i,i+n,0);
            road(i+n,i,0);
        }
        else if(l1[i]%2==1)
        {
            road(i,n*2+1,0);
            road(n*2+1,i,0);
        }
        else if(l2[i]%2==1)
        {
            road(i+n,n*2+1,0);
            road(n*2+1,i+n,0);
        }
    }
    for(int i=1;i<=n*2+1;++i) dfs(i);
    printf("%d\n",w);
    for(int i=1;i<=m;++i)
    {
        printf("%d",b[i]);
    }
    return 0;
}