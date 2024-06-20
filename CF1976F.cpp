#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,b[N];
vector<int> a[N];
int dfs(int x,int fa)
{
    int p=x;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        int z=dfs(i,x);
        if(b[z]>b[p]) p=z;
    }
    ++b[p];
    return p;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) a[i].clear();
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        for(int i=1;i<=n*2;++i) b[i]=0;
        dfs(1,0);
        sort(b+1,b+n+1,[](int x,int y){return x>y;});
        int w=n;
        for(int i=1;i<=n-1;++i)
        {
            w-=b[i*2-2]+b[i*2-1];
            printf("%d ",w);
        }
        printf("\n");
    }
    return 0;
}