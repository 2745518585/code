#include<cstdio>
#include<algorithm>
using namespace std;
const int N=500001,M=21;
int n,m,tot,p=1,t[N],p2=1,t2[N],S[N],Top,fa[N][M],f[N],g1[N],g2[N],c[N];
bool h[N];
struct tree
{
    int f,s,d,t,z,b;
}T[N];
struct str
{
    int x,t;
}b[N];
struct road
{
    int m,q;
}a[N<<1];
struct road2
{
    int m,q;
}a2[N<<1];
bool cmp(str x,str y)
{
    return T[x.x].b<T[y.x].b;
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void road2(int x,int y)
{
    a2[++p2].m=y;
    a2[p2].q=t2[x];
    t2[x]=p2;
}
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        T[a[i].m].f=x;
        dfs1(a[i].m);
        T[x].s+=T[a[i].m].s;
        if(T[a[i].m].s>T[T[x].z].s) T[x].z=a[i].m;
    }
}
void dfs2(int x,int k)
{
    T[x].b=++tot;
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        else dfs2(a[i].m,a[i].m);
    }
}
int LCA(int x,int y)
{
    if(x==0||y==0) return 0;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d) x=T[T[x].t].f;
        else y=T[T[y].t].f;
    }
    if(T[x].d<T[y].d) return x;
    else return y;
}
bool check(int x,int y,int z)
{
    return g2[x]+T[x].d-T[z].d<g2[y]+T[z].d-T[y].d||(g2[x]+T[x].d-T[z].d==g2[y]+T[z].d-T[y].d&&g1[x]<g1[y]);
}
int find(int x,int y)
{
    int z=x,t=0;
    while(t>=0)
    {
        if(T[fa[z][t]].d>T[y].d) z=fa[z][t],++t;
        else --t;
    }
    return z;
}
void solve(int x,int y)
{
    int z=x,t=0;
    while(t>=0)
    {
        if(T[fa[z][t]].d>=T[y].d&&check(x,y,fa[z][t])) z=fa[z][t],++t;
        else --t;
    }
    int p=find(x,y);
    f[g1[x]]+=T[z].s-T[x].s;
    f[g1[y]]+=T[p].s-T[z].s;
}
void _dfs1(int x)
{
    if(h[x]==true) g1[x]=x,g2[x]=0;
    else g1[x]=0,g2[x]=1e9;
    for(int i=t2[x];i!=0;i=a2[i].q)
    {
        _dfs1(a2[i].m);
        int w=T[a2[i].m].d-T[x].d;
        if(g2[a2[i].m]+w<g2[x]||(g2[a2[i].m]+w==g2[x]&&g1[a2[i].m]<g1[x])) g1[x]=g1[a2[i].m],g2[x]=g2[a2[i].m]+w;
    }
}
void _dfs2(int x)
{
    int s=0;
    for(int i=t2[x];i!=0;i=a2[i].q)
    {
        int w=T[a2[i].m].d-T[x].d;
        if(g2[x]+w<g2[a2[i].m]||(g2[x]+w==g2[a2[i].m]&&g1[x]<g1[a2[i].m])) g1[a2[i].m]=g1[x],g2[a2[i].m]=g2[x]+w;
        _dfs2(a2[i].m);
        s+=T[find(a2[i].m,x)].s;
        solve(a2[i].m,x);
    }
    f[g1[x]]+=T[x].s-s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=n;++i) fa[i][0]=T[i].f;
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=n;++j)
        {
            fa[j][i]=fa[fa[j][i-1]][i-1];
        }
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int k;
        scanf("%d",&k);
        for(int j=1;j<=k;++j)
        {
            scanf("%d",&b[j].x);
            f[b[j].x]=0;
            b[j].t=j;
        }
        sort(b+1,b+k+1,cmp);
        p2=1;
        t2[1]=0;
        S[Top=1]=1;
        h[1]=false;
        for(int j=1;j<=k;++j)
        {
            if(b[j].x==1) continue;
            int z=LCA(b[j].x,S[Top]);
            while(Top>=1&&T[z].d<=T[S[Top-1]].d)
            {
                road2(S[Top-1],S[Top]);
                --Top;
                z=LCA(b[j].x,S[Top]);
            }
            t2[b[j].x]=0;
            h[b[j].x]=false;
            if(z==S[Top]) S[++Top]=b[j].x;
            else
            {
                t2[z]=0;
                h[z]=false;
                road2(z,S[Top]);
                S[Top]=z;
                S[++Top]=b[j].x;
            }
        }
        while(Top>=2)
        {
            road2(S[Top-1],S[Top]);
            --Top;
        }
        for(int j=1;j<=k;++j) h[b[j].x]=true;
        _dfs1(1);
        _dfs2(1);
        for(int j=1;j<=k;++j) c[b[j].t]=f[b[j].x];
        for(int j=1;j<=k;++j)
        {
            printf("%d ",c[j]);
        }
        printf("\n");
    }
    return 0;
}