#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,p=0,a[1000001],b[1000001],rt[1000001];
struct tree
{
    int l,r,s;
}T[100000001];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void build(int &x,int l,int r)
{
    x=++p;
    if(l==r)
    {
        T[x].s=a[l];
        return;
    }
    int z=l+r>>1;
    build(T[x].l,l,z);
    build(T[x].r,z+1,r);
}
void modify(int &x,int l,int r,int q,int k)
{
    T[++p]=T[x];
    T[p].s=k;
    x=p;
    if(l==r) return;
    int z=l+r>>1;
    if(q<=z) modify(T[x].l,l,z,q,k);
    else modify(T[x].r,z+1,r,q,k);
}
int sum(int x,int l,int r,int q)
{
    if(l==r) return T[x].s;
    int z=l+r>>1;
    if(q<=z) return sum(T[x].l,l,z,q);
    else return sum(T[x].r,z+1,r,q);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    build(rt[0],1,n);
    for(int i=1;i<=m;++i)
    {
        int d,z,x;
        scanf("%d%d%d",&d,&z,&x);
        rt[i]=rt[d];
        if(z==1)
        {
            int k;
            scanf("%d",&k);
            modify(rt[i],1,n,x,k);
        }
        else
        {
            printf("%d\n",sum(rt[i],1,n,x));
        }
    }
    return 0;
}