#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int N=1000001,M=61;
int n,m,k,q,b[N],c[N],d[N],fa[M][N],ga[M][N];
bool h[N];
struct road
{
    int x,y;
}a[N];
struct node
{
    int x,k,t;
    node(){}
    node(int x,int k,int t):x(x),k(k),t(t){}
};
struct tree
{
    int l,r;
    vector<node> x;
}T[N<<2];
struct str
{
    int x,y,k,t;
    str(){}
    str(int x,int y,int k,int t):x(x),y(y),k(k),t(t){}
};
stack<str> S;
int find(int x,int k)
{
    if(fa[k][x]==x) return x;
    return find(fa[k][x],k);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,int l,int r,node k)
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
void merge(int x,int y,int k)
{
    x=find(x,k),y=find(y,k);
    if(x==y) return;
    if(ga[x]<ga[y]) swap(x,y);
    fa[k][y]=x;
    ga[k][x]+=ga[k][y];
    S.push(str(x,y,k,S.top().t+1));
}
void del()
{
    int x=S.top().x,y=S.top().y,k=S.top().k;
    S.pop();
    fa[k][y]=y;
    ga[k][x]-=ga[k][y];
}
void dfs(int x)
{
    int p=S.top().t;
    printf("%d %d\n",T[x].l,T[x].r);
    for(auto i:T[x].x)
    {
        road z=a[i.x];
        printf("*%d %d %d %d %d\n",i.t,z.x,z.y,find(z.x,i.k),find(z.y,i.k));
        if(h[i.t]==false) i.k=b[i.x];
        else b[i.x]=i.k;
        merge(z.x,z.y+n,i.k);
        merge(z.y,z.x+n,i.k);
    }
    if(T[x].l==T[x].r)
    {
        if(T[x].l!=q)
        {
            int t=x;
            while(t!=1&&t%2==1) t/=2;
            while(true)
            {
                for(auto i:T[t].x)
                {
                    road z=a[i.x];
                    printf("#%d %d %d %d %d\n",i.t,z.x,z.y,find(z.x,i.k),find(z.y,i.k));
                    if(find(z.x,i.k)==find(z.y,i.k)) h[i.t]=false;
                }
                if(T[t].l==T[t].r) break;
                t*=2;
            }
        }
    }
    else
    {
        dfs(x<<1);
        dfs(x<<1|1);
    }
    while(S.top().t>p) del();
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&k,&q);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    build(1,1,q);
    for(int i=1;i<=q;++i)
    {
        int x,k;
        scanf("%d%d",&x,&k);
        if(c[x]!=0)
        {
            add(1,c[x],i-1,node(x,d[x],c[x]));
        }
        c[x]=i;
        d[x]=k;
    }
    for(int i=1;i<=m;++i)
    {
        if(c[i]!=0)
        {
            add(1,c[i],q,node(i,d[i],c[i]));
        }
    }
    S.push(str(0,0,0,0));
    for(int i=1;i<=k;++i)
    {
        for(int j=1;j<=n*2;++j) fa[i][j]=j,ga[i][j]=1;
    }
    for(int i=1;i<=q;++i) h[i]=true;
    dfs(1);
    for(int i=1;i<=q;++i)
    {
        if(h[i]) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}