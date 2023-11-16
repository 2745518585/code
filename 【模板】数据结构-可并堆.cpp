#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,fa[N];
bool h[N];
struct tree
{
    int x,l,r,d;
}T[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int merge(int x,int y)
{
    if(x==0||y==0) return x+y;
    if(T[x].x>T[y].x||(T[x].x==T[y].x&&x>y)) swap(x,y);
    T[x].r=merge(T[x].r,y);
    if(T[T[x].l].d<T[T[x].r].d) swap(T[x].l,T[x].r);
    T[x].d=T[T[x].r].d+1;
    return x;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&T[i].x);
        T[i].d=1;
        fa[i]=i;
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            if(h[x]||h[y]) continue;
            x=find(x),y=find(y);
            if(x==y) continue;
            fa[x]=fa[y]=merge(x,y);
        }
        else if(z==2)
        {
            int x;
            scanf("%d",&x);
            if(h[x])
            {
                printf("-1\n");
                continue;
            }
            x=find(x);
            printf("%d\n",T[x].x);
            h[x]=true;
            fa[x]=fa[T[x].l]=fa[T[x].r]=merge(T[x].l,T[x].r);
        }
    }
    return 0;
}