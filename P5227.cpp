#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
const int N=1000001;
int n,m,k,p=1,t[N<<2],a[N][2],c[N],fa[N],d[N];
bool g[N];
struct tree
{
    int l,r;
}T[N<<2];
struct road
{
    int m,q;
}b[N<<5];
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
void merge(int x,int y)
{
    x=find(x),y=find(y);
    if(x==y) return;
    if(d[x]>d[y]) swap(x,y);
    S.push((str){x,y,S.top().t+1});
    fa[x]=y;
    d[y]+=d[x];
}
void del()
{
    int x=S.top().x,y=S.top().y;
    S.pop();
    fa[x]=x;
    d[y]-=d[x];
}
void road(int x,int k)
{
    b[++p].m=k;
    b[p].q=t[x];
    t[x]=p;
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
    if(T[x].l>=l&&T[x].r<=r)
    {
        road(x,k);
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
}
void dfs(int x,int s)
{
    int z=S.top().t;
    for(int i=t[x];i!=0;i=b[i].q)
    {
        if(find(a[b[i].m][0])!=find(a[b[i].m][1]))
        {
            --s;
            merge(a[b[i].m][0],a[b[i].m][1]);
            if(s==1) break;
        }
    }
    if(s==1) for(int i=T[x].l;i<=T[x].r;++i) g[i]=true;
    else
    {
        if(T[x].l==T[x].r) g[T[x].l]=false;
        else
        {
            dfs(x<<1,s);
            dfs(x<<1|1,s);
        }
    }
    while(S.top().t>z)
    {
        del();
        ++s;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&a[i][0],&a[i][1]);
    }
    scanf("%d",&k);
    build(1,1,k+1);
    for(int i=1;i<=k;++i)
    {
        int q;
        scanf("%d",&q);
        for(int j=1;j<=q;++j)
        {
            int x;
            scanf("%d",&x);
            add(1,c[x]+1,i,x);
            c[x]=i+1;
        }
    }
    for(int i=1;i<=m;++i)
    {
        if(c[i]<k+1) add(1,c[i]+1,k+1,i);
    }
    for(int i=1;i<=n;++i) fa[i]=i,d[i]=1;
    S.push((str){0,0,0});
    dfs(1,n);
    for(int i=2;i<=k+1;++i)
    {
        if(g[i]==true) printf("Connected\n");
        else printf("Disconnected\n");
    }
    return 0;
}