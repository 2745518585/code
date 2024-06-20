#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,f[N][2],g[N][2];
vector<int> a[N];
void dfs1(int x,int fa)
{
    f[x][0]=0,f[x][1]=1;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs1(i,x);
        f[x][0]+=max(f[i][0],f[i][1]);
        f[x][1]+=f[i][0];
    }
}
void dfs2(int x,int fa)
{
    for(auto i:a[x])
    {
        if(i==fa) continue;
        g[i][0]=max(g[x][0]+f[x][0]-max(f[i][0],f[i][1]),g[x][1]+f[x][1]-f[i][0]);
        g[i][1]=g[x][0]+f[x][0]-max(f[i][0],f[i][1]);
        dfs2(i,x);
    }
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
        dfs1(1,0);
        g[1][0]=g[1][1]=0;
        dfs2(1,1);
        int s=0;
        for(int i=1;i<=n;++i)
        {
            s=max(s,max(f[i][0]+g[i][0],f[i][1]+g[i][1]));
            if(a[i].size()==1)
            {
                if(i==1) s=max(s,max(f[a[i][0]][0],f[a[i][0]][1])+1);
                else s=max(s,max(g[i][0],g[i][1])+1);
            }
        }
        printf("%d\n",s);
    }
    return 0;
}