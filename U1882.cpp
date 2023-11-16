#include<bits/stdc++.h>
using namespace std;
const int N=1000001;
int n,m,sa[N],rk[N],he[N];
char a[N];
namespace SA
{
    int h[N],x1[N],x2[N];
    void init(char a[])
    {
        int n=strlen(a+1),m=128;
        for(int i=1;i<=n;++i)
        {
            ++h[a[i]];
            x1[i]=a[i];
        }
        for(int i=1;i<=m;++i) h[i]+=h[i-1];
        for(int i=n;i>=1;--i) sa[h[x1[i]]--]=i;
        for(int r=1;r<=n;r<<=1)
        {
            int p=0;
            for(int i=n-r+1;i<=n;++i) x2[++p]=i;
            for(int i=1;i<=n;++i) if(sa[i]>r) x2[++p]=sa[i]-r;
            for(int i=1;i<=m;++i) h[i]=0;
            for(int i=1;i<=n;++i) ++h[x1[i]];
            for(int i=1;i<=m;++i) h[i]+=h[i-1];
            for(int i=n;i>=1;--i) sa[h[x1[x2[i]]]--]=x2[i],x2[i]=0;
            swap(x1,x2);
            p=0;
            x1[sa[1]]=++p;
            for(int i=2;i<=n;++i)
            {
                if(x2[sa[i]]==x2[sa[i-1]]&&x2[sa[i]+r]==x2[sa[i-1]+r]) x1[sa[i]]=p;
                else x1[sa[i]]=++p;
            }
            if(p==n) break;
            m=p;
        }
        for(int i=1;i<=n;++i) rk[sa[i]]=i;
        int p=0;
        for(int i=1;i<=n;++i)
        {
            if(rk[i]==1) continue;
            if(p>=1) --p;
            int j=sa[rk[i]-1];
            while(i+p<=n&&j+p<=n&&a[i+p]==a[j+p]) ++p;
            he[rk[i]]=p;
        }
    }
}
namespace Segment_tree
{
    struct tree
    {
        int l,r,s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=min(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        if(l==r)
        {
            T[x].s=he[l];
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(l>r) return 1e9;
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        int z=T[x].l+T[x].r>>1,s=1e9;
        if(l<=z) s=min(s,sum(x<<1,l,r));
        if(r>z) s=min(s,sum(x<<1|1,l,r));
        return s;
    }
}
struct tree
{
    int l,r,s;
}T[N<<4];
int rt[N],tot;
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void add(int &x,int ls,int rs,int q,int k)
{
    T[++tot]=T[x];
    x=tot;
    if(ls==rs)
    {
        T[x].s=k;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q,k);
    else add(T[x].r,z+1,rs,q,k);
    pushup(x);
}
int sum(int x,int ls,int rs,int l,int r)
{
    if(x==0) return 0;
    if(ls>=l&&rs<=r)
    {
        return T[x].s;
    }
    int z=ls+rs>>1,s=0;
    if(l<=z) s+=sum(T[x].l,ls,z,l,r);
    if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
    return s;
}
int sum1(int x1,int x2,int ls,int rs,int r,int k)
{
    if(ls==rs) return ls;
    int z=ls+rs>>1;
    if(r>z&&k-(T[T[x2].l].s-T[T[x1].l].s)>0) return sum1(T[x1].r,T[x2].r,z+1,rs,r,k-(T[T[x2].l].s-T[T[x1].l].s));
    if(r>z) return sum1(T[x1].l,T[x2].l,ls,z,z,T[T[x2].l].s-T[T[x1].l].s);
    else return sum1(T[x1].l,T[x2].l,ls,z,r,k);
}
int sum2(int x1,int x2,int ls,int rs,int l,int k)
{
    if(ls==rs) return ls;
    int z=ls+rs>>1;
    if(l<=z&&k-(T[T[x2].r].s-T[T[x1].r].s)>0) return sum2(T[x1].l,T[x2].l,ls,z,l,k-(T[T[x2].r].s-T[T[x1].r].s));
    if(l<=z) return sum2(T[x1].r,T[x2].r,z+1,rs,z+1,T[T[x2].r].s-T[T[x1].r].s);
    else return sum2(T[x1].r,T[x2].r,z+1,rs,l,k);
}
int main()
{
    scanf("%d%d%s",&n,&m,a+1);
    SA::init(a);
    Segment_tree::build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        rt[i]=rt[i-1];
        add(rt[i],1,n,rk[i],1);
    }
    for(int i=1;i<=m;++i)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        int l=0,r=min(y1-x1+1,y2-x2+1);
        while(l<r)
        {
            int z=l+r+1>>1;
            int p1=sum1(rt[x1-1],rt[y1-z+1],1,n,rk[x2],sum(rt[y1-z+1],1,n,1,rk[x2])-sum(rt[x1-1],1,n,1,rk[x2]));
            int p2=sum2(rt[x1-1],rt[y1-z+1],1,n,rk[x2],sum(rt[y1-z+1],1,n,rk[x2],n)-sum(rt[x1-1],1,n,rk[x2],n));
            if(max((sa[p1]>=x1&&sa[p1]<=y1)?Segment_tree::sum(1,p1+1,rk[x2]):0,(sa[p2]>=x1&&sa[p2]<=y1)?Segment_tree::sum(1,rk[x2]+1,p2):0)>=z) l=z;
            else r=z-1;
        }
        printf("%d\n",l);
    }
    return 0;
}