#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,q,rt,b[N],e[N],f[N];
bool g[N];
vector<int> a[N],c;
vector<pair<int,int>> c1[N],c2[N];
vector<pair<pair<int,int>,int>> d[N];
namespace sgt
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]+=k,x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
    }
}
struct tree
{
    int s,ms;
}T[N];
void dfs1(int x,int fa)
{
    T[x].s=1;
    T[x].ms=0;
    for(auto i:a[x])
    {
        if(i==fa||g[i]) continue;
        dfs1(i,x);
        T[x].s+=T[i].s;
        T[x].ms=max(T[x].ms,T[i].s);
    }
    T[x].ms=max(T[x].ms,q-T[x].s);
    if(T[x].ms<T[rt].ms) rt=x;
}
void dfs2(int x,int fa,int w1,int w2)
{
    w1=min(w1,x);
    w2=max(w2,x);
    c.push_back(x);
    c1[w1].push_back(make_pair(w2,b[x]));
    for(auto &i:d[x])
    {
        if(w1>=i.first.first&&w2<=i.first.second)
        {
            c.push_back(i.first.first);
            c.push_back(i.first.second);
            c2[i.first.first].push_back(make_pair(i.first.second,i.second));
            i.first.first=i.first.second=0;
        }
    }
    for(auto i:a[x])
    {
        if(i==fa||g[i]) continue;
        dfs2(i,x,w1,w2);
    }
}
void solve(int x)
{
    c.push_back(x);
    c1[x].push_back(make_pair(x,b[x]));
    for(auto i:d[x])
    {
        if(x>=i.first.first&&x<=i.first.second)
        {
            c.push_back(i.first.first);
            c.push_back(i.first.second);
            c2[i.first.first].push_back(make_pair(i.first.second,i.second));
            i.first.first=i.first.second=0;
        }
    }
    for(auto i:a[x])
    {
        if(g[i]) continue;
        dfs2(i,x,x,x);
    }
    sort(c.begin(),c.end(),[](int x,int y){return x>y;});
    c.resize(distance(c.begin(),unique(c.begin(),c.end())));
    for(auto i:c)
    {
        for(auto j:c1[i])
        {
            if(j.first<f[j.second])
            {
                sgt::add(f[j.second],-1);
                sgt::add(j.first,1);
                f[j.second]=j.first;
            }
        }
        for(auto j:c2[i])
        {
            e[j.second]=sgt::sum(j.first);
        }
    }
    for(auto i:c)
    {
        c1[i].clear();
        c2[i].clear();
        sgt::add(f[b[i]],-1);
        f[b[i]]=n+1;
    }
    c.clear();
}
void dfs(int x)
{
    rt=0;
    q=T[x].s;
    dfs1(x,0);
    solve(rt);
    g[rt]=true;
    for(auto i:a[rt])
    {
        if(g[i]) continue;
        dfs(i);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for(int i=1;i<=m;++i)
    {
        int x,l,r;
        scanf("%d%d%d",&l,&r,&x);
        d[x].push_back(make_pair(make_pair(l,r),i));
    }
    T[1].s=n;
    T[0].ms=1e9;
    for(int i=1;i<=n;++i) f[i]=n+1;
    dfs(1);
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",e[i]);
    }
    return 0;
}