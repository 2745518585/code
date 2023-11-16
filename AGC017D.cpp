#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,f[N];
vector<int> a[N];
void dfs(int x,int fa)
{
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x);
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
    dfs(1,0);
    if(f[1]!=0) printf("Alice\n");
    else printf("Bob\n");
    return 0;
}