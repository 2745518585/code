#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,a[N];
struct tree
{
    int l,r;
    long long lm,rm,m,s;
}T[N<<2];
void pushup(tree &x,tree l,tree r)
{
    x.lm=max(l.lm,l.s+r.lm);
    x.rm=max(r.rm,r.s+l.rm);
    x.m=max(l.rm+r.lm,max(l.m,r.m));
    x.s=l.s+r.s;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].lm=T[x].rm=T[x].m=T[x].s=a[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
void add(int x,int t,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].lm=T[x].rm=T[x].m=T[x].s=k;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(t<=z) add(x<<1,t,k);
    else add(x<<1|1,t,k);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
tree sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r) return T[x];
    int z=T[x].l+T[x].r>>1;
    if(r<=z) return sum(x<<1,l,r);
    if(l>z) return sum(x<<1|1,l,r);
    tree s;
    pushup(s,sum(x<<1,l,r),sum(x<<1|1,l,r));
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    build(1,1,n);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,z;
        scanf("%d%d%d",&z,&x,&y);
        if(z==1)
        {
            if(x>y) swap(x,y);
            printf("%lld\n",sum(1,x,y).m);
        }
        else
        {
            add(1,x,y);
        }
    }
    return 0;
}