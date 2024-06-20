#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,tot;
ll f[N],g[N],e[N];
char b[N];
vector<int> a[N];
struct tree
{
    int b,bm;
}T[N];
struct str
{
    int x,w;
    str():x(0),w(-1e9) {}
    str(int x,int w):x(x),w(w) {}
}h1[N],h2[N];
str max(str a,str b)
{
    return a.w>b.w?a:b;
}
namespace sgt
{
    struct tree
    {
        int l,r,k;
        str s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=max(T[x<<1].s,T[x<<1|1].s);
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        T[x<<1].s.w+=T[x].k;
        T[x<<1].k+=T[x].k;
        T[x<<1|1].s.w+=T[x].k;
        T[x<<1|1].k+=T[x].k;
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add1(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s.w+=k;
            T[x].k+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add1(x<<1,l,r,k);
        if(r>z) add1(x<<1|1,l,r,k);
        pushup(x);
    }
    void add2(int x,int q,str k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add2(x<<1,q,k);
        else add2(x<<1|1,q,k);
        pushup(x);
    }
    str sum(int x,int l,int r)
    {
        if(l>r) return str();
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        str s;
        if(l<=z) s=max(s,sum(x<<1,l,r));
        if(r>z) s=max(s,sum(x<<1|1,l,r));
        return s;
    }
}
void dfs1(int x,int fa)
{
    T[x].b=++tot;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs1(i,x);
        sgt::add2(1,T[i].b,str(i,0));
        if(b[i]=='0')
        {
            h1[i]=sgt::sum(1,T[i].b,T[i].bm);
            sgt::add2(1,T[h1[i].x].b,str());
            f[i]+=h1[i].w;
        }
        sgt::add1(1,T[i].b,T[i].bm,1);
        f[x]+=f[i];
    }
    T[x].bm=tot;
}
void dfs2(int x,int fa)
{
    e[x]=g[x];
    if(b[x]=='0'&&sgt::T[1].s.x!=0) e[x]+=sgt::T[1].s.w;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        g[i]=g[x];
        sgt::add2(1,T[x].b,str(x,0));
        if(b[x]=='0')
        {
            h2[i]=max(sgt::sum(1,1,T[i].b-1),sgt::sum(1,T[i].bm+1,n));
            sgt::add2(1,T[h2[i].x].b,str());
            g[i]+=h2[i].w;
        }
        sgt::add1(1,1,n,1);
        sgt::add1(1,T[i].b,T[i].bm,-2);
        if(b[i]=='0')
        {
            sgt::add2(1,T[h1[i].x].b,h1[i]);
            g[i]-=h1[i].w;
        }
        sgt::add2(1,T[i].b,str());
        dfs2(i,x);
        sgt::add2(1,T[i].b,str(i,0));
        if(b[i]=='0') sgt::add2(1,T[h1[i].x].b,str());
        sgt::add1(1,1,n,-1);
        sgt::add1(1,T[i].b,T[i].bm,2);
        if(b[x]=='0') sgt::add2(1,T[h2[i].x].b,h2[i]);
        sgt::add2(1,T[x].b,str());
    }
}
int main()
{
    scanf("%d%s",&n,b+1);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    sgt::build(1,1,n);
    dfs1(1,0);
    g[1]=f[1];
    dfs2(1,0);
    for(int i=1;i<=n;++i)
    {
        printf("%lld ",e[i]);
    }
    return 0;
}