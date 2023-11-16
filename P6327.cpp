#include<cmath>
#include<cstdio>
using namespace std;
int n,m,a[1000001];
struct tree
{
    int l,r,k;
    double s1,s2;
}T[10000001];
void plus(int x,int k)
{
    double q,r;
    q=T[x].s1*cos(k)+T[x].s2*sin(k);
    r=T[x].s2*cos(k)-T[x].s1*sin(k);
    T[x].s1=q;
    T[x].s2=r;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].k+=T[x].k;
    plus(x<<1,T[x].k);
    T[x<<1|1].k+=T[x].k;
    plus(x<<1|1,T[x].k);
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s1=sin(a[l]);
        T[x].s2=cos(a[l]);
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    T[x].s1=T[x<<1].s1+T[x<<1|1].s1;
    T[x].s2=T[x<<1].s2+T[x<<1|1].s2;
}
void add(int x,int l,int r,int k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        plus(x,k);
        T[x].k+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    T[x].s1=T[x<<1].s1+T[x<<1|1].s1;
    T[x].s2=T[x<<1].s2+T[x<<1|1].s2;
}
double sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s1;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    double s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
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
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            add(1,x,y,k);
        }
        else
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%.1lf\n",sum(1,x,y));
        }
    }
}