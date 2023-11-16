#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001;
int n,m,s,p=1,t[N],a1[N][2],a2[N][2],fa[N],b1[N],b2[N];
struct road
{
    int m,q,k;
}a[N];
void road(int x,int y,int k)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].k=k;
}
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
namespace Solve1
{
    int q,b[N],fa[N];
    bool g[N],h[N],v;
    void check(int x,int y,int k)
    {
        b[++q]=k;
        g[x]=true;
        while(y!=x)
        {
            b[++q]=fa[y];
            g[y]=true;
            y=a[fa[y]^1].m;
        }
        v=true;
    }
    void dfs1(int x)
    {
        h[x]=true;
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if((i^1)==fa[x]) continue;
            if(h[a[i].m])
            {
                if(v==false) check(a[i].m,x,i);
                continue;
            }
            fa[a[i].m]=i;
            dfs1(a[i].m);
        }
    }
    bool dfs2(int x)
    {
        bool u=false;
        if(g[x]) u=true;
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if((i^1)==fa[x]||a[i].k==a[b[1]].k) continue;
            bool z=dfs2(a[i].m);
            if(!g[x]||!g[a[i].m])
            {
                if(z)
                {
                    if(a1[a[i].k][i%2]) ++s;
                }
                else
                {
                    if(a1[a[i].k][i%2^1]) ++s;
                }
            }
            u|=z;
        }
        return u;
    }
    void solve(int x)
    {
        v=false;
        q=0;
        dfs1(x);
        dfs2(x);
        int s0=0,s1=0,s2=0;
        if(q==1)
        {
            if(a1[a[b[1]].k][0]) ++s1,++s2;
        }
        else
        {
            for(int i=1;i<=q;++i)
            {
                if(a1[a[b[i]].k][0]&&a1[a[b[i]].k][1]) ++s0;
                else if(a1[a[b[i]].k][b[i]%2]) ++s1;
                else if(a1[a[b[i]].k][b[i]%2^1]) ++s2;
            }
        }
        s+=min((s0+s1+s2)/2,min(s0+s1,s0+s2));
    }
}
namespace Solve2
{
    int f[N],g[N],u,v;
    void dfs1(int x,int fa)
    {
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(a[i].m==fa) continue;
            f[a[i].m]=f[x];
            if(!a1[a[i].k][0]&&!a1[a[i].k][1]) ++u;
            if(a1[a[i].k][0]^a1[a[i].k][1])
            {
                if(a1[a[i].k][i%2]) --f[a[i].m],++u;
                else ++f[a[i].m];
            }
            dfs1(a[i].m,x);
        }
    }
    void dfs2(int x,int fa)
    {
        if(g[x]+f[x]>g[v]+f[v]) v=x;
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(a[i].m==fa) continue;
            g[a[i].m]=g[x]+(a1[a[i].k][0]&&a1[a[i].k][1]);
            dfs2(a[i].m,x);
        }
    }
    void solve(int x)
    {
        u=v=0;
        f[x]=0;
        dfs1(x,0);
        g[x]=0;
        dfs2(x,0);
        int z=v;
        g[v]=0;
        dfs2(v,0);
        s+=b1[x]-((g[v]+(f[v]+u)+(f[z]+u)+3)/2);
    }
}
void abc()
{
    s=0;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        a1[i][0]=a1[i][1]=0;
        int k;
        scanf("%d",&k);
        for(int j=0;j<=k-1;++j)
        {
            scanf("%d",&a1[i][j]);
        }
    }
    for(int i=1;i<=m;++i)
    {
        a2[i][0]=a2[i][1]=0;
        int k;
        scanf("%d",&k);
        for(int j=0;j<=k-1;++j)
        {
            scanf("%d",&a2[i][j]);
        }
        if(a2[i][1]==0) a2[i][1]=a2[i][0];
        bool u1=false,u2=false;
        if(a1[i][0]==a2[i][0]||a1[i][1]==a2[i][0]) u1=true;
        if(a2[i][1]!=0&&(a1[i][0]==a2[i][1]||a1[i][1]==a2[i][1])) u2=true;
        a1[i][0]=u1,a1[i][1]=u2;
    }
    p=1;
    for(int i=1;i<=n;++i) t[i]=0,fa[i]=i,b1[i]=1,b2[i]=0;
    for(int i=1;i<=m;++i)
    {
        road(a2[i][0],a2[i][1],i);
        road(a2[i][1],a2[i][0],i);
        int x=find(a2[i][0]),y=find(a2[i][1]);
        if(x!=y)
        {
            b1[x]+=b1[y];
            b2[x]+=b2[y]+1;
            fa[y]=x;
        }
        else ++b2[x];
    }
    for(int i=1;i<=n;++i)
    {
        if(find(i)==i&&b1[i]<b2[i])
        {
            printf("-1\n");
            return;
        }
    }
    for(int i=1;i<=n;++i) Solve1::g[i]=Solve1::h[i]=Solve1::fa[i]=Solve1::b[i]=0;
    for(int i=1;i<=n;++i)
    {
        if(find(i)==i)
        {
            if(b1[i]==b2[i]) Solve1::solve(i);
            else Solve2::solve(i);
        }
    }
    printf("%d\n",s);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}