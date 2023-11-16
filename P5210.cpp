#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001,M=21;
int n,m,q,tot,b[N],b1[N],b2[N],fa[N][M];
ll c1[N],c2[N];
struct tree
{
    int l,r,f,d,b,bm;
}T[N<<2];
void build(int x,int l,int r)
{
    if(l==r)
    {
        b[l]=x;
        return;
    }
    int z;
    scanf("%d",&z);
    build(T[x].l=++q,l,z);
    build(T[x].r=++q,z+1,r);
}
void dfs(int x)
{
    T[x].b=++tot;
    if(T[x].l==0)
    {
        T[x].bm=tot;
        return;
    }
    T[T[x].l].f=x;
    T[T[x].r].f=x;
    T[T[x].l].d=T[x].d+1;
    T[T[x].r].d=T[x].d+1;
    b1[T[x].l]=b1[x]+1;
    b1[T[x].r]=b1[x];
    b2[T[x].l]=b2[x];
    b2[T[x].r]=b2[x]+1;
    c1[T[x].l]=c1[x]+(T[x].d+1);
    c1[T[x].r]=c1[x];
    c2[T[x].l]=c2[x];
    c2[T[x].r]=c2[x]+(T[x].d+1);
    dfs(T[x].l);
    dfs(T[x].r);
    T[x].bm=tot;
}
int LCA(int x,int y)
{
    if(T[x].d<T[y].d) swap(x,y);
    int t=0;
    while(t>=0)
    {
        if(T[fa[x][t]].d>=T[y].d) x=fa[x][t],++t;
        else --t;
    }
    if(x==y) return x;
    t=0;
    while(t>=0)
    {
        if(fa[x][t]!=fa[y][t]) x=fa[x][t],y=fa[y][t],++t;
        else --t;
    }
    return fa[x][0];
}
int main()
{
    scanf("%d",&n);
    build(++q,1,n);
    T[q+4].l=q+3;
    T[q+4].r=q+2;
    T[q+2].l=1;
    T[q+2].r=q+1;
    b[0]=q+3;
    b[n+1]=q+1;
    q+=4;
    T[q].d=1;
    dfs(q);
    for(int i=1;i<=q;++i) fa[i][0]=T[i].f;
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=q;++j)
        {
            fa[j][i]=fa[fa[j][i-1]][i-1];
        }
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int u,x,y;
        scanf("%d%d%d",&u,&x,&y);
        if(x==y)
        {
            printf("%lld\n",T[u].d+T[b[x]].d-T[LCA(u,b[x])].d*2);
            continue;
        }
        x=b[x-1],y=b[y+1];
        int z=LCA(x,y);
        ll s=(c1[x]-c1[T[z].l]+c2[y]-c2[T[z].r])+(ll)T[u].d*(b1[x]-b1[T[z].l]+b2[y]-b2[T[z].r]);
        if(T[u].b<=T[z].b||T[u].b>T[z].bm)
        {
            int p=LCA(u,z);
            s-=(ll)2*T[p].d*(b1[x]-b1[T[z].l]+b2[y]-b2[T[z].r]);
        }
        else if(T[u].b>=T[T[z].l].b&&T[u].b<=T[T[z].l].bm)
        {
            int p=LCA(u,x);
            s-=(ll)2*T[z].d*(b2[y]-b2[T[z].r]);
            s-=(ll)2*T[p].d*(b1[x]-b1[p]);
            s-=(ll)2*((c1[p]-c1[T[z].l])-(b1[p]-b1[T[z].l]));
            if(T[u].b>=T[T[p].r].b&&T[u].b<=T[T[p].r].bm) s-=2;
        }
        else
        {
            int p=LCA(u,y);
            s-=(ll)2*T[z].d*(b1[x]-b1[T[z].l]);
            s-=(ll)2*T[p].d*(b2[y]-b2[p]);
            s-=(ll)2*((c2[p]-c2[T[z].r])-(b2[p]-b2[T[z].r]));
            if(T[u].b>=T[T[p].l].b&&T[u].b<=T[T[p].l].bm) s-=2;
        }
        printf("%lld\n",s);
    }
    return 0;
}