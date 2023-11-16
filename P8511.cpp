#include<cstdio>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,c[N],fa[N];
ll b[N],g[N];
vector<int> a[N];
namespace sgt
{
    int tot=1,b[N<<6][2],c[N<<6],dx,dy;
    ll s;
    void clear()
    {
        tot=1;
        b[1][0]=b[1][1]=0;
        s=dx=dy=0;
    }
    void sum(ll x,int t)
    {
        int q=1;
        ll w=0;
        for(int i=60;i>=0;--i)
        {
            int z=(x&(1ll<<i))==0;
            if(b[q][z]!=0) q=b[q][z],w^=(1ll<<i);
            else q=b[q][z^1];
        }
        if(w>s)
        {
            s=w;
            dx=t;
            dy=c[q];
        }
    }
    void add(ll x,int t)
    {
        int q=1;
        for(int i=60;i>=0;--i)
        {
            int z=(x&(1ll<<i))!=0;
            if(b[q][z]==0)
            {
                b[q][z]=++tot;
                b[tot][0]=b[tot][1]=0;
            }
            q=b[q][z];
        }
        c[q]=t;
        sum(x,t);
    }
}
void dfs0(int x)
{
    for(auto i:a[x])
    {
        if(i==fa[x]) continue;
        fa[i]=x;
        dfs0(i);
    }
}
void dfs(int x)
{
    for(auto i:a[x])
    {
        if(i==fa[x]) continue;
        dfs(i);
    }
    sgt::add(b[x],x);
}
void dfs2(int x)
{
    sgt::add(b[x],x);
    for(auto i:a[x])
    {
        if(i==fa[x]||i==c[x]) continue;
        dfs(i);
    }
    if(c[x])
    {
        g[c[x]]=sgt::s;
        dfs2(c[x]);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        a[x].push_back(i);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    dfs0(1);
    sgt::clear();
    for(int i=1;i<=n;++i) sgt::add(b[i],i);
    int dx=sgt::dx,dy=sgt::dy;
    for(int i=1;i<=n;++i) g[i]=sgt::s;
    for(int i=1;i<=n;++i) c[i]=0;
    int z=dx;
    while(z!=1) c[fa[z]]=z,z=fa[z];
    sgt::clear();
    dfs2(1);
    for(int i=1;i<=n;++i) c[i]=0;
    z=dy;
    while(z!=1) c[fa[z]]=z,z=fa[z];
    sgt::clear();
    dfs2(1);
    g[1]=0;
    for(int i=1;i<=n;++i)
    {
        printf("%lld\n",g[i]);
    }
    return 0;
}