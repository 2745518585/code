#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,b[N],g[N];
ll f[N];
vector<int> a[N];
struct str
{
    int x;
    ll s;
    str() {}
    str(int x,ll s):x(x),s(s) {}
    friend bool operator<(str a,str b)
    {
        return a.s<b.s;
    }
};
void dfs(int x)
{
    for(auto i:a[x])
    {
        dfs(i);
        if(f[i]>f[g[x]]) g[x]=i;
    }
    f[x]=f[g[x]]+b[x];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
    }
    dfs(1);
    priority_queue<str> Q;
    Q.push(str(1,f[1]));
    ll w=0;
    for(int i=1;i<=m;++i)
    {
        if(Q.empty()) break;
        int k=Q.top().x;
        Q.pop();
        w+=f[k];
        while(k)
        {
            for(auto i:a[k])
            {
                if(g[k]!=i) Q.push(str(i,f[i]));
            }
            k=g[k];
        }
    }
    printf("%lld",w);
    return 0;
}