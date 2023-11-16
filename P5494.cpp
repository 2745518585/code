#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q=1,tot,rt[N];
struct tree
{
    int l,r;
    ll s;
}T[N<<6];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void add(int &x,int ls,int rs,int q,ll k)
{
    if(x==0) x=++tot;
    if(ls==rs)
    {
        T[x].s+=k;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q,k);
    else add(T[x].r,z+1,rs,q,k);
    pushup(x);
}
void split(int x,int ls,int rs,int k,int &x1,int &x2)
{
    if(x==0) return;
    if(ls==rs)
    {
        if(ls<=k) x1=x;
        else x2=x;
        return;
    }
    int z=ls+rs>>1;
    x1=++tot,x2=++tot;
    if(z<=k)
    {
        T[x1].l=T[x].l;
        split(T[x].r,z+1,rs,k,T[x1].r,T[x2].r);
    }
    else
    {
        T[x2].r=T[x].r;
        split(T[x].l,ls,z,k,T[x1].l,T[x2].l);
    }
    pushup(x1);
    pushup(x2);
}
int merge(int x1,int x2,int ls,int rs)
{
    if(x1==0) return x2;
    if(x2==0) return x1;
    if(ls==rs)
    {
        T[x1].s=T[x1].s+T[x2].s;
        return x1;
    }
    int z=ls+rs>>1;
    T[x1].l=merge(T[x1].l,T[x2].l,ls,z);
    T[x1].r=merge(T[x1].r,T[x2].r,z+1,rs);
    pushup(x1);
    return x1;
}
ll sum(int x,int ls,int rs,int l,int r)
{
    if(x==0) return 0;
    if(ls>=l&&rs<=r) return T[x].s;
    int z=ls+rs>>1;
    ll s=0;
    if(l<=z) s+=sum(T[x].l,ls,z,l,r);
    if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
    return s;
}
int sum2(int x,int ls,int rs,int k)
{
    if(x==0) return -1;
    if(ls==rs)
    {
        if(k<=T[x].s) return ls;
        return -1;
    }
    int z=ls+rs>>1,s=0;
    if(k<=T[T[x].l].s) return sum2(T[x].l,ls,z,k);
    else return sum2(T[x].r,z+1,rs,k-T[T[x].l].s);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        add(rt[1],1,n,i,x);
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==0)
        {
            int p,x,y;
            scanf("%d%d%d",&p,&x,&y);
            int x1,x2,x3;
            split(rt[p],1,n,y,x1,x3);
            split(x1,1,n,x-1,x1,x2);
            rt[p]=merge(x1,x3,1,n);
            rt[++q]=x2;
        }
        else if(z==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            rt[x]=merge(rt[x],rt[y],1,n);
        }
        else if(z==2)
        {
            int p,x,k;
            scanf("%d%d%d",&p,&k,&x);
            add(rt[p],1,n,x,k);
        }
        else if(z==3)
        {
            int p,x,y;
            scanf("%d%d%d",&p,&x,&y);
            printf("%lld\n",sum(rt[p],1,n,x,y));
        }
        else if(z==4)
        {
            int p;
            ll k;
            scanf("%d%lld",&p,&k);
            printf("%d\n",sum2(rt[p],1,n,k));
        }
    }
    return 0;
}