#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,b[N],g[N];
ll a[N];
set<int> Set[N];
struct tree
{
    int l,r,w;
    ll s;
}T[N<<2];
ll find(int x,int l)
{
    if(l>=T[x].r) return 0;
    if(T[x].l==T[x].r) return a[T[x].l]-a[max(l,g[T[x].l])];
    int z=T[x].l+T[x].r>>1;
    if(l<=T[x<<1].w) return max(find(x<<1,l),T[x].s);
    else return max(a[z]-a[l],find(x<<1|1,l));
}
void pushup(int x)
{
    T[x].w=max(T[x<<1].w,T[x<<1|1].w);
    T[x].s=find(x<<1|1,T[x<<1].w);
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    if(l==r)
    {
        T[x].s=a[l]-a[g[l]];
        T[x].w=g[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=a[T[x].l]-a[g[T[x].l]];
        T[x].w=g[T[x].l];
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q);
    else add(x<<1|1,q);
    pushup(x);
}
ll sum(int x,int l,int r,int k)
{
    if(T[x].l>=l&&T[x].r<=r) return find(x,k);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s=max(s,sum(x<<1,l,r,k));
    if(r>z) s=max(s,sum(x<<1|1,l,r,max(k,T[x<<1].w)));
    return s;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        a[i]+=a[i-1];
    }
    for(int i=1;i<=m;++i) Set[i].insert(0);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        g[i]=*prev(Set[b[i]].end());
        Set[b[i]].insert(i);
    }
    build(1,1,n);
    for(int i=1;i<=q;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%lld\n",sum(1,l,r,l-1));
        }
        else if(z==2)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            auto p=Set[b[x]].find(x);
            if(next(p)!=Set[b[x]].end())
            {
                g[*next(p)]=g[x];
                add(1,*next(p));
            }
            Set[b[x]].erase(x);
            b[x]=k;
            Set[k].insert(x);
            p=Set[k].find(x);
            g[x]=*prev(p);
            add(1,x);
            if(next(p)!=Set[k].end())
            {
                g[*next(p)]=x;
                add(1,*next(p));
            }
        }
    }
    return 0;
}