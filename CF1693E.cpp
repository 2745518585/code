#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=500001;
int n,a[N],b[N],h1[N],h2[N];
struct num
{
    int s[3],t[3];
}p[4];
struct tree
{
    int l,r;
    num s;
}T[N<<2];
void pushup(num &T,num T1,num T2)
{
    T.s[0]=T1.s[T2.t[0]]+T2.s[0];
    T.t[0]=T1.t[T2.t[0]];
    T.s[1]=T1.s[T2.t[1]]+T2.s[1];
    T.t[1]=T1.t[T2.t[1]];
    T.s[2]=T1.s[T2.t[2]]+T2.s[2];
    T.t[2]=T1.t[T2.t[2]];
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=p[0];
        return;
    }
    int z=T[x].l+T[x].r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(T[x].s,T[x<<1].s,T[x<<1|1].s);
}
void add(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        b[q]+=k;
        T[x].s=p[b[q]];
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(T[x].s,T[x<<1].s,T[x<<1|1].s);
}
num sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1;
    num s;
    if(l<=z&&(!(r>z))) s=sum(x<<1,l,r);
    else if((!(l<=z))&&r>z) s=sum(x<<1|1,l,r);
    else pushup(s,sum(x<<1,l,r),sum(x<<1|1,l,r));
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
	p[0]=(num){{0,0,0},{0,1,2}};
	p[1]=(num){{0,0,1},{1,1,0}};
	p[2]=(num){{0,1,0},{2,0,2}};
	p[3]=(num){{1,1,1},{0,0,0}};
    h1[0]=h2[0]=1;
    build(1,0,n);
    add(1,0,3);
    for(int i=1;i<=n;++i) ++h1[a[i]];
    for(int i=1;i<=n;++i)
    {
        if(h1[i]) add(1,i,2);
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        --h1[a[i]];
        if(h1[a[i]]==0) add(1,a[i],-2);
        if(a[i]!=0) s+=sum(1,0,a[i]-1).s[0];
        if(h2[a[i]]==0) add(1,a[i],1);
        ++h2[a[i]];
    }
    printf("%lld",s);
    return 0;
}