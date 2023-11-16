// LUOGU_RID: 123761221
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,b[N],fa[N];
ll f[N],g[N];
bool h1[N],h2[N];
vector<int> a[N],c,t;
void dfs(int x)
{
    c.push_back(x);
    if(a[x].size()==1&&fa[x]!=0)
    {
        f[x]=b[x],g[x]=0;
        return;
    }
    ll w=0,q=0;
    for(auto i:a[x])
    {
        if(i==fa[x]) continue;
        fa[i]=x;
        dfs(i);
        w+=f[i];
        q=max(q,f[i]-g[i]);
    }
    f[x]=min(w-q+b[x],w);
    g[x]=w-q;
}
void dfs1(int x);
void dfs2(int x);
void dfs1(int x)
{
    if(a[x].size()==1&&fa[x]!=0)
    {
        t.push_back(x);
        return;
    }
    ll q=0;
    for(auto i:a[x])
    {
        if(i==fa[x]) continue;
        q=max(q,f[i]-g[i]);
    }
    if(b[x]>q) q=1e18;
    else if(b[x]==q)
    {
        for(auto i:a[x])
        {
            if(i==fa[x]) continue;
            h1[i]=true;
        }
        t.push_back(x);
    }
    else t.push_back(x);
    int u=0;
    for(auto i:a[x])
    {
        if(i==fa[x]) continue;
        if(f[i]-g[i]==q) h2[i]=true,++u;
        else h1[i]=true;
    }
    if(u>=2)
    {
        for(auto i:a[x])
        {
            if(i==fa[x]) continue;
            if(f[i]-g[i]==q) h1[i]=true;
        }
    }
}
void dfs2(int x)
{
    if(a[x].size()==1&&fa[x]!=0) return;
    ll q=0;
    for(auto i:a[x])
    {
        if(i==fa[x]) continue;
        q=max(q,f[i]-g[i]);
    }
    int u=0;
    for(auto i:a[x])
    {
        if(i==fa[x]) continue;
        if(f[i]-g[i]==q) h2[i]=true,++u;
        else h1[i]=true;
    }
    if(u>=2)
    {
        for(auto i:a[x])
        {
            if(i==fa[x]) continue;
            if(f[i]-g[i]==q) h1[i]=true;
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs(1);
    h1[1]=true;
    for(auto i:c)
    {
        if(h1[i]) dfs1(i);
        if(h2[i]) dfs2(i);
    }
    sort(t.begin(),t.end());
    t.erase(unique(t.begin(),t.end()),t.end());
    printf("%lld %d\n",f[1],t.size());
    for(auto i:t) printf("%d ",i);
    return 0;
}