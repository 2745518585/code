#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001,M=61;
int n,m,q,P,a[N],c[N],d[N],h[N];
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
struct tree
{
    int l,r,s[M],t,k;
}T[N<<2];
void pushup(int x)
{
    for(int i=0;i<=q-1;++i) T[x].s[i]=T[x<<1].s[i]+T[x<<1|1].s[i];
    T[x].t=max(T[x<<1].t,T[x<<1|1].t);
}
void maketag(int x,int k)
{
    rotate(T[x].s,T[x].s+k%q,T[x].s+q);
    T[x].k+=k;
    T[x].t=max(T[x].t-k,0);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    maketag(x<<1,T[x].k);
    maketag(x<<1|1,T[x].k);
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].t=c[a[l]];
        int p=a[l];
        T[x].s[0]=p;
        for(int i=1;i<=q-1;++i)
        {
            p=p*p%P;
            T[x].s[i]=p;
        }
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r&&T[x].t==0)
    {
        maketag(x,1);
        return;
    }
    if(T[x].l==T[x].r)
    {
        for(int i=0;i<=q-1;++i) T[x].s[i]=T[x].s[i]*T[x].s[i]%P;
        --T[x].t;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r);
    if(r>z) add(x<<1|1,l,r);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s[0];
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1,s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
int main()
{
    scanf("%d%d%d",&n,&m,&P);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<=P-1;++i)
    {
        for(int j=0;j<=P-1;++j) h[j]=-1;
        int x=i;
        h[x]=0;
        while(true)
        {
            x=x*x%P;
            if(h[x]!=-1)
            {
                c[i]=h[x];
                d[i]-=c[i]-1;
                break;
            }
            ++d[i];
            h[x]=d[i];
        }
    }
    q=d[0];
    for(int i=0;i<=P-1;++i) q=q*d[i]/gcd(q,d[i]);
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z,l,r;
        scanf("%d%d%d",&z,&l,&r);
        if(z==1) add(1,l,r);
        else printf("%d\n",sum(1,l,r));
    }
    return 0;
}