#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n1,n2,m,g[N];
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
int main()
{
    scanf("%d%d%d",&n1,&n2,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
    }
    int s=0;
    for(int i=1;i<=n1;++i)
    {
        for(int j=1;j<=n2;++j) h[j]=false;
        if(dfs(i)) ++s;
    }
    printf("%d",s);
    return 0;
}