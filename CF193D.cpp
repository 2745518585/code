#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N],b[N];
ll s;
struct tree
{
    int l,r,k,t1,t2;
    ll s1,s2;
}T[N<<2];
void pushup(tree &T,tree T1,tree T2)
{
    if(T1.t1==T2.t1)
    {
        T.t1=T1.t1;
        T.t2=min(T1.t2,T2.t2);
    }
    else if(T1.t1<T2.t1)
    {
        T.t1=T1.t1;
        T.t2=min(T1.t2,T2.t1);
    }
    else
    {
        T.t1=T2.t1;
        T.t2=min(T1.t1,T2.t2);
    }
    T.s1=T.s2=0;
    if(T.t1==T1.t1) T.s1+=T1.s1;
    if(T.t1==T2.t1) T.s1+=T2.s1;
    if(T.t2==T1.t1) T.s2+=T1.s1;
    if(T.t2==T2.t1) T.s2+=T2.s1;
    if(T.t2==T1.t2) T.s2+=T1.s2;
    if(T.t2==T2.t2) T.s2+=T2.s2;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].k+=T[x].k;
    T[x<<1].t1+=T[x].k;
    T[x<<1].t2+=T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x<<1|1].t1+=T[x].k;
    T[x<<1|1].t2+=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].t1=0,T[x].t2=1e9;
    T[x].s1=1,T[x].s2=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
void add(int x,int l,int r,int k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k+=k;
        T[x].t1+=k;
        T[x].t2+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
tree sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x];
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    tree s;
    if(l<=z&&!(r>z)) s=sum(x<<1,l,r);
    else if(!(l<=z)&&r>z) s=sum(x<<1|1,l,r);
    else pushup(s,sum(x<<1,l,r),sum(x<<1|1,l,r));
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i) b[a[i]]=i;
    build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        add(1,1,i,1);
        if(a[b[i]-1]!=0&&a[b[i]-1]<i) add(1,1,a[b[i]-1],-1);
        if(a[b[i]+1]!=0&&a[b[i]+1]<i) add(1,1,a[b[i]+1],-1);
        if(i>1)
        {
            tree w=sum(1,1,i-1);
            s+=(w.t1<=2)*w.s1+(w.t2<=2)*w.s2;
        }
    }
    printf("%lld",s);
    return 0;
}