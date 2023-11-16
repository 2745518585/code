#include<cstdio>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,a[N],b[N];
ll d[N];
vector<pair<int,int>> c[N];
struct tree
{
    int l,r;
    ll s,k;
}T[N<<2];
void pushup(int x)
{
    T[x].s=min(T[x<<1].s,T[x<<1|1].s);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].s+=T[x].k;
    T[x<<1].k+=T[x].k;
    T[x<<1|1].s+=T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s=T[x].k=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,ll k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s+=k;
        T[x].k+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n-1;++i)
    {
        scanf("%d%d",&a[i],&b[i+1]);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        c[x].push_back(make_pair(y,k));
    }
    build(1,1,n);
    for(int i=1;i<=n;++i) add(1,i,i,b[i]);
    for(int i=1;i<=n;++i)
    {
        for(auto j:c[i]) add(1,1,j.first,j.second);
        d[i]=T[1].s;
    }
    build(1,1,n);
    for(int i=1;i<=n;++i) add(1,i,i,a[i]+d[i]);
    printf("%lld\n",T[1].s);
    for(int i=1;i<=q;++i)
    {
        int x,k;
        scanf("%d%d",&x,&k);
        add(1,x,x,k-a[x]);
        a[x]=k;
        printf("%lld\n",T[1].s);
    }
    return 0;
}