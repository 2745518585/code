#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
const int N=1000001;
int n,b[N],g[N],h[N];
struct tree
{
    int f,s,z;
}T[N];
vector<int> a[N];
set<int> f[N];
map<int,int> Map;
void dfs0(int x)
{
    T[x].s=1;
    for(auto i:a[x])
    {
        if(i==T[x].f) continue;
        T[i].f=x;
        dfs0(i);
        T[x].s+=T[i].s;
        if(T[i].s>T[T[x].z].s) T[x].z=i;
    }
}
void dfs(int x)
{
    if(a[x].size()-(T[x].f!=0)==0)
    {
        f[x].insert(b[x]);
        g[x]=h[x]=0;
        return;
    }
    dfs(T[x].z);
    g[x]+=g[T[x].z];
    for(auto i:a[x])
    {
        if(i==T[x].f||i==T[x].z) continue;
        dfs(i);
        g[x]+=g[i];
    }
    Map.clear();
    for(auto i:a[x])
    {
        if(i==T[x].f||i==T[x].z) continue;
        for(auto j:f[i]) ++Map[j^h[i]];
    }
    for(auto i:Map)
    {
        if(f[T[x].z].count(i.first^h[T[x].z])) ++Map[i.first];
    }
    int p=1;
    for(auto i:Map) p=max(p,i.second);
    g[x]+=(a[x].size()-(T[x].f!=0))-p;
    if(p>1)
    {
        for(auto i:Map)
        {
            if(i.second==p) f[x].insert(i.first);
        }
        h[x]=b[x];
    }
    else
    {
        for(auto i:Map) f[T[x].z].insert(i.first^h[T[x].z]);
        swap(f[T[x].z],f[x]);
        h[x]=h[T[x].z]^b[x];
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
    dfs0(1);
    dfs(1);
    printf("%lld",g[1]+(f[1].count(h[1])==0));
    return 0;
}