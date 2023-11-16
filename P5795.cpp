#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int m,n,q,tot,rt[N],a[N],b1[N],b2[N];
struct tree
{
    int l,r,s;
}T[N<<4];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void add(int &x,int t,int q)
{
    T[++tot]=T[x];
    x=tot;
    if(t==-1)
    {
        ++T[x].s;
        return;
    }
    if((q&(1<<t))==0) add(T[x].l,t-1,q);
    else add(T[x].r,t-1,q);
    pushup(x);
}
int sum(int t,int x1,int x2,ll k)
{
    if(t==-1) return 0;
    ll s=0;
    for(int i=x1;i<=x2;++i)
    {
        if((a[i]&(1<<t))==0) s+=T[T[b2[i]].r].s-T[T[b1[i]].r].s;
        else s+=T[T[b2[i]].l].s-T[T[b1[i]].l].s;
    }
    if(k<=s)
    {
        for(int i=x1;i<=x2;++i)
        {
            if((a[i]&(1<<t))==0) b1[i]=T[b1[i]].r,b2[i]=T[b2[i]].r;
            else b1[i]=T[b1[i]].l,b2[i]=T[b2[i]].l;
        }
        return sum(t-1,x1,x2,k)+(1<<t);
    }
    else
    {
        for(int i=x1;i<=x2;++i)
        {
            if((a[i]&(1<<t))==0) b1[i]=T[b1[i]].l,b2[i]=T[b2[i]].l;
            else b1[i]=T[b1[i]].r,b2[i]=T[b2[i]].r;
        }
        return sum(t-1,x1,x2,k-s);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        rt[i]=rt[i-1];
        add(rt[i],30,x);
    }
    scanf("%d",&q);
    for(int i=1;i<=q;++i)
    {
        int x1,x2,y1,y2;
        ll k;
        scanf("%d%d%d%d%lld",&x1,&x2,&y1,&y2,&k);
        for(int i=1;i<=n;++i) b1[i]=rt[y1-1],b2[i]=rt[y2];
        printf("%d\n",sum(30,x1,x2,k));
    }
    return 0;
}