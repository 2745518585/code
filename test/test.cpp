#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,b[N];
struct tree
{
    int l,r,s,k;
}T[N<<2];
void pushup(int x)
{
    if(T[x].k==-1) return;
    T[x<<1].s=T[x].k*(b[T[x<<1].r+1]-b[T[x<<1].l]);
    T[x<<1].k=T[x].k;
    T[x<<1|1].s=T[x].k*(b[T[x<<1|1].r+1]-b[T[x<<1|1].l]);
    T[x<<1|1].k=T[x].k;
    T[x].k=-1;
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    T[x].k=-1;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,int k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s=k*(b[T[x].r+1]-b[T[x].l]);
        T[x].k=k;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
int main()
{
    scanf("%d%d",&n,&m);
    build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        int x,l,r;
        scanf("%d%d%d",&x,&l,&r);
        add(1,l,r,x);
    }
}