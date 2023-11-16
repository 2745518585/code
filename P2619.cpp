#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,k,w;
struct road
{
    int x,y,w,c;
}a[N];
bool cmp(road a,road b)
{
    if(a.w!=b.w) return a.w<b.w;
    return a.c<b.c;
}
int fa[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int solve(int x)
{
    for(int i=1;i<=m;++i) if(a[i].c==0) a[i].w+=x;
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=n;++i) fa[i]=i;
    int s=0;
    w=0;
    for(int i=1;i<=m;++i)
    {
        if(find(a[i].x)!=find(a[i].y))
        {
            fa[find(a[i].x)]=find(a[i].y);
            s+=(a[i].c==0);
            w+=a[i].w;
        }
    }
    for(int i=1;i<=m;++i) if(a[i].c==0) a[i].w-=x;
    return s;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d%d",&a[i].x,&a[i].y,&a[i].w,&a[i].c);
        ++a[i].x,++a[i].y;
    }
    int l=-200,r=200;
    while(l<r)
    {
        int z=l+r+1>>1;
        if(solve(z)>=k) l=z;
        else r=z-1;
    }
    solve(l);
    printf("%d\n",w-l*k);
    return 0;
}