#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,m,a[N],b[N],c[N];
struct tree
{
    int l,r,k,w1,w2;
    ll s;
}T[N];
void pushup(int x)
{
    if(T[x].k)
    {
        T[x].w1=T[x].w2=T[x].r-T[x].l+1;
        T[x].s=(ll)(T[x].r-T[x].l+1)*(T[x].r-T[x].l+2)/2;
        return;
    }
    if(T[x<<1].w1==T[x<<1].r-T[x<<1].l+1) T[x].w1=T[x<<1].w1+T[x<<1|1].w1;
    else T[x].w1=T[x<<1].w1;
    if(T[x<<1|1].w2==T[x<<1|1].r-T[x<<1|1].l+1) T[x].w2=T[x<<1|1].w2+T[x<<1].w2;
    else T[x].w2=T[x<<1|1].w2;
    T[x].s=T[x<<1].s+T[x<<1|1].s+(ll)T[x<<1].w2*T[x<<1|1].w1;
    // printf("%d %d: %d %d %d %lld\n",T[x].l,T[x].r,T[x].k,T[x].w1,T[x].w2,T[x].s);
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    T[x].k=T[x].w1=T[x].w2=T[x].s=0;
    if(l==r)
    {
        T[x<<1].k=T[x<<1].w1=T[x<<1].w2=T[x<<1].s=0;
        T[x<<1|1].k=T[x<<1|1].w1=T[x<<1|1].w2=T[x<<1|1].s=0;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,int k)
{
    if(l>r) return;
    // if(x==1) printf(" %d %d %d\n",l,r,k);
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k+=k;
        pushup(x);
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
void update(int x,int y,int k)
{
    if(b[x]>1) add(1,a[x],a[c[b[x]-1]]-1,k);
    if(b[x]<n) add(1,a[c[b[x]+1]],a[x]-1,k);
    if(b[y]>1) add(1,a[y],a[c[b[y]-1]]-1,k);
    if(b[y]<n) add(1,a[c[b[y]+1]],a[y]-1,k);
    if(abs(b[x]-b[y])==1)
    {
        add(1,a[c[max(b[x],b[y])]],a[c[min(b[x],b[y])]]-1,-k);
    }
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
            c[b[i]]=i;
        }
        build(1,1,n);
        for(int i=1;i<=n-1;++i)
        {
            add(1,a[c[i+1]],a[c[i]]-1,1);
        }
        for(int i=1;i<=m;++i)
        {
            int z,x,y;
            scanf("%d%d%d",&z,&x,&y);
            update(x,y,-1);
            if(z==1) swap(a[x],a[y]);
            else if(z==2)
            {
                swap(b[x],b[y]);
                c[b[x]]=x,c[b[y]]=y;
            }
            update(x,y,1);
            printf("%lld\n",(ll)n*(n+1)/2+T[1].s);
            // printf("%lld\n",T[1].s);
        }
    }
    return 0;
}