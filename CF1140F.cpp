#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m=3e5,fa[N],ga[N],g1[N],g2[N];
ll b[N],s;
stack<pair<int,int>> S;
map<pair<int,int>,int> Map;
int find(int x)
{
    if(fa[x]==x) return x;
    return find(fa[x]);
}
struct tree
{
    int l,r;
    vector<pair<int,int>> k;
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
void add(int x,int l,int r,pair<int,int> k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k.push_back(k);
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
}
void merge(int x,int y)
{
    x=find(x),y=find(y);
    if(x==y) return;
    if(ga[x]<ga[y]) swap(x,y);
    s-=(ll)g1[x]*g2[x]+g1[y]*g2[y];
    fa[y]=x;
    ga[x]+=ga[y];
    g1[x]+=g1[y];
    g2[x]+=g2[y];
    S.push(make_pair(x,y));
    s+=(ll)g1[x]*g2[x];
}
void del()
{
    int x=S.top().first,y=S.top().second;
    s-=(ll)g1[x]*g2[x];
    S.pop();
    ga[x]-=ga[y];
    g1[x]-=g1[y];
    g2[x]-=g2[y];
    fa[y]=y;
    s+=(ll)g1[x]*g2[x]+g1[y]*g2[y];
}
void dfs(int x)
{
    int p=S.size();
    for(auto i:T[x].k)
    {
        merge(i.first,m+i.second);
    }
    if(T[x].l==T[x].r)
    {
        b[T[x].l]=s;
    }
    else
    {
        dfs(x<<1);
        dfs(x<<1|1);
    }
    while(S.size()>p) del();
}
int main()
{
    scanf("%d",&n);
    build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(!Map.count(make_pair(x,y)))
        {
            Map[make_pair(x,y)]=i;
        }
        else
        {
            add(1,Map[make_pair(x,y)],i-1,make_pair(x,y));
            Map.erase(make_pair(x,y));
        }
    }
    for(auto i:Map)
    {
        add(1,i.second,n,i.first);
    }
    for(int i=1;i<=m*2;++i) fa[i]=i,ga[i]=1;
    for(int i=1;i<=m;++i) g1[i]=1;
    for(int i=m+1;i<=m*2;++i) g2[i]=1;
    dfs(1);
    for(int i=1;i<=n;++i)
    {
        printf("%lld ",b[i]);
    }
    return 0;
}