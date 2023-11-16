#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=4000001,M=21;
int n,n2,m,p=1,t[N],t2[N];
ll s=-1e18;
struct road
{
    int m,q;
    ll w;
}a[N];
void road(int x,int y,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void road2(int x,int y,ll w)
{
    a[++p].m=y;
    a[p].q=t2[x];
    t2[x]=p;
    a[p].w=w;
}
struct tree
{
    int f,s,ms,c;
    ll h,xh;
}T[N];
namespace lca
{
    int tot,p=1,t[N],b[N][M],c[N],lg[N];
    struct tree
    {
        int f,s,d,t,z,b;
        ll h;
    }T[N];
    struct road
    {
        int m,q;
        ll w;
    }a[N];
    void road(int x,int y,ll w)
    {
        a[++p].m=y;
        a[p].q=t[x];
        t[x]=p;
        a[p].w=w;
    }
    int dmin(int x,int y)
    {
        return T[x].d<T[y].d?x:y;
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
        T[x].b=++tot;
        if(T[x].z) dfs2(T[x].z,k);
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
            dfs2(a[i].m,a[i].m);
        }
    }
    int LCA(int x,int y)
    {
        while(T[x].t!=T[y].t)
        {
            if(T[T[x].t].d>T[T[y].t].d) x=T[T[x].t].f;
            else y=T[T[y].t].f;
        }
        if(T[x].d<T[y].d) return x;
        else return y;
    }
    int sum(int x,int y)
    {
        x=T[x].b,y=T[y].b;
        if(x>y) swap(x,y);
        int t=lg[y-x];
        return dmin(b[x][t],b[y-(1<<t)][t]);
    }
    void init()
    {
        dfs1(1);
        dfs2(1,1);
        for(int i=1;i<=n;++i) c[T[i].b]=i;
        for(int i=1;i<=n-1;++i) b[i][0]=LCA(c[i],c[i+1]);
        for(int i=0;i<=20;++i)
        {
            for(int j=(1<<i);j<=(1<<(i+1))-1;++j) lg[j]=i;
        }
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n-1;++j)
            {
                b[j][i]=dmin(b[j][i-1],b[j+(1<<(i-1))][i-1]);
            }
        }
    }
}
namespace vt
{
    int n,p=1,t[N],b[N],S[N],Top,f[N][2];
    ll g[N];
    bool h[N];
    struct road
    {
        int m,q;
    }a[N];
    void road(int x,int y)
    {
        a[++p].m=y;
        a[p].q=t[x];
        t[x]=p;
    }
    int dmax(int x,int y)
    {
        return g[x]>g[y]?x:y;
    }
    void dfs(int x)
    {
        if(h[x])
        {
            f[x][0]=x;
            f[x][1]=0;
        }
        else f[x][0]=f[x][1]=0;
        for(int i=t[x];i;i=a[i].q)
        {
            dfs(a[i].m);
            if(T[f[x][0]].c!=T[f[a[i].m][0]].c)
            {
                s=max(s,g[f[x][0]]+g[f[a[i].m][0]]-lca::T[x].h*2);
            }
            else
            {
                s=max(s,g[f[x][0]]+g[f[a[i].m][1]]-lca::T[x].h*2);
                s=max(s,g[f[x][1]]+g[f[a[i].m][0]]-lca::T[x].h*2);
            }
            if(g[f[a[i].m][0]]>g[f[x][0]])
            {
                if(T[f[x][0]].c!=T[f[a[i].m][0]].c) f[x][1]=f[x][0];
                f[x][0]=f[a[i].m][0];
                if(T[f[a[i].m][1]].c!=T[f[x][0]].c) f[x][1]=dmax(f[x][1],f[a[i].m][1]);
            }
            else
            {
                if(T[f[a[i].m][0]].c!=T[f[x][0]].c) f[x][1]=dmax(f[x][1],f[a[i].m][0]);
                else if(T[f[a[i].m][1]].c!=T[f[x][0]].c) f[x][1]=dmax(f[x][1],f[a[i].m][1]);
            }
        }
    }
    void solve()
    {
        for(int i=1;i<=n;++i) h[b[i]]=true;
        p=1;
        t[1]=0;
        S[Top=1]=1;
        S[0]=0;
        for(int i=1;i<=n;++i)
        {
            if(b[i]==1) continue;
            int z=lca::sum(b[i],S[Top]);
            while(Top>=1&&lca::T[z].d<=lca::T[S[Top-1]].d)
            {
                road(S[Top-1],S[Top]);
                --Top;
                z=lca::sum(b[i],S[Top]);
            }
            t[b[i]]=0;
            if(z!=S[Top])
            {
                t[z]=0;
                h[z]=false;
                road(z,S[Top]);
                S[Top]=z;
            }
            S[++Top]=b[i];
        }
        while(Top>=2)
        {
            road(S[Top-1],S[Top]);
            --Top;
        }
        g[0]=-1e18;
        dfs(1);
    }
}
namespace pwt
{
    int b[N],c[N],d[N],*f[N],f2[N];
    bool g[N];
    void dfs(int x,int c)
    {
        T[x].c=c;
        for(int i=t[x];i;i=a[i].q)
        {
            if(a[i].m==T[x].f||g[a[i].m]) continue;
            T[a[i].m].f=x;
            T[a[i].m].h=T[x].h+a[i].w;
            dfs(a[i].m,c);
        }
    }
    void solve(int x)
    {
        T[x].f=0;
        T[x].c=x;
        d[x]=1;
        for(int i=t[x];i;i=a[i].q)
        {
            if(g[a[i].m]) continue;
            T[a[i].m].f=x;
            T[a[i].m].h=a[i].w;
            dfs(a[i].m,a[i].m);
            d[x]+=d[c[i/2]];
        }
        f[x]=new int[d[x]+1];
        d[x]=0;
        if(x<=n) f[x][++d[x]]=x;
        for(int i=t[x];i;i=a[i].q)
        {
            if(g[a[i].m]) continue;
            int z1=1,z2=1;
            for(int j=1;j<=d[x]+d[c[i/2]];++j)
            {
                if(z1<=d[x]&&(z2>d[c[i/2]]||lca::T[f[x][z1]].b<lca::T[f[c[i/2]][z2]].b)) f2[j]=f[x][z1],++z1;
                else f2[j]=f[c[i/2]][z2],++z2;
            }
            delete[] f[c[i/2]];
            d[x]+=d[c[i/2]];
            for(int i=1;i<=d[x];++i) f[x][i]=f2[i];
        }
        vt::n=d[x];
        for(int i=1;i<=d[x];++i)
        {
            vt::b[i]=f[x][i];
            vt::g[f[x][i]]=T[f[x][i]].h+T[f[x][i]].xh;
        }
        vt::solve();
    }
    void main()
    {
        for(int i=1;i<=n2;++i) g[i]=true;
        for(int i=n2;i>=1;--i)
        {
            g[b[i]]=false;
            solve(b[i]);
        }
    }
}
namespace bpwt
{
    int sz,rt,q;
    bool g[N];
    void dfs1(int x)
    {
        T[x].s=1;
        T[x].ms=0;
        for(int i=t[x];i;i=a[i].q)
        {
            if(a[i].m==T[x].f||g[a[i].m]) continue;
            T[a[i].m].f=x;
            dfs1(a[i].m);
            T[x].s+=T[a[i].m].s;
            T[x].ms=max(T[x].ms,T[a[i].m].s);
        }
        T[x].ms=max(T[x].ms,sz-T[x].s);
        if(T[x].ms<T[rt].ms) rt=x;
    }
    void dfs2(int x)
    {
        T[x].s=1;
        for(int i=t[x];i;i=a[i].q)
        {
            if(a[i].m==T[x].f||g[a[i].m]) continue;
            T[a[i].m].f=x;
            dfs2(a[i].m);
            T[x].s+=T[a[i].m].s;
        }
    }
    int dfs(int x)
    {
        sz=T[x].s;
        rt=0;
        T[x].f=0;
        dfs1(x);
        T[rt].f=0;
        dfs2(rt);
        pwt::b[++q]=rt;
        g[rt]=true;
        int z=rt;
        for(int i=t[rt];i;i=a[i].q)
        {
            if(g[a[i].m]) continue;
            pwt::c[i/2]=dfs(a[i].m);
        }
        return z;
    }
}
void rebuild(int x,int fa)
{
    int z=0;
    for(int i=t2[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(z==0)
        {
            road(x,a[i].m,a[i].w);
            road(a[i].m,x,a[i].w);
            z=x;
        }
        else
        {
            ++n2;
            road(z,n2,0);
            road(n2,z,0);
            road(n2,a[i].m,a[i].w);
            road(a[i].m,n2,a[i].w);
            z=n2;
        }
        rebuild(a[i].m,x);
    }
}
void dfs(int x,int fa)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        T[a[i].m].xh=T[x].xh+a[i].w;
        dfs(a[i].m,x);
    }
}
int main()
{
    scanf("%d",&n);
    n2=n;
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        road2(x,y,w);
        road2(y,x,w);
    }
    rebuild(1,0);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        lca::road(x,y,w);
        lca::road(y,x,w);
    }
    dfs(1,0);
    lca::init();
    T[0].ms=1e9;
    T[1].s=n2;
    bpwt::dfs(1);
    pwt::main();
    for(int i=1;i<=n;++i) s=max(s,(T[i].xh-lca::T[i].h)*2);
    printf("%lld",s/2);
    return 0;
}