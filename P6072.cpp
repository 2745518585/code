#include<cstdio>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
const int N=1000001;
int n,m,b[N],c[N],f[N],g[N];
vector<pair<int,int>> a[N];
namespace sgt
{
    int tot=1,b[N][2],c[N],s,dx,dy;
    void clear()
    {
        tot=1;
        b[1][0]=b[1][1]=0;
        s=dx=dy=0;
    }
    void sum(int x,int t)
    {
        int q=1,w=0;
        for(int i=30;i>=0;--i)
        {
            int z=(x&(1<<i))==0;
            if(b[q][z]!=0) q=b[q][z],w^=(1<<i);
            else q=b[q][z^1];
        }
        if(w>s)
        {
            s=w;
            dx=t;
            dy=c[q];
        }
    }
    void add(int x,int t)
    {
        int q=1;
        for(int i=30;i>=0;--i)
        {
            int z=(x&(1<<i))!=0;
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
struct tree
{
    int f,s,z;
}T[N];
void dfs0(int x)
{
    T[x].s=1;
    for(auto i:a[x])
    {
        if(i.first==T[x].f) continue;
        T[i.first].f=x;
        b[i.first]=b[x]^i.second;
        dfs0(i.first);
        T[x].s+=T[i.first].s;
        if(T[i.first].s>T[T[x].z].z) T[x].z=i.first;
    }
}
void dfs(int x)
{
    for(auto i:a[x])
    {
        if(i.first==T[x].f) continue;
        dfs(i.first);
    }
    sgt::add(b[x],x);
}
void dfs1(int x)
{
    for(auto i:a[x])
    {
        if(i.first==T[x].f||i.first==T[x].z) continue;
        dfs1(i.first);
        sgt::clear();
    }
    if(T[x].z) dfs1(T[x].z);
    for(auto i:a[x])
    {
        if(i.first==T[x].f||i.first==T[x].z) continue;
        dfs(i.first);
    }
    sgt::add(b[x],x);
    f[x]=sgt::s;
}
void dfs2(int x)
{
    sgt::add(b[x],x);
    for(auto i:a[x])
    {
        if(i.first==T[x].f||i.first==c[x]) continue;
        dfs(i.first);
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
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    dfs0(1);
    dfs1(1);
    sgt::clear();
    for(int i=1;i<=n;++i) sgt::add(b[i],i);
    int dx=sgt::dx,dy=sgt::dy;
    for(int i=1;i<=n;++i) g[i]=sgt::s;
    for(int i=1;i<=n;++i) c[i]=0;
    int z=dx;
    while(z!=1) c[T[z].f]=z,z=T[z].f;
    sgt::clear();
    dfs2(1);
    for(int i=1;i<=n;++i) c[i]=0;
    z=dy;
    while(z!=1) c[T[z].f]=z,z=T[z].f;
    sgt::clear();
    dfs2(1);
    int s=0;
    for(int i=2;i<=n;++i) s=max(s,f[i]+g[i]);
    printf("%d",s);
    return 0;
}