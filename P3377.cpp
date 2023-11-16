#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m;
bool h[N];
struct tree
{
    int x,l,r,d,f;
}T[N];
int findrt(int x)
{
    if(T[x].f==x) return x;
    return T[x].f=findrt(T[x].f);
}
int merge(int x,int y)
{
    if(x==0) return y;
    if(y==0) return x;
    if(T[x].x>T[y].x) swap(x,y);
    T[x].r=merge(T[x].r,y);
    if(T[T[x].l].d<T[T[x].r].d) swap(T[x].l,T[x].r);
    T[x].d=T[T[x].r].d+1;
    return x;
}
int main()
{
    h[0]=-1;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) T[i].f=i;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&T[i].x);
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            if(h[x]==true||h[y]==true) continue;
            x=findrt(x),y=findrt(y);
            if(x==y) continue;
            T[x].f=T[y].f=merge(x,y);
        }
        else if(z==2)
        {
            int x;
            scanf("%d",&x);
            if(h[x]==true)
            {
                printf("-1\n");
                continue;
            }
            x=findrt(x);
            printf("%d\n",T[x].x);
            h[x]=true;
            T[x].f=T[T[x].l].f=T[T[x].r].f=merge(T[x].l,T[x].r);
            T[x].l=T[x].r=T[x].d=0;
        }
    }
    return 0;
}