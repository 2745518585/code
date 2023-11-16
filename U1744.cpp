#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
struct tree
{
    int l,r;
    ll s;
}T[N<<2];
int a[N];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=a[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void change(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s+=k;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) change(x<<1,q,k);
    else change(x<<1|1,q,k);
    pushup(x);
}
ll sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==0)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            change(1,x,k);
        }
        else if(z==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%lld\n",sum(1,x,y));
        }
    }
    return 0;
}