#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
typedef unsigned long long ull;
const int N=1001;
int n,m,rt;
ull f[N],g[N],s,b[N];
vector<int> a[N];
map<ull,int> Map;
void dfs1(int x)
{
    f[x]=10007;
    for(auto i:a[x])
    {
        dfs1(i);
        f[x]+=(f[i]*(f[i]+1)+1);
    }
}
void dfs2(int x)
{
    for(auto i:a[x])
    {
        g[i]=(x==rt?0:(g[x]*(g[x]+1)+1))+f[x]-(f[i]*(f[i]+1)+1);
        dfs2(i);
    }
}
ull solve()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) a[i].clear();
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        if(x==0) rt=i;
        else a[x].push_back(i);
    }
    dfs1(rt);
    g[rt]=0;
    dfs2(rt);
    s=0;
    for(int i=1;i<=n;++i) s=max(s,f[i]+(i==rt?0:(g[i]*(g[i]+1)+1)));
    return s;
}
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        b[i]=solve();
        if(!Map.count(b[i])) Map[b[i]]=i;
        else Map[b[i]]=min(Map[b[i]],i);
    }
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",Map[b[i]]);
    }
    return 0;
}