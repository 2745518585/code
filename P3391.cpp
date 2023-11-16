#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10000001;
int n,m,q,rt;
struct tree
{
    int x,l,r,s,h,k;
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+1;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    swap(T[x].l,T[x].r);
    T[T[x].l].k^=1;
    T[T[x].r].k^=1;
    T[x].k=0;
}
void split(int x,int k,int &x1,int &x2)
{
    if(x==0)
    {
        x1=x2=0;
        return;
    }
    pushdown(x);
    if(T[T[x].l].s+1<=k)
    {
        x1=x;
        split(T[x].r,k-T[T[x].l].s-1,T[x].r,x2);
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
    if(x1==0) return x2;
    if(x2==0) return x1;
    if(T[x1].h<T[x2].h)
    {
        pushdown(x1);
        T[x1].r=merge(T[x1].r,x2);
        pushup(x1);
        return x1;
    }
    else
    {
        pushdown(x2);
        T[x2].l=merge(x1,T[x2].l);
        pushup(x2);
        return x2;
    }
}
void add(int k)
{
    int x1,x2;
    split(rt,k,x1,x2);
    T[++q].x=k;
    T[q].s=1;
    T[q].h=rand();
    rt=merge(merge(x1,q),x2);
}
void print(int x)
{
    if(x==0) return;
    pushdown(x);
    print(T[x].l);
    printf("%d ",T[x].x);
    print(T[x].r);
}
int main()
{
    scanf("%d%d",&n,&m);
    srand(m);
    for(int i=1;i<=n;++i) add(i);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int x1,x2,x3;
        split(rt,y,x1,x3);
        split(x1,x-1,x1,x2);
        T[x2].k^=1;
        rt=merge(merge(x1,x2),x3);
    }
    print(rt);
    return 0;
}