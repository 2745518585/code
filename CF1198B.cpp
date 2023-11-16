#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,a[N];
struct tree
{
    int l,r,k;
}T[N<<2];
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].k=max(T[x<<1].k,T[x].k);
    T[x<<1|1].k=max(T[x<<1|1].k,T[x].k);
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].k=a[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].k=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
}
int sum(int x,int q)
{
    if(T[x].l==T[x].r)
    {
        return T[x].k;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) return sum(x<<1,q);
    else return sum(x<<1|1,q);
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
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            add(1,x,k);
        }
        else
        {
            int x;
            scanf("%d",&x);
            T[1].k=max(T[1].k,x);
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d ",sum(1,i));
    }
    return 0;
}