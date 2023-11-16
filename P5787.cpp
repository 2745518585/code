#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int N=1000001;
int n,m,k,b[N],fa[N],ga[N];
struct road
{
    int x,y;
}a[N];
struct tree
{
    int l,r;
    vector<int> x;
}T[N<<2];
struct str
{
    int x,y,t;
};
stack<str> S;
int find(int x)
{
    if(fa[x]==x) return x;
    return find(fa[x]);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,int l,int r,int k)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].x.push_back(k);
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
    S.push((str){x,y,S.top().t+1});
}
void del()
{
    int x=S.top().x,y=S.top().y;
    S.pop();
    fa[y]=y;
    ga[x]-=ga[y];
}
void dfs(int x)
{
    int p=S.top().t;
    bool u=true;
    for(int i=0;i<T[x].x.size();++i)
    {
        road z=a[T[x].x[i]];
        if(find(z.x)==find(z.y))
        {
            u=false;
            break;
        }
        merge(z.x,z.y+n);
        merge(z.y,z.x+n);
    }
    if(u==true)
    {
        if(T[x].l==T[x].r) b[T[x].l]=true;
        else dfs(x<<1),dfs(x<<1|1);
    }
    while(S.top().t>p) del();
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    build(1,1,k);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d%d%d",&a[i].x,&a[i].y,&x,&y);
        add(1,x+1,y,i);
    }
    S.push((str){0,0,0});
    for(int i=1;i<=n*2;++i) fa[i]=i,ga[i]=1;
    dfs(1);
    for(int i=1;i<=k;++i)
    {
        if(b[i]) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}