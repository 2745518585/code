#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,s1,tot,b[N],c[N],d[N],f[N],g[N],h[N],fa[N],ga[N];
vector<pair<int,int>> a[N];
vector<int> a1[N],a2[N],e[N];
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
    for(auto i:a1[x])
    {
        if(b[i]) continue;
        d[i]=x;
        dfs(i);
    }
}
void SPFA(int x)
{
    queue<int> Q;
    static ll f[N];
    static bool h[N];
    for(int i=1;i<=n;++i) f[i]=1e18,h[i]=false;
    f[x]=0,h[x]=true;
    Q.push(x);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(auto i:a[k])
        {
            if(f[k]+i.second<f[i.first])
            {
                f[i.first]=f[k]+i.second;
                h[i.first]=true;
                Q.push(i.first);
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(auto j:a[i])
        {
            if(f[i]+j.second==f[j.first])
            {
                a1[i].push_back(j.first);
                a2[j.first].push_back(i);
            }
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&s1);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    SPFA(s1);
    dfs(s1);
    b[0]=n+1;
    for(int i=1;i<=n;++i) c[b[i]]=i;
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=n;i>=1;--i)
    {
        if(c[i]==0) continue;
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
    int s=0;
    for(int i=1;i<=n;++i)
    {
        if(i!=s1&&b[i]!=0) s=max(s,h[i]);
    }
    printf("%d",s);
    return 0;
}