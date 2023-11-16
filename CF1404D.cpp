#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,b[N][2],f[N];
vector<int> a[N];
void dfs(int x,int w)
{
    f[x]=w;
    for(auto i:a[x])
    {
        if(f[i]!=0) continue;
        dfs(i,-w);
    }
}
int main()
{
    scanf("%d",&n);
    if(n%2==0)
    {
        printf("First\n");
        fflush(stdout);
        for(int i=1;i<=n;++i) printf("%d ",i);
        for(int i=1;i<=n;++i) printf("%d ",i);
        printf("\n");
        fflush(stdout);
        return 0;
    }
    printf("Second\n");
    fflush(stdout);
    for(int i=1;i<=n*2;++i)
    {
        int x;
        scanf("%d",&x);
        if(b[x][0]==0) b[x][0]=i;
        else b[x][1]=i;
    }
    for(int i=1;i<=n;++i)
    {
        a[b[i][0]].push_back(b[i][1]);
        a[b[i][1]].push_back(b[i][0]);
    }
    for(int i=1;i<=n;++i)
    {
        a[i].push_back(n+i);
        a[n+i].push_back(i);
    }
    for(int i=1;i<=n*2;++i)
    {
        if(f[i]==0) dfs(i,1);
    }
    int s=0;
    for(int i=1;i<=n*2;++i)
    {
        if(f[i]==1) s=(s+i)%(n*2);
    }
    if(s==0)
    {
        for(int i=1;i<=n*2;++i)
        {
            if(f[i]==1) printf("%d ",i);
        }
    }
    else
    {
        for(int i=1;i<=n*2;++i)
        {
            if(f[i]==-1) printf("%d ",i);
        }
    }
    printf("\n");
    fflush(stdout);
    return 0;
}