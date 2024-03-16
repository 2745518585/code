#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,tot,a[N],b[N],rt[N];
struct tree
{
    int l,r,k;
}T[N<<6];
void maketag(int &x,int k)
{
    T[++tot]=T[x],x=tot;
    T[x].k+=k;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    maketag(T[x].l,T[x].k);
    maketag(T[x].r,T[x].k);
    T[x].k=0;
}
void add(int &x,int ls,int rs,int l,int r,int k)
{
    if(l>r) return;
    T[++tot]=T[x],x=tot;
    if(ls>=l&&rs<=r)
    {
        T[x].k+=k;
        return;
    }
    pushdown(x);
    int z=ls+rs>>1;
    if(l<=z) add(T[x].l,ls,z,l,r,k);
    if(r>z) add(T[x].r,z+1,rs,l,r,k);
}
int sum(int x,int ls,int rs,int q)
{
    if(x==0) return 0;
    if(ls==rs) return T[x].k;
    pushdown(x);
    int z=ls+rs>>1;
    if(q<=z) return sum(T[x].l,ls,z,q);
    else return sum(T[x].r,z+1,rs,q);
}
void merge(int &x1,int x2,int ls,int rs,int q)
{
    if(rs<=q) return;
    T[++tot]=T[x1],x1=tot;
    if(ls>q)
    {
        x1=x2;
        return;
    }
    pushdown(x1);
    pushdown(x2);
    int z=ls+rs>>1;
    merge(T[x1].l,T[x2].l,ls,z,q);
    merge(T[x1].r,T[x2].r,z+1,rs,q);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i) b[i]=n+1;
    for(int i=n;i>=1;--i)
    {
        rt[i]=rt[i+1];
        add(rt[i],1,n,i,b[a[i]]-1,1);
        merge(rt[i],rt[b[a[i]]+1],1,n,b[a[i]]-1);
        b[a[i]]=i;
    }
    int las=0;
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        l^=las,r^=las;
        printf("%d\n",las=sum(rt[l],1,n,r));
    }
    return 0;
}