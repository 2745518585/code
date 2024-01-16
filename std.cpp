#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N];
vector<pair<int,int>> b[N];
struct tree
{
    int l,r,s,k;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].s=(T[x<<1].r-T[x<<1].l+1)-T[x<<1].s;
    T[x<<1].k^=1;
    T[x<<1|1].s=(T[x<<1|1].r-T[x<<1|1].l+1)-T[x<<1|1].s;
    T[x<<1|1].k^=1;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    if(l==r)
    {
        T[x].s=0;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s=(T[x].r-T[x].l+1)-T[x].s;
        T[x].k^=1;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r);
    if(r>z) add(x<<1|1,l,r);
    pushup(x);
}
int sum(int x,int q)
{
    if(T[x].l==T[x].r) return T[x].s;
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) return sum(x<<1,q);
    else return sum(x<<1|1,q);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        l=lower_bound(a+1,a+n+1,l)-a;
        r=upper_bound(a+1,a+n+1,r)-a-1;
        b[l].push_back(make_pair(l,r));
        b[r+1].push_back(make_pair(l,r));
    }
    build(1,1,n);
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        for(auto j:b[i])
        {
            add(1,j.first,j.second);
        }
        int z=T[1].s-sum(1,i);
        s+=(ll)z*(z-1)/2;
        printf("%lld\n",s);
        return 0;
        add(1,i,i);
    }
    printf("%lld",(ll)n*(n-1)*(n-2)/6-s);
    return 0;
}