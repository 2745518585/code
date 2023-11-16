#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline ll read()
{
    char c=getchar();ll x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
ll b[N];
struct Segment_tree
{
    struct tree
    {
        int l,r,k;
        ll s;
    };
    tree T[N<<2];
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
            T[x].s=b[l];
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int l,int r,ll k)
    {
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
    ll sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        ll s=1e18;
        if(l<=z) s=min(s,sum(x<<1,l,r));
        if(r>z) s=min(s,sum(x<<1|1,l,r));
        return s;
    }
};
Segment_tree T;
int n,m;
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;++i) b[i]=read();
    T.build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        ll k=read();
        int x=read(),y=read();
        if(T.sum(1,x,y)>=k) T.add(1,x,y,-k);
        else
        {
            printf("-1\n%d",i);
            return 0;
        }
    }
    printf("0");
    return 0;
}