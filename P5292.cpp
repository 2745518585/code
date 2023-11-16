#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=5001,M=1000001;
int n,m,q,h[N];
bool u,f[N][N];
char b[N];
vector<int> a[N];
vector<pair<int,int>> a0,a1,a2,a3;
void dfs(int x,int w)
{
    h[x]=w;
    for(auto i:a[x])
    {
        if(h[i]!=-1)
        {
            if(h[i]!=(w^1)) u=true;
            continue;
        }
        a0.push_back(make_pair(x,i));
        dfs(i,w^1);
    }
}
int main()
{
    scanf("%d%d%d%s",&n,&m,&q,b+1);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(b[x]=='1'&&b[y]=='1') a1.push_back(make_pair(x,y));
        else if(b[x]=='0'&&b[y]=='0') a2.push_back(make_pair(x,y));
        else a3.push_back(make_pair(x,y));
    }
    for(int i=1;i<=n;++i) h[i]=-1,a[i].clear();
    for(auto i:a1) a[i.first].push_back(i.second),a[i.second].push_back(i.first);
    for(int i=1;i<=n;++i)
    {
        if(h[i]==-1)
        {
            u=false;
            dfs(i,0);
            if(u) a0.push_back(make_pair(i,i));
        }
    }
    for(int i=1;i<=n;++i) h[i]=-1,a[i].clear();
    for(auto i:a2) a[i.first].push_back(i.second),a[i.second].push_back(i.first);
    for(int i=1;i<=n;++i)
    {
        if(h[i]==-1)
        {
            u=false;
            dfs(i,0);
            if(u) a0.push_back(make_pair(i,i));
        }
    }
    for(int i=1;i<=n;++i) h[i]=-1,a[i].clear();
    for(auto i:a3) a[i.first].push_back(i.second),a[i.second].push_back(i.first);
    for(int i=1;i<=n;++i)
    {
        if(h[i]==-1) dfs(i,0);
    }
    for(int i=1;i<=n;++i) a[i].clear();
    for(auto i:a0) a[i.first].push_back(i.second),a[i.second].push_back(i.first);
    queue<pair<int,int>> Q;
    for(int i=1;i<=n;++i) f[i][i]=true,Q.push(make_pair(i,i));
    for(int i=1;i<=n;++i)
    {
        for(auto j:a[i])
        {
            if(b[i]==b[j]) f[i][j]=true,Q.push(make_pair(i,j));
        }
    }
    while(!Q.empty())
    {
        auto k=Q.front();
        Q.pop();
        for(auto i:a[k.first])
        {
            for(auto j:a[k.second])
            {
                if(b[i]!=b[j]) continue;
                if(f[i][j]==false)
                {
                    f[i][j]=true;
                    Q.push(make_pair(i,j));
                }
            }
        }
    }
    for(int i=1;i<=q;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(f[x][y]) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}