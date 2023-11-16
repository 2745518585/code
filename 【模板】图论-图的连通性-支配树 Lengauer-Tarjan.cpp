#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,tot,b[N],c[N],d[N],f[N],g[N],h[N],fa[N],ga[N];
vector<int> a[N],a2[N],e[N];
int dmin(int x,int y)
{
    return b[x]<b[y]?x:y;
}
int find(int x)
{
    if(fa[x]==x) return x;
    int z=find(fa[x]);
    if(b[g[ga[fa[x]]]]<b[g[ga[x]]]) ga[x]=ga[fa[x]];
    return fa[x]=z;
}
void dfs(int x)
{
    b[x]=++tot;
    for(auto i:a[x])
    {
        if(b[i]) continue;
        d[i]=x;
        dfs(i);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a2[y].push_back(x);
    }
    dfs(1);
    b[0]=n+1;
    for(int i=1;i<=n;++i) c[b[i]]=i;
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=n;i>=1;--i)
    {
        for(auto j:a2[c[i]])
        {
            if(b[j]==0) continue;
            if(b[j]<b[c[i]]) g[c[i]]=dmin(g[c[i]],j);
            else
            {
                find(j);
                g[c[i]]=dmin(g[c[i]],g[ga[j]]);
            }
        }
        e[g[c[i]]].push_back(c[i]);
        for(auto j:e[c[i]])
        {
            find(j);
            if(g[ga[j]]==c[i]) f[j]=c[i];
            else f[j]=-ga[j];
        }
        fa[c[i]]=d[c[i]];
        ga[c[i]]=c[i];
    }
    for(int i=2;i<=n;++i)
    {
        if(f[c[i]]<0) f[c[i]]=f[-f[c[i]]];
    }
    for(int i=1;i<=n;++i) h[i]=1;
    for(int i=n;i>=2;--i)
    {
        h[f[c[i]]]+=h[c[i]];
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d ",h[i]);
    }
    return 0;
}