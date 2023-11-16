#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int N=1000001;
int n,m,b[N][2],fa[N],ga[N],h[N];
bool g[N];
vector<int> d[N<<2];
int find(int x)
{
    if(fa[x]==x) return x;
    return find(fa[x]);
}
struct road
{
    int x,y;
    road(){}
    road(int x,int y):x(x),y(y){}
};
stack<road> S;
struct tree
{
    int l,r;
    vector<road> s;
}T[N<<2];
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,int l,int r,road k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s.push_back(k);
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
}
void dfs(int x)
{
    int p=S.size();
    for(auto i:T[x].s)
    {
        if(find(i.x)!=find(i.y))
        {
            int x=find(i.x),y=find(i.y);
            if(ga[x]<ga[y]) swap(x,y);
            fa[y]=x;
            ga[x]+=ga[y];
            S.push(road(x,y));
        }
    }
    if(T[x].l==T[x].r)
    {
        d[x].push_back(find(1));
    }
    else
    {
        dfs(x<<1);
        dfs(x<<1|1);
        for(auto i:d[x<<1]) d[x].push_back(i);
        for(auto i:d[x<<1|1]) d[x].push_back(i);
        vector<int>().swap(d[x<<1]);
        vector<int>().swap(d[x<<1|1]);
    }
    for(auto i:d[x]) h[i]=x;
    while(S.size()>p)
    {
        road k=S.top();
        S.pop();
        fa[k.y]=k.y;
        ga[k.x]-=ga[k.y];
        if(h[k.x]==x) d[x].push_back(k.y),h[k.y]=x;
    }
    sort(d[x].begin(),d[x].end());
    d[x].erase(unique(d[x].begin(),d[x].end()),d[x].end());
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&b[i][0],&b[i][1]);
    }
    build(1,1,2e5);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(1,b[x][0],b[x][1],road(x,n+i));
        add(1,b[y][0],b[y][1],road(y,n+i));
    }
    for(int i=1;i<=n+m;++i) fa[i]=i,ga[i]=1;
    dfs(1);
    for(auto i:d[1]) g[i]=true;
    for(int i=1;i<=n;++i)
    {
        if(g[i]) printf("%d ",i);
    }
    return 0;
}