#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N],S1[N],S2[N],T1,T2;
ll d;
struct tree
{
    int l,r;
    ll k,s;
}T[N<<2];
map<int,int> Map;
void pushup(int x)
{
    T[x].s=min(T[x<<1].s,T[x<<1|1].s);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].k+=T[x].k;
    T[x<<1].s+=T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x<<1|1].s+=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=(ll)l*d;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,ll k)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k+=k;
        T[x].s+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
ll sum(int x,ll k)
{
    if(T[x].l==T[x].r) return T[x].l;
    pushdown(x);
    if(T[x<<1].s<=k) return sum(x<<1,k);
    return sum(x<<1|1,k);
}
int main()
{
    scanf("%d%d%lld",&n,&m,&d);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    if(d==0)
    {
        int s=0,w=0,q;
        for(int i=1;i<=n;++i)
        {
            if(a[i]==a[i-1]) ++w;
            else w=1;
            if(w>s) s=w,q=i;
        }
        printf("%d %d",q-s+1,q);
        return 0;
    }
    build(1,1,n);
    int x=1,s=0,q;
    for(int i=1;i<=n;++i)
    {
        int p=x;
        if((a[i]%d+d)%d!=(a[i-1]%d+d)%d) x=i;
        if(Map.count(a[i])) x=max(x,Map[a[i]]+1);
        add(1,p,x-1,1e18);
        Map[a[i]]=i;
        while(T1>=1&&a[S1[T1]]<=a[i])
        {
            add(1,S1[T1-1]+1,S1[T1],a[i]-a[S1[T1]]);
            --T1;
        }
        S1[++T1]=i;
        while(T2>=1&&a[S2[T2]]>=a[i])
        {
            add(1,S2[T2-1]+1,S2[T2],a[S2[T2]]-a[i]);
            --T2;
        }
        S2[++T2]=i;
        int z=i-sum(1,(m+i)*d)+1;
        if(z>s) s=z,q=i;
    }
    printf("%d %d",q-s+1,q);
    return 0;
}