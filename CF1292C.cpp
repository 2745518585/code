#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=3001;
int n,g[N][N],h[N][N];
ll f[N][N];
vector<int> a[N];
vector<pair<int,int>> b[N];
void dfs(int x,int fa,int rt,int t,int w)
{
    ++g[rt][t];
    h[rt][x]=t;
    b[w].push_back(make_pair(rt,x));
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x,rt,t,w+1);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for(int i=1;i<=n;++i)
    {
        for(auto j:a[i]) dfs(j,i,i,j,1);
    }
    for(int i=1;i<=n;++i) f[i][i]=0;
    for(int i=1;i<=n-1;++i)
    {
        for(auto j:b[i])
        {
            int x=j.first,y=j.second;
            f[x][y]=max(f[h[x][y]][y],f[x][h[y][x]])+(n-g[x][h[x][y]])*(n-g[y][h[y][x]]);
        }
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            s=max(s,f[i][j]);
        }
    }
    printf("%lld",s);
    return 0;
}