#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,tot,rt,a[N];
struct tree
{
    int k,l,r,h,t,w;
    ll s;
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+(ll)T[x].t*(T[T[x].l].w+1)*(T[T[x].r].w+1);
    T[x].w=T[T[x].l].w+T[T[x].r].w+1;
}
void split(int x,int k,int &x1,int &x2)
{
    if(x==0)
    {
        x1=x2=0;
        return;
    }
    if(T[x].k<=k)
    {
        x1=x;
        split(T[x].r,k,T[x].r,x2);
    }
    else
    {
        x2=x;
        split(T[x].l,k,x1,T[x].l);
    }
    pushup(x);
}
int merge(int x1,int x2)
{
    if(x1==0||x2==0) return x1|x2;
    if(T[x1].t<T[x2].t||(T[x1].t==T[x2].t&&T[x1].h<T[x2].h))
    {
        T[x1].r=merge(T[x1].r,x2);
        pushup(x1);
        return x1;
    }
    else
    {
        T[x2].l=merge(x1,T[x2].l);
        pushup(x2);
        return x2;
    }
}
void add(int k,int t)
{
    int x1,x2;
    split(rt,k,x1,x2);
    T[++tot].k=k;
    T[tot].l=T[tot].r=0;
    T[tot].h=rand();
    T[tot].s=T[tot].t=t,T[tot].w=1;
    rt=merge(merge(x1,tot),x2);
}
void remove(int k)
{
    int x1,x2,x3;
    split(rt,k,x1,x3);
    split(x1,k-1,x1,x2);
    x2=merge(T[x2].l,T[x2].r);
    rt=merge(merge(x1,x2),x3);
}
int main()
{
    scanf("%d%d",&n,&m);
    srand(n+m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        add(i,a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int x,k;
        scanf("%d%d",&x,&k);
        remove(x);
        add(x,k);
        printf("%lld\n",T[rt].s);
    }
    return 0;
}