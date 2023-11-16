#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,f[N],fa[N];
bool g[N];
vector<int> a[N];
void dfs(int x)
{
    for(auto i:a[x])
    {
        if(i==fa[x]) continue;
        fa[i]=x;
        dfs(i);
        f[x]^=(f[i]+1);
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
    dfs(1);
    g[1]=true;
    int s=f[1],t=0;
    printf("%d",(s==0)+1);
    for(int i=2;i<=n;++i)
    {
        int x=i;
        while(!g[x])
        {
            s^=(f[x]+1)^f[x];
            g[x]=true;
            ++t;
            x=fa[x];
        }
        printf("%d",((s^(t%2))==0)+1);
    }
    return 0;
}