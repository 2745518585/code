#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,n2,m,q,p=1,t[N],p2,fa[N],ga[N],f[N];
bool g[N],h[N];
struct tree
{
    int f,s,d,t,z,h;
}T[N];
struct road
{
    int m,q,w;
}a[N];
struct road2
{
    int x,y,w;
}a2[N];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void add(int x,int y,int w)
{
    int s=w,z=y;
    while(z!=x)
    {
        f[z]=s;
        s+=a[ga[z]].w;
        g[ga[z]]=g[ga[z]^1]=true;
        z=fa[z];
    }
    f[x]=0;
    ++n2;
    f[n2]=s;
    a2[++p2]=(road2){x,n2,0};
    z=y;
    int t=w;
    while(z!=x)
    {
        a2[++p2]=(road2){z,n2,min(t,s-t)};
        t+=a[ga[z]].w;
        z=fa[z];
    }
}
void dfs(int x)
{
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa[x]||g[i]==true) continue;
        if(h[a[i].m]==true)
        {
            add(a[i].m,x,a[i].w);
            g[i]=g[i^1]=true;
            continue;
        }
        fa[a[i].m]=x;
        ga[a[i].m]=i;
        dfs(a[i].m);
        if(g[i]==false) a2[++p2]=(road2){x,a[i].m,a[i].w};
    }
}
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        T[a[i].m].f=x;
        T[a[i].m].h=T[x].h+a[i].w;
        dfs1(a[i].m);
        T[x].s+=T[a[i].m].s;
        if(T[a[i].m].s>T[T[x].z].s) T[x].z=a[i].m;
    }
}
void dfs2(int x,int k)
{
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        else dfs2(a[i].m,a[i].m);
    }
}
int LCA(int x,int y,int &x2,int &y2)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d) x2=T[x].t,x=T[T[x].t].f;
        else y2=T[y].t,y=T[T[y].t].f;
    }
    if(T[x].d==T[y].d) return x;
    if(T[x].d<T[y].d)
    {
        y2=T[x].z;
        return x;
    }
    else
    {
        x2=T[y].z;
        return y;
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    n2=n;
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    dfs(1);
    p=1;
    for(int i=1;i<=n2;++i) t[i]=0;
    for(int i=1;i<=p2;++i)
    {
        road(a2[i].x,a2[i].y,a2[i].w);
        road(a2[i].y,a2[i].x,a2[i].w);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=q;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int x2=0,y2=0,z=LCA(x,y,x2,y2);
        if(z<=n) printf("%d\n",T[x].h+T[y].h-2*T[z].h);
        else printf("%d\n",T[x].h+T[y].h-T[x2].h-T[y2].h+min(abs(f[x2]-f[y2]),f[z]-abs(f[x2]-f[y2])));
    }
    return 0;
}