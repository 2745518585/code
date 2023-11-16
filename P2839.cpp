#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,tot,rt[N],a[N],b[N];
struct str
{
    int x,s;
}c[N];
struct tree
{
    int l,r,s,s1,s2;
}T[N<<4];
bool cmp(str a,str b)
{
    return a.s<b.s;
}
void pushup(tree &T,tree T1,tree T2)
{
    T.s=T1.s+T2.s;
    T.s1=max(T1.s1,T1.s+T2.s1);
    T.s2=max(T2.s2,T2.s+T1.s2);
}
void add(int &x,int ls,int rs,int q,int k)
{
    T[++tot]=T[x];
    x=tot;
    if(ls==rs)
    {
        T[x].s=k;
        if(k>=0) T[x].s1=T[x].s2=k;
        else T[x].s1=T[x].s2=0;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q,k);
    else add(T[x].r,z+1,rs,q,k);
    pushup(T[x],T[T[x].l],T[T[x].r]);
}
tree sum(int x,int ls,int rs,int l,int r)
{
    if(l>r||x==0) return (tree){0,0,0,0,0};
    if(ls>=l&&rs<=r)
    {
        return T[x];
    }
    int z=ls+rs>>1;
    tree s;
    if(l<=z&&!(r>z)) s=sum(T[x].l,ls,z,l,r);
    else if(!(l<=z)&&r>z) s=sum(T[x].r,z+1,rs,l,r);
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
    for(int i=1;i<=n;++i) add(rt[1],1,n,i,1);
    int x=1;
    for(int i=2;i<=q+1;++i)
    {
        rt[i]=rt[i-1];
        while(c[x].s==i-1)
        {
            add(rt[i],1,n,c[x].x,-1);
            ++x;
        }
    }
    scanf("%d",&m);
    int las=0;
    for(int i=1;i<=m;++i)
    {
        int x[10];
        for(int j=1;j<=4;++j)
        {
            scanf("%d",&x[j]);
            x[j]=(x[j]+las)%n+1;
        }
        sort(x+1,x+5);
        int x1=x[1],x2=x[2],x3=x[3],x4=x[4],l=1,r=q+1;
        while(l<r)
        {
            int z=l+r+1>>1;
            if(sum(rt[z],1,n,x2,x3).s+sum(rt[z],1,n,x1,x2-1).s2+sum(rt[z],1,n,x3+1,x4).s1>=0) l=z;
            else r=z-1;
        }
        printf("%d\n",las=b[l]);
    }
    return 0;
}