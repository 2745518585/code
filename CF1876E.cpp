#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int N=1000001;
int n,q,f[N],g[N],d[N];
vector<pair<int,int>> a[N];
vector<pair<pair<int,int>,int>> ans;
stack<int> S;
void dfs1(int x,int fa)
{
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        d[i.first]=d[x]+i.second;
        dfs1(i.first,x);
        f[x]+=f[i.first];
        if(i.second>=0) ++f[x];
    }
}
void dfs2(int x,int fa)
{
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        g[i.first]=g[x]+f[x]-(f[i.first]+(i.second>=0))+(i.second<=0);
        dfs2(i.first,x);
    }
}
void dfs3(int x,int fa)
{
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        int z=0;
        if(i.second>=0) S.push(++q),ans.push_back(make_pair(make_pair(x,i.first),z=q));
        else ans.push_back(make_pair(make_pair(i.first,x),z=S.top())),S.pop();
        dfs3(i.first,x);
        if(i.second>=0) S.pop();
        else S.push(z);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,-w));
    }
    dfs1(1,0);
    dfs2(1,0);
    int x=1;
    for(int i=1;i<=n;++i)
    {
        if(d[i]<d[x]) x=i;
    }
    dfs3(x,0);
    printf("%d\n",q);
    for(auto i:ans) printf("%d %d %d\n",i.first.first,i.first.second,i.second);
    return 0;
}