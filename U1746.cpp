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
    T[x].s=max(T[x<<1].s,T[x<<1|1].s);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void change(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=k;
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
    ll s=-1e18;
    if(l<=z) s=max(s,sum(x<<1,l,r));
    if(r>z) s=max(s,sum(x<<1|1,l,r));
    return s;
}
int n,m,t,las=0;
int main()
{
    scanf("%d%d",&n,&m);
    build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='A')
        {
            ++t;
            scanf("%d",&a[t]);
            a[t]=(a[t]+las)%m;
            change(1,t,a[t]);
        }
        else if(z[0]=='Q')
        {
            int x;
            scanf("%d",&x);
            las=sum(1,max(1,t-x+1),t);
            printf("%lld\n",las);
        }
    }
    return 0;
}