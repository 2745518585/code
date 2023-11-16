#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,tot,a[N],b[N],rt[N];
struct str
{
    int x,s;
}c[N];
struct tree
{
    int l,r,s,s1,s2,t;
}T[N<<2];
bool cmp(str a,str b)
{
    return a.s>b.s;
}
void pushup(tree &T,tree T1,tree T2)
{
    T.t=T1.t+T2.t;
    T.s=max(max(T1.s,T2.s),T1.s2+T2.s1);
    T.s1=T1.s1,T.s2=T2.s2;
    if(T1.s==T1.t) T.s1=T1.s+T2.s1;
    if(T2.s==T2.t) T.s2=T1.s2+T2.s;
}
void build(int &x,int l,int r)
{
    x=++tot;
    if(l==r)
    {
        T[x].t=1;
        return;
    }
    int z=l+r>>1;
    build(T[x].l,l,z);
    build(T[x].r,z+1,r);
    pushup(T[x],T[T[x].l],T[T[x].r]);
}
void add(int &x,int ls,int rs,int q)
{
    T[++tot]=T[x];
    x=tot;
    if(ls==rs)
    {
        T[x].s=T[x].s1=T[x].s2=1;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q);
    else add(T[x].r,z+1,rs,q);
    pushup(T[x],T[T[x].l],T[T[x].r]);
}
tree sum(int x,int ls,int rs,int l,int r)
{
    if(x==0) return (tree){0,0,0,0,0,0};
    if(ls>=l&&rs<=r)
    {
        return T[x];
    }
    int z=ls+rs>>1;
    tree s;
    if(l<=z&&(!(r>z))) s=sum(T[x].l,ls,z,l,r);
    else if((!(l<=z))&&r>z) s=sum(T[x].r,z+1,rs,l,r);
    else pushup(s,sum(T[x].l,ls,z,l,r),sum(T[x].r,z+1,rs,l,r));
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    q=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(b+1,b+q+1,a[i])-b;
        c[i].s=a[i];
        c[i].x=i;
    }
    sort(c+1,c+n+1,cmp);
    build(rt[q+1],1,n);
    int x=1;
    for(int i=q;i>=1;--i)
    {
        rt[i]=rt[i+1];
        while(c[x].s==i)
        {
            add(rt[i],1,n,c[x].x);
            ++x;
        }
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        int l=1,r=q;
        while(l<r)
        {
            int z=l+r+1>>1;
            if(sum(rt[z],1,n,x,y).s>=k) l=z;
            else r=z-1;
        }
        printf("%d\n",b[l]);
    }
    return 0;
}