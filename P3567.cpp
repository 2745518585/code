#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10000001;
int n,m,p=0,a[N],b[N],rt[N];
struct tree
{
    int l,r,s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void build(int &x,int l,int r)
{
    x=++p;
    if(l==r) return;
    int z=l+r>>1;
    build(T[x].l,l,z);
    build(T[x].r,z+1,r);
}
void modify(int &x,int l,int r,int q)
{
    T[++p]=T[x];
    ++T[p].s;
    x=p;
    if(l==r) return;
    int z=l+r>>1;
    if(q<=z) modify(T[x].l,l,z,q);
    else modify(T[x].r,z+1,r,q);
}
int sum(int x1,int x2,int l,int r,int q)
{
    if(l==r) return b[l];
    int z=l+r>>1;
    if(q<=T[T[x2].l].s-T[T[x1].l].s) return sum(T[x1].l,T[x2].l,l,z,q);
    else if(q<=T[T[x2].r].s-T[T[x1].r].s) return sum(T[x1].r,T[x2].r,z+1,r,q);
    else return 0;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    int q=unique(b+1,b+n+1)-b-1;
    build(rt[0],1,q);
    for(int i=1;i<=n;++i)
    {
        rt[i]=rt[i-1];
        modify(rt[i],1,q,lower_bound(b+1,b+q+1,a[i])-b);
    }
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",sum(rt[l-1],rt[r],1,q,(r-l+1)/2+1));
    }
    return 0;
}