#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m;
ll a[N];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
struct tree
{
    int l,r;
    ll s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=gcd(T[x<<1].s,T[x<<1|1].s);
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
ll sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s=gcd(s,sum(x<<1,l,r));
    if(r>z) s=gcd(s,sum(x<<1|1,l,r));
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        if(n==1)
        {
            printf("1\n");
            continue;
        }
        for(int i=1;i<=n-1;++i) a[i]=abs(a[i+1]-a[i]);
        a[n]=0;
        build(1,1,n-1);
        int x=0,s=0;
        for(int i=1;i<=n-1;++i)
        {
            if(x<i) x=i;
            ll w=sum(1,i,x);
            while(x<=n-1&&w!=1) ++x,w=gcd(w,a[x]);
            s=max(s,x-i);
        }
        printf("%d\n",s+1);
    }
    return 0;
}