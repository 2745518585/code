#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,tot,rt[N],a[N];
struct tree
{
    int l,r,s;
}T[N<<3];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void add(int &x,int ls,int rs,int q)
{
    T[++tot]=T[x];
    x=tot;
    if(ls==rs)
    {
        ++T[x].s;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q);
    else add(T[x].r,z+1,rs,q);
    pushup(x);
}
int sum(int x,int ls,int rs,int l,int r)
{
    if(l<0) l=0;
    if(r>1e6) r=1e6;
    if(x==0||l>r) return 0;
    if(ls>=l&&rs<=r)
    {
        return T[x].s;
    }
    int z=ls+rs>>1,s=0;
    if(l<=z) s+=sum(T[x].l,ls,z,l,r);
    if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        rt[i]=rt[i-1];
        add(rt[i],0,1e6,a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y,l,r;
        scanf("%d%d%d%d",&x,&y,&l,&r);
        int s=0;
        for(int i=20;i>=0;--i)
        {
            if((x&(1<<i))==0)
            {
                if(sum(rt[r],0,1e6,s+(1<<i)-y,s+(1<<i)+((1<<i)-1)-y)-sum(rt[l-1],0,1e6,s+(1<<i)-y,s+(1<<i)+((1<<i)-1)-y)!=0) s|=(1<<i);
            }
            else
            {
                if(sum(rt[r],0,1e6,s-y,s+((1<<i)-1)-y)-sum(rt[l-1],0,1e6,s-y,s+((1<<i)-1)-y)==0) s|=(1<<i);
            }
        }
        printf("%d\n",x^s);
    }
    return 0;
}