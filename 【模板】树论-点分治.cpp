#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,q,rt,b[N];
bool e[N],g[N],h[20000001];
vector<pair<int,int>> a[N];
struct tree
{
    int s,ms;
}T[N];
void dfs0(int x,int fa)
{
    ++q;
    for(auto i:a[x])
    {
        if(i.first==fa||g[i.first]) continue;
        dfs0(i.first,x);
    }
}
void dfs1(int x,int fa)
{
    T[x].s=1;
    T[x].ms=0;
    for(auto i:a[x])
    {
        if(i.first==fa||g[i.first]) continue;
        dfs1(i.first,x);
        T[x].s+=T[i.first].s;
        T[x].ms=max(T[x].ms,T[i.first].s);
    }
    T[x].ms=max(T[x].ms,q-T[x].s);
    if(T[x].ms<T[rt].ms) rt=x;
}
void dfs2(int x,int fa,int w,vector<int> &p)
{
    if(w>1e7) return;
    p.push_back(w);
    for(auto i:a[x])
    {
        if(i.first==fa||g[i.first]) continue;
        dfs2(i.first,x,w+i.second,p);
    }
}
void solve(int x)
{
    vector<int> p1,p2;
    h[0]=true;
    for(auto i:a[x])
    {
        if(g[i.first]) continue;
        dfs2(i.first,x,i.second,p1);
        for(auto j:p1)
        {
            for(int k=1;k<=m;++k)
            {
                if(j<=b[k]&&h[b[k]-j]) e[k]=true;
            }
        }
        for(auto j:p1)
        {
            h[j]=true;
            p2.push_back(j);
        }
        p1.clear();
    }
    for(auto i:p2) h[i]=false;
}
void dfs(int x)
{
    q=0;
    dfs0(x,0);
    rt=0;
    dfs1(x,0);
    solve(rt);
    g[rt]=true;
    for(auto i:a[rt])
    {
        if(g[i.first]) continue;
        dfs(i.first);
    }
}
int main()
{
    T[0].ms=1e9;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&b[i]);
    }
    dfs(1);
    for(int i=1;i<=m;++i)
    {
        if(e[i]) printf("AYE\n");
        else printf("NAY\n");
    }
    return 0;
}