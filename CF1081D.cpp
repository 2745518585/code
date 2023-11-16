#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,k,fa[N];
bool h[N];
struct road
{
    int x,y,w;
}a[N];
bool cmp(road a,road b)
{
    return a.w<b.w;
}
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;++i)
    {
        int x;
        scanf("%d",&x);
        h[x]=true;
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w);
    }
    sort(a+1,a+m+1,cmp);
    int s=0;
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=m;++i)
    {
        if(find(a[i].x)!=find(a[i].y))
        {
            if(h[find(a[i].x)]&&h[find(a[i].y)]) ++s;
            if(h[find(a[i].x)]) fa[find(a[i].y)]=find(a[i].x);
            else fa[find(a[i].x)]=find(a[i].y);
            if(s==k-1)
            {
                for(int j=1;j<=k;++j) printf("%d ",a[i].w);
                return 0;
            }
        }
    }
    return 0;
}