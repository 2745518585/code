#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,w,q,p=1,t[N],b[N],c[N],d[N],f[N],l[N];
bool h[N];
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
    for(int i=t[x];i!=0;i=t[x])
    {
        t[x]=a[i].q;
        if(h[i]) continue;
        h[i]=h[i^1]=true;
        dfs(a[i].m);
    }
    f[++w]=x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        scanf("%d",&b[i]);
        d[i]=b[i];
    }
    for(int i=1;i<=n-1;++i)
    {
        scanf("%d",&c[i]);
        d[(n-1)+i]=c[i];
    }
    sort(d+1,d+(n-1)*2+1);
    q=unique(d+1,d+(n-1)*2+1)-d-1;
    for(int i=1;i<=n-1;++i)
    {
        if(b[i]>c[i])
        {
            printf("-1");
            return 0;
        }
        b[i]=lower_bound(d+1,d+q+1,b[i])-d;
        c[i]=lower_bound(d+1,d+q+1,c[i])-d;
        road(b[i],c[i]);
        road(c[i],b[i]);
        ++l[b[i]],++l[c[i]];
    }
    int p=1,u=0;
    for(int i=1;i<=q;++i)
    {
        if(l[i]%2==1) p=i,++u;
    }
    if(u!=0&&u!=2)
    {
        printf("-1");
        return 0;
    }
    dfs(p);
    if(w<n-1)
    {
        printf("-1");
        return 0;
    }
    for(int i=1;i<=w;++i) printf("%d ",d[f[i]]);
    return 0;
}