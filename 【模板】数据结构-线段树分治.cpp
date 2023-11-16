#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int N=1000001;
int n,m,k;
bool b[N];
struct road
{
    int x,y;
    road(){}
    road(int x,int y):x(x),y(y){}
};
stack<road> S;
int fa[N],ga[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return find(fa[x]);
}
struct tree
{
    int l,r;
    vector<road> k;
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
    fa[y]=x;
    ga[x]+=ga[y];
    S.push(road(x,y));
}
void del()
{
    int x=S.top().x,y=S.top().y;
    S.pop();
    ga[x]-=ga[y];
    fa[y]=y;
}
void dfs(int x)
{
    int p=S.size();
    bool u=true;
    for(auto i:T[x].k)
    {
        if(find(i.x)==find(i.y))
        {
            u=false;
            break;
        }
        merge(i.x,i.y+n);
        merge(i.y,i.x+n);
    }
    if(u==true)
    {
        if(T[x].l==T[x].r) b[T[x].l]=true;
        else dfs(x<<1),dfs(x<<1|1);
    }
    while(S.size()>p) del();
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    build(1,1,k);
    for(int i=1;i<=m;++i)
    {
        int x,y,l,r;
        scanf("%d%d%d%d",&x,&y,&l,&r);
        if(l<r) add(1,l+1,r,road(x,y));
    }
    for(int i=1;i<=n*2;++i) fa[i]=i,ga[i]=1;
    dfs(1);
    for(int i=1;i<=k;++i)
    {
        if(b[i]) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}