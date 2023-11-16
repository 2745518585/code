#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001,M=21;
int n,m,d[N],g[M];
bool f[N][M];
vector<int> a[N];
void dfs(int x,int fa)
{
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x);
    }
    for(int i=0;i<=20;++i) g[i]=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        for(int j=0;j<=20;++j) g[j]+=f[i][j];
    }
    d[x]=0;
    for(int i=0;i<=20;++i)
    {
        if(g[i]>=2) d[x]=i+1;
    }
    while(g[d[x]]!=0) ++d[x];
    for(int i=d[x];i<=20;++i)
    {
        if(g[i]!=0) f[x][i]=true;
    }
    f[x][d[x]]=true;
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
    int s=0;
    for(int i=1;i<=n;++i) s=max(s,d[i]);
    printf("%d",s);
    return 0;
}