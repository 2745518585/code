#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=1000001;
int n,fa[N];
bool g[N],h[N];
vector<int> a[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int dfs(int x)
{
    if(g[x]) return 0;
    if(h[x]) return x;
    h[x]=true;
    int z=0;
    while(true)
    {
        if(a[x].empty())
        {
            g[x]=true;
            break;
        }
        int t=a[x].back();
        a[x].pop_back();
        z=dfs(t);
        if(z==0)
        {
            fa[find(x)]=find(t);
            g[x]=true;
            break;
        }
        if(z!=x) break;
        z=0;
    }
    h[x]=false;
    return z;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int k;
        scanf("%d",&k);
        for(int j=1;j<=k;++j)
        {
            int x;
            scanf("%d",&x);
            a[i].push_back(x);
        }
    }
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=n;++i)
    {
        if(!g[i]) dfs(i);
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d ",find(i));
    }
    return 0;
}