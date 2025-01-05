#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=3000001;
int n,m,q,tot;
bool g[N],h[N];
vector<pair<int,int>> a[N];
struct tree
{
    int b,c;
}T[N];
void dfs(int x,int fa)
{
    T[x].b=T[x].c=++tot;
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        if(T[i.first].b==0)
        {
            dfs(i.first,x);
            T[x].c=min(T[x].c,T[i.first].c);
            if(T[i.first].c>T[x].b) g[i.second]=true;
        }
        T[x].c=min(T[x].c,T[i.first].b);
    }
}
void dfs2(int x,vector<int> &p)
{
    h[x]=true;
    p.push_back(x);
    for(auto i:a[x])
    {
        if(h[i.first]||g[i.second]) continue;
        dfs2(i.first,p);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(make_pair(y,i));
        a[y].push_back(make_pair(x,i));
    }
    for(int i=1;i<=n;++i)
    {
        if(T[i].b==0) dfs(i,0);
    }
    for(int i=1;i<=n;++i)
    {
        if(h[i]) continue;
        vector<int> p;
        dfs2(i,p);
        ++q;
    }
    printf("%d\n",q);
    for(int i=1;i<=n;++i) h[i]=false;
    for(int i=1;i<=n;++i)
    {
        if(h[i]) continue;
        vector<int> p;
        dfs2(i,p);
        printf("%d ",p.size());
        for(auto j:p) printf("%d ",j);
        printf("\n");
    }
    return 0;
}