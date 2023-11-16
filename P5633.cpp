#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,m1,m2,p,k,w;
struct road
{
    int x,y,w;
}a1[N],a2[N];
bool cmp(road a,road b)
{
    if(a.w!=b.w) return a.w<b.w;
    return (a.x==p||a.y==p)>(b.x==p||b.y==p);
}
int fa[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int solve(int x)
{
    for(int i=1;i<=m1;++i) a1[i].w+=x;
    for(int i=1;i<=n;++i) fa[i]=i;
    int s=0;
    w=0;
    int x1=1,x2=1;
    for(int i=1;i<=m;++i)
    {
        road z;
        if(x1<=m1&&(x2>m2||cmp(a1[x1],a2[x2]))) z=a1[x1++];
        else z=a2[x2++];
        if(find(z.x)!=find(z.y))
        {
            fa[find(z.x)]=find(z.y);
            s+=(z.x==p||z.y==p);
            w+=z.w;
        }
    }
    for(int i=1;i<=m1;++i) a1[i].w-=x;
    return s;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&p,&k);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        if(x==p||y==p) a1[++m1]=(road){x,y,w};
        else a2[++m2]=(road){x,y,w};
    }
    if(m1<k)
    {
        printf("Impossible");
        return 0;
    }
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=m2;++i)
    {
        if(find(a2[i].x)!=find(a2[i].y)) fa[find(a2[i].x)]=find(a2[i].y);
    }
    int u=0;
    for(int i=1;i<=m1;++i)
    {
        if(u<k&&find(a1[i].x)!=find(a1[i].y))
        {
            ++u;
            fa[find(a1[i].x)]=find(a1[i].y);
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(find(i)!=find(1))
        {
            printf("Impossible");
            return 0;
        }
    }
    sort(a1+1,a1+m1+1,cmp);
    sort(a2+1,a2+m2+1,cmp);
    int l=-50000,r=50000;
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