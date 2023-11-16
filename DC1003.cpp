#include<cstdio>
using namespace std;
typedef long long ll;
int n,m,a[1000001];
struct tree
{
    int l,r;
    ll s;
}T[10000001];
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
	T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void add(int x,int q,int k)
{
    T[x].s+=k;
    if(T[x].l==T[x].r) return;
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else if(q>z) add(x<<1|1,q,k);
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
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int x,y,z;
        scanf("%d%d%d",&z,&x,&y);
        if(z==1)
        {
            add(1,x,y);
        }
        else if(z==2)
        {
            printf("%lld\n",sum(1,x,y));
        }
    }
    return 0;
}