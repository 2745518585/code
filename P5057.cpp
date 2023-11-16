#include<cstdio>
using namespace std;
int n,m;
struct tree
{
    int l,r,k;
}T[1000001];
void pushdown(int x)
{
    T[x<<1].k^=T[x].k;
    T[x<<1|1].k^=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void modify(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k^=1;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) modify(x<<1,l,r);
    if(r>z) modify(x<<1|1,l,r);
}
int sum(int x,int q)
{
    if(T[x].l==q&&T[x].r==q)
    {
        return T[x].k;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) return sum(x<<1,q);
    return sum(x<<1|1,q);
}
int main()
{
    scanf("%d%d",&n,&m);
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            modify(1,x,y);
        }
        else if(z==2)
        {
            int x;
            scanf("%d",&x);
            printf("%d\n",sum(1,x));
        }
    }
    return 0;
}