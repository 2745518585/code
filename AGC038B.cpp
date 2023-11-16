#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,k,a[N],b[N];
struct tree
{
    int l,r,s1,s2;
}T[N<<2];
void pushup(int x)
{
    T[x].s1=min(T[x<<1].s1,T[x<<1|1].s1);
    T[x].s2=max(T[x<<1].s2,T[x<<1|1].s2);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s1=T[x].s2=a[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
int sum1(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s1;
    }
    int z=T[x].l+T[x].r>>1,s=1e9;
    if(l<=z) s=min(s,sum1(x<<1,l,r));
    if(r>z) s=min(s,sum1(x<<1|1,l,r));
    return s;
}
int sum2(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s2;
    }
    int z=T[x].l+T[x].r>>1,s=-1e9;
    if(l<=z) s=max(s,sum2(x<<1,l,r));
    if(r>z) s=max(s,sum2(x<<1|1,l,r));
    return s;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        if(a[i]>a[i-1]) b[i]=b[i-1];
        else b[i]=i;
    }
    build(1,1,n);
    bool u=false;
    int s=0;
    if(b[1]!=b[k]) s=1;
    else u=true;
    for(int i=1;i<=n-k;++i)
    {
        if(b[i+1]==b[i+k]) u=true;
        else if(sum1(1,i,i+k-1)==a[i]&&sum2(1,i+1,i+k)==a[i+k]);
        else ++s;
    }
    printf("%d",s+u);
    return 0;
}