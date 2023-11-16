#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,p=1,s1,s2,t[N],t0[N],f[N],b[N],c[N];
bool h[N];
struct road
{
    int m,q;
    ll r;
}a[N];
void road(int x,int y,ll r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[++p].m=x;
    a[p].q=t[y];
    t[y]=p;
    a[p].r=0;
}
bool bfs()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=s2;++i) f[i]=0;
    f[s1]=1;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[a[i].m]==0&&a[i].r!=0)
            {
                f[a[i].m]=f[k]+1;
                Q.push(a[i].m);
            }
        }
    }
    return f[s2]!=0;
}
ll dfs(int x,ll r)
{
    if(x==s2) return r;
    ll s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(f[a[i].m]==f[x]+1&&a[i].r!=0)
        {
            ll z=dfs(a[i].m,min(r,a[i].r));
            if(z!=0)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
            }
            else f[a[i].m]=0;
            if(r==0) return s;
        }
    }
    return s;
}
void dfs2(int x)
{
    h[x]=true;
    for(int i=t[x];i;i=a[i].q)
    {
        if(h[a[i].m]||a[i].r==0) continue;
        dfs2(a[i].m);
    }
}
namespace sgt
{
    struct tree
    {
        int l,r;
    }T[N<<2];
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        if(l==r)
        {
            road(m+x,s2,1);
            c[l]=m+x;
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        road(m+x,m+(x<<1),1e9);
        road(m+x,m+(x<<1|1),1e9);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            road(k,m+x,1e9);
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
    }
}
namespace TC
{
    int tot;
    vector<pair<int,int>> a[N];
    struct tree
    {
        int f,s,d,t,z,b;
    }T[N];
    void dfs1(int x)
    {
        T[x].s=1;
        T[x].d=T[T[x].f].d+1;
        for(auto i:a[x])
        {
            if(i.first==T[x].f) continue;
            T[i.first].f=x;
            dfs1(i.first);
            T[x].s+=T[i.first].s;
            if(T[i.first].s>T[T[x].z].s) T[x].z=i.first;
        }
    }
    void dfs2(int x,int k)
    {
        T[x].t=k;
        T[x].b=++tot;
        if(T[x].z) dfs2(T[x].z,k);
        for(auto i:a[x])
        {
            if(i.first==T[x].f||i.first==T[x].z) continue;
            dfs2(i.first,i.first);
        }
        for(auto i:a[x])
        {
            if(i.first==T[x].f) continue;
            b[T[i.first].b]=i.second;
        }
    }
    void solve(int x,int y,int k)
    {
        while(T[x].t!=T[y].t)
        {
            if(T[T[x].t].d>T[T[y].t].d)
            {
                sgt::add(1,T[T[x].t].b,T[x].b,k);
                x=T[T[x].t].f;
            }
            else
            {
                sgt::add(1,T[T[y].t].b,T[y].b,k);
                y=T[T[y].t].f;
            }
        }
        if(T[x].d<T[y].d)
        {
            sgt::add(1,T[x].b+1,T[y].b,k);
        }
        else
        {
            sgt::add(1,T[y].b+1,T[x].b,k);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    s1=m+n*4+1,s2=m+n*4+2;
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        TC::a[x].push_back(make_pair(y,i));
        TC::a[y].push_back(make_pair(x,i));
    }
    TC::dfs1(1);
    TC::dfs2(1,1);
    sgt::build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        TC::solve(x,y,i);
        road(s1,i,1);
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%lld\n",r);
    dfs2(s1);
    int z=0;
    for(int i=1;i<=m;++i)
    {
        if(h[i]==false) ++z;
    }
    printf("%d ",z);
    for(int i=1;i<=m;++i)
    {
        if(h[i]==false) printf("%d ",i);
    }
    printf("\n");
    z=0;
    for(int i=1;i<=n;++i)
    {
        if(h[c[i]]==true) ++z;
    }
    printf("%d ",z);
    for(int i=1;i<=n;++i)
    {
        if(h[c[i]]==true) printf("%d ",b[i]);
    }
    printf("\n");
    return 0;
}