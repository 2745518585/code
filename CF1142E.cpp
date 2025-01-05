#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int N=1000001;
int n,m,l[N];
bool g[N],h[N];
vector<int> a[N],b[N];
int query(int x,int y)
{
    printf("? %d %d\n",x,y);
    fflush(stdout);
    int z;
    scanf("%d",&z);
    return z;
}
void dfs(int x)
{
    g[x]=h[x]=true;
    for(auto i:a[x])
    {
        if(!h[i]) b[x].push_back(i);
        if(!g[i]) dfs(i);
    }
    h[x]=false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
    }
    for(int i=1;i<=n;++i)
    {
        if(!g[i]) dfs(i);
    }
    for(int i=1;i<=n;++i)
    {
        for(auto j:b[i]) ++l[j];
    }
    stack<int> Q;
    for(int i=1;i<=n;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(Q.size()>1)
    {
        int x=Q.top();
        Q.pop();
        int y=Q.top();
        Q.pop();
        if(!query(x,y)) swap(x,y);
        Q.push(x);
        for(auto i:b[y])
        {
            --l[i];
            if(l[i]==0) Q.push(i);
        }
    }
    printf("! %d\n",Q.top());
    fflush(stdout);
    return 0;
}