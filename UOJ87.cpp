#include<cstdio>
#include<algorithm>
#include<vector>
#include<utility>
#include<map>
using namespace std;
typedef long long ll;
const int N=1000001,M=21;
int n,m,q,fa[N][M];
ll f[N],g[N],s;
bool h[N];
vector<int> a[N];
namespace Tree_chain
{
    int p=1,t[N];
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
}
namespace rstree
{
    int p=1,t[N],fa[N];
    bool h[N],h2[N];
    struct road
    {
        int m,q,w;
    }a[N];
    void road(int x,int y,int w)
    {
        a[++p].m=y;
        a[p].q=t[x];
        t[x]=p;
        a[p].w=w;
    }
    void add(int x,int y,int w)
    {
        int z=y;
        ll s=w;
        while(z!=x)
        {
            g[z]=s;
            s+=a[fa[z]].w;
            h2[fa[z]]=h2[fa[z]^1]=true;
            z=a[fa[z]^1].m;
        }
        ++q;
        g[q]=s;
        Tree_chain::road(x,q,0);
        Tree_chain::road(q,x,0);
        z=y;
        ll t=w;
        while(z!=x)
        {
            Tree_chain::road(z,q,min(t,s-t));
            Tree_chain::road(q,z,min(t,s-t));
            t+=a[fa[z]].w;
            z=a[fa[z]^1].m;
        }
    }
    void dfs(int x)
    {
        h[x]=true;
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(i==(fa[x]^1)||h2[i]==true) continue;
            if(h[a[i].m]==true)
            {
                add(a[i].m,x,a[i].w);
                h2[i]=h2[i^1]=true;
                continue;
            }
            fa[a[i].m]=i;
            dfs(a[i].m);
            if(h2[i]==false)
            {
                Tree_chain::road(x,a[i].m,a[i].w);
                Tree_chain::road(a[i].m,x,a[i].w);
            }
        }
    }
}
struct tree
{
    int f,s,d,t,z,b;
    ll h;
}T[N];
namespace Tree_chain
{
    int tot;
    void dfs1(int x)
    {
        T[x].s=1;
        T[x].d=T[T[x].f].d+1;
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(a[i].m==T[x].f) continue;
            T[a[i].m].f=x;
            T[a[i].m].h=T[x].h+a[i].w;
            ::a[x].push_back(a[i].m);
            dfs1(a[i].m);
            T[x].s+=T[a[i].m].s;
            if(T[a[i].m].s>T[T[x].z].s) T[x].z=a[i].m;
        }
    }
    void dfs2(int x,int k)
    {
        T[x].t=k;
        T[x].b=++tot;
        if(T[x].z!=0) dfs2(T[x].z,k);
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
            else dfs2(a[i].m,a[i].m);
        }
    }
    int LCA(int x,int y)
    {
        while(T[x].t!=T[y].t)
        {
            if(T[T[x].t].d>=T[T[y].t].d) x=T[T[x].t].f;
            else y=T[T[y].t].f;
        }
        if(T[x].d<T[y].d) return x;
        else return y;
    }
}
bool cmp(int x,int y)
{
    return T[x].b<T[y].b;
}
bool cmp2(int x,int y)
{
    return g[x]<g[y];
}
int find(int x,int y)
{
    int t=0;
    while(t>=0)
    {
        if(T[fa[x][t]].d>T[y].d) x=fa[x][t],++t;
        else --t;
    }
    return x;
}
void dfs(int x)
{
    f[x]=0;
    if(!h[x]) f[x]=-1e18;
    for(auto i:a[x])
    {
        dfs(i);
        f[x]=max(f[x],f[i]+(T[i].h-T[x].h));
    }
    if(h[x]) s=max(s,f[x]);
    if(x<=n)
    {
        ll w=-1e18;
        for(auto i:a[x])
        {
            s=max(s,w+f[i]+(T[i].h-T[x].h));
            w=max(w,f[i]+(T[i].h-T[x].h));
        }
        return;
    }
    int n=a[x].size();
    int *b=new int[n*2+10],*Q=new int[n*2+10];
    ll *c=new ll[n*2+10];
    for(int i=1;i<=n;++i) b[i]=find(a[x][i-1],x),f[b[i]]=f[a[x][i-1]]+(T[a[x][i-1]].h-T[b[i]].h);
    sort(b+1,b+n+1,cmp2);
    int T=1,R=0;
    for(int i=1;i<=n;++i) b[n+i]=b[i],c[i]=g[b[i]],c[n+i]=g[x]+g[b[i]];
    for(int i=1;i<=n*2;++i)
    {
        while(T<=R&&c[i]-c[Q[T]]>g[x]/2) ++T;
        if(T<=R) s=max(s,f[b[i]]+f[b[Q[T]]]+(c[i]-c[Q[T]]));
        while(T<=R&&f[b[Q[R]]]-c[Q[R]]<=f[b[i]]-c[i]) --R;
        Q[++R]=i;
    }
    delete[] b;
    delete[] c;
    delete[] Q;
}
int main()
{
    scanf("%d%d",&n,&m);
    q=n;
    map<pair<int,int>,int> Map;
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        if(x>y) swap(x,y);
        if(!Map.count(make_pair(x,y))) Map[make_pair(x,y)]=w;
        else Map[make_pair(x,y)]=min(Map[make_pair(x,y)],w);
    }
    for(auto i:Map)
    {
        rstree::road(i.first.first,i.first.second,i.second);
        rstree::road(i.first.second,i.first.first,i.second);
    }
    rstree::dfs(1);
    Tree_chain::dfs1(1);
    Tree_chain::dfs2(1,1);
    for(int i=1;i<=q;++i) fa[i][0]=T[i].f;
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=q;++j) fa[j][i]=fa[fa[j][i-1]][i-1];
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int k;
        scanf("%d",&k);
        int *b=new int[k+10],*S=new int[k+10],Top=0;
        for(int j=1;j<=k;++j)
        {
            scanf("%d",&b[j]);
        }
        sort(b+1,b+k+1,cmp);
        k=unique(b+1,b+k+1)-b-1;
        a[1].clear();
        h[1]=false;
        S[0]=0;
        S[Top=1]=1;
        for(int j=1;j<=k;++j)
        {
            if(b[j]==1) continue;
            int z=Tree_chain::LCA(b[j],S[Top]);
            while(Top>=1&&T[z].d<=T[S[Top-1]].d)
            {
                a[S[Top-1]].push_back(S[Top]);
                h[S[Top-1]]=false;
                --Top;
                z=Tree_chain::LCA(b[j],S[Top]);
            }
            a[b[j]].clear();
            if(z!=S[Top])
            {
                a[z].clear();
                h[z]=false;
                a[z].push_back(S[Top]);
                S[Top]=z;
            }
            S[++Top]=b[j];
        }
        while(Top>=2)
        {
            a[S[Top-1]].push_back(S[Top]);
            --Top;
        }
        for(int j=1;j<=k;++j) h[b[j]]=true;
        s=0;
        dfs(1);
        printf("%lld\n",s);
        delete[] b;
        delete[] S;
    }
    return 0;
}