#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,p=0,a[N],b[N],rt[N];
struct tree
{
    int l,r,s;
}T[N<<4];
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
int sum(int x,int l,int r,int l0,int r0)
{
    if(l>=l0&&r<=r0) return T[x].s;
    int z=l+r>>1,s=0;
    if(l0<=z) s+=sum(T[x].l,l,z,l0,r0);
    if(r0>z) s+=sum(T[x].r,z+1,r,l0,r0);
    return s;
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
        int d,z,x,y;
        scanf("%d%d%d%d",&d,&z,&x,&y);
        rt[i]=rt[d];
        if(z==1)
        {
            modify(rt[i],1,n,x,y);
        }
        else
        {
            printf("%d\n",sum(rt[i],1,n,x,y));
        }
    }
    return 0;
}