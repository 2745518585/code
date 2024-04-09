#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001,M=21;
const ll P=1e9+7;
int n,m,b1[N],bm1[N],b2[N],bm2[N],d[N],f1[N][M],f2[N][M],g1[N][M],g2[N][M];
struct str
{
    int l,r;
}a[N];
vector<int> a1[N],a2[N];
vector<pair<int,int>> c1[N];
vector<pair<int,pair<int,int>>> c2[N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
namespace sgt1
{
    struct tree
    {
        int l,r,k;
    }T[N<<2];
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        T[x<<1].k=T[x<<1|1].k=T[x].k;
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].k=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
    }
    int sum(int x,int q)
    {
        if(T[x].l==T[x].r) return T[x].k;
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(q<=z) return sum(x<<1,q);
        else return sum(x<<1|1,q);
    }
}
namespace sgt2
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n*2) T[x]+=k,x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
    }
}
void dfs1(int x)
{
    static int tot=-1;
    b1[x]=++tot;
    for(auto i:a1[x]) dfs1(i);
    bm1[x]=++tot;
}
void dfs2(int x)
{
    static int tot=-1;
    b2[x]=++tot;
    for(auto i:a2[x]) dfs2(i);
    bm2[x]=++tot;
}
int find1(int x,int p)
{
    int t=0,s=0;
    while(t>=0)
    {
        if(f1[x][t]<p) s+=g1[x][t],x=f1[x][t],++t;
        else --t;
    }
    return s+g1[x][0];
}
int find2(int x,int p)
{
    int t=0,s=0;
    while(t>=0)
    {
        if(f2[x][t]<p) s+=g2[x][t],x=f2[x][t],++t;
        else --t;
    }
    return s+g2[x][0];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].l,&a[i].r);
    }
    sgt1::build(1,1,n*2);
    sgt1::add(1,1,n*2,n+1);
    for(int i=n;i>=1;--i)
    {
        int z1=sgt1::sum(1,a[i].l),z2=sgt1::sum(1,a[i].r);
        a1[z1].push_back(i);
        a2[z2].push_back(i);
        f1[i][0]=z1,f2[i][0]=z2;
        sgt1::add(1,a[i].l,a[i].r,i);
    }
    for(int i=1;i<=n*2;++i) sgt2::T[i]=0;
    for(int i=n;i>=1;--i)
    {
        sgt2::add(a[i].r,1);
        g1[i][0]+=sgt2::sum(a[i].l);
        for(auto j:a1[i]) g1[j][0]-=sgt2::sum(a[j].l);
    }
    for(int i=1;i<=n*2;++i) sgt2::T[i]=0;
    for(int i=n;i>=1;--i)
    {
        sgt2::add(n*2-a[i].l+1,1);
        g2[i][0]+=sgt2::sum(n*2-a[i].r+1);
        for(auto j:a2[i]) g2[j][0]-=sgt2::sum(n*2-a[j].r+1);
    }
    f1[n+1][0]=f2[n+1][0]=n+1;
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=n+1;++j)
        {
            f1[j][i]=f1[f1[j][i-1]][i-1];
            f2[j][i]=f2[f2[j][i-1]][i-1];
            g1[j][i]=g1[j][i-1]+g1[f1[j][i-1]][i-1];
            g2[j][i]=g2[j][i-1]+g2[f2[j][i-1]][i-1];
        }
    }
    dfs1(n+1);
    dfs2(n+1);
    for(int i=1;i<=n;++i)
    {
        c1[b1[i]].push_back(make_pair(b2[i],i));
        c2[b1[i]].push_back(make_pair(b2[i],make_pair(i,1)));
        c2[b1[i]].push_back(make_pair(bm2[i],make_pair(i,-1)));
        c2[bm1[i]].push_back(make_pair(b2[i],make_pair(i,-1)));
        c2[bm1[i]].push_back(make_pair(bm2[i],make_pair(i,1)));
    }
    for(int i=1;i<=n*2;++i) sgt2::T[i]=0;
    sgt2::add(1,n+1);
    for(int i=1;i<=n*2;++i)
    {
        for(auto j:c1[i])
        {
            d[j.second]=sgt2::sum(j.first);
        }
        for(auto j:c2[i])
        {
            sgt2::add(j.first,(j.second.first-d[j.second.first])*j.second.second);
        }
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        s=(s+inv(d[i]-i-find1(i,d[i])-find2(i,d[i])))%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}