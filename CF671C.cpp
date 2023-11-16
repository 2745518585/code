#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N],b[N][2],c[N][2],f[N];
struct tree
{
    int l,r,s1,s2,k;
    ll s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
    T[x].s2=min(T[x<<1].s2,T[x<<1|1].s2);
    T[x].s2=max(T[x<<1].s2,T[x<<1|1].s2);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].s=(ll)(T[x<<1].r-T[x<<1].l+1)*T[x].k;
    T[x<<1].s1=T[x<<1].s2=T[x<<1].k=T[x].k;
    T[x<<1|1].s=(ll)(T[x<<1|1].r-T[x<<1|1].l+1)*T[x].k;
    T[x<<1|1].s1=T[x<<1|1].s2=T[x<<1|1].k=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=l;
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
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s=(ll)(T[x].r-T[x].l+1)*k;
        T[x].s1=T[x].s2=T[x].k=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
ll sum(int x,int q)
{
    if(T[x].l==T[x].r)
    {
        return T[x].s;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(q<=z) return sum(x<<1,q);
    else return sum(x<<1|1,q);
}
int find(int x)
{
    int l=0,r=n;
    while(l<r)
    {
        int z=l+r+1>>1;
        if(sum(1,z)>=x) r=z-1;
        else l=z;
    }
    return l;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j*j<=a[i];++j)
        {
            if(a[i]%j==0)
            {
                if(b[j][0]==0) b[j][0]=i;
                else if(b[j][1]==0) b[j][1]=i;
                c[j][1]=c[j][0];
                c[j][0]=i;
                if(j==a[i]/j) continue;
                if(b[a[i]/j][0]==0) b[a[i]/j][0]=i;
                else if(b[a[i]/j][1]==0) b[a[i]/j][1]=i;
                c[a[i]/j][1]=c[a[i]/j][0];
                c[a[i]/j][0]=i;
            }
        }
    }
    build(1,1,n);
    ll s=0;
    for(int i=200000;i>=1;--i)
    {
        if(b[i][1]==0) continue;
        ll z=T[1].s;
        add(1,1,min(b[i][0],find(c[i][1])),c[i][1]);
        add(1,b[i][0]+1,min(b[i][1],find(c[i][0])),c[i][0]);
        add(1,b[i][1]+1,n,n+1);
        s+=(T[1].s-z)*i;
    }
    printf("%lld",s);
    return 0;
}