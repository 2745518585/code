#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200001,M=10;
int n,m,q,a[N];
struct str
{
    int a[M];
};
str merge(str a,str b)
{
    str c;
    for(int i=1;i<=m+1;++i) c.a[i]=a.a[b.a[i]];
    return c;
}
struct tree
{
    int l,r,k;
    str s[2];
}T[N<<2];
void pushup(int x)
{
    T[x].s[0]=merge(T[x<<1].s[0],T[x<<1|1].s[0]);
    T[x].s[1]=merge(T[x<<1].s[1],T[x<<1|1].s[1]);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    swap(T[x<<1].s[0],T[x<<1].s[1]);
    T[x<<1].k^=1;
    swap(T[x<<1|1].s[0],T[x<<1|1].s[1]);
    T[x<<1|1].k^=1;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        for(int i=1;i<=m;++i) T[x].s[0].a[i]=T[x].s[1].a[i]=i+1;
        T[x].s[a[l]].a[m+1]=1;
        T[x].s[a[l]^1].a[m+1]=m+1;
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
        swap(T[x].s[0],T[x].s[1]);
        T[x].k^=1;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r);
    if(r>z) add(x<<1|1,l,r);
    pushup(x);
}
str sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s[0];
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z&&(!(r>z))) return sum(x<<1,l,r);
    if((!(l<=z))&&r>z) return sum(x<<1|1,l,r);
    return merge(sum(x<<1,l,r),sum(x<<1|1,l,r));
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)
    {
        ll x;
        scanf("%lld",&x);
        a[i]=(x%2)^1;
    }
    build(1,1,n);
    for(int i=1;i<=q;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int l,r;
            ll k;
            scanf("%d%d%lld",&l,&r,&k);
            if(k%2==1) add(1,l,r);
        }
        else if(z==2)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",(sum(1,l,r).a[m+1]==1)+1);
        }
    }
    return 0;
}