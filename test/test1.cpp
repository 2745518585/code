#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,d[N],e[N];
ll f[N];
bool h[N];
vector<int> a[N],b[N];
void dfs(int x,int fa,int rt,int d)
{
    if(d>e[rt]) return;
    b[rt].push_back(x);
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x,rt,d+1);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&d[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&e[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for(int i=1;i<=n;++i)
    {
        dfs(i,0,i,0);
    }
    for(int i=1;i<=n;++i) f[i]=1e18;
    f[1]=d[1];
    h[1]=true;
    queue<int> Q;
    Q.push(1);
    while(!Q.empty()) 
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(auto i:b[k])
        {
            if(f[k]+d[k]<f[i])
            {
                f[i]=f[k]+d[k];
                h[i]=true;
                Q.push(i);
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%lld ",f[i]);
    }
    return 0;
}