#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=5001;
int n,m,d[N],e[N],f[N][N];
ll b[N],p[N];
vector<int> a[N],e1,e2;
vector<pair<int,int>> g[N][N];
namespace match
{
    int n,g[N];
    bool h[N];
    vector<int> a[N];
    bool dfs(int x)
    {
        for(auto i:a[x])
        {
            if(h[i]) continue;
            h[i]=true;
            if(g[i]==0||dfs(g[i]))
            {
                g[i]=x;
                return true;
            }
        }
        return false;
    }
    bool solve()
    {
        for(int i=1;i<=n;++i) g[i]=0;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j) h[j]=false;
            if(!dfs(i)) return false;
        }
        return true;
    }
}
void solve(int x,int t)
{
    if(f[x][t]!=-1) return;
    int q=a[x].size(),w=q?(d[x]-1)/q:0;
    for(auto i:a[x])
    {
        for(int j=t+1;j<=t+d[x]-1;j+=w) solve(i,j);
    }
    match::n=q;
    for(int i=1;i<=q;++i) match::a[i].clear();
    for(int i=1;i<=q;++i)
    {
        int z=a[x][i-1];
        for(int j=1;j<=q;++j)
        {
            if(f[z][t+(j-1)*w+1]&&(b[z]==p[t+(j-1)*w+1]||b[x]+b[z]==p[t+(j-1)*w+1]||p[t]+b[z]==p[t+(j-1)*w+1]))
            {
                match::a[i].push_back(j);
            }
        }
    }
    f[x][t]=match::solve();
    if(f[x][t])
    {
        for(int i=1;i<=q;++i)
        {
            g[x][t].push_back(make_pair(a[x][match::g[i]-1],t+(i-1)*w+1));
        }
    }
}
void dfs(int x,int t)
{
    e[t]=x;
    for(auto i:g[x][t])
    {
        dfs(i.first,i.second);
        if(b[i.first]==p[i.second]);
        else if(b[x]+b[i.first]==p[i.second]) e1.push_back(i.first);
        else e2.push_back(i.first);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d%lld",&x,&b[i]);
        a[x].push_back(i);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&p[i]);
    }
    for(int i=n;i>=1;--i)
    {
        d[i]=1;
        for(auto j:a[i]) d[i]+=d[j];
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) f[i][j]=-1;
    }
    solve(1,1);
    dfs(1,1);
    printf("%d\n",e1.size()+e2.size());
    for(auto i:e1) printf("%d ",i);
    reverse(e2.begin(),e2.end());
    for(auto i:e2) printf("%d ",i);
    printf("\n");
    for(int i=1;i<=n;++i)
    {
        printf("%d ",e[i]);
    }
    return 0;
}