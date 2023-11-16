#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=20000001;
int n,m,q,rt[N];
struct tree
{
    int x,l,r,s,h,k;
    ll d;
}T[N];
void copy(int &x)
{
    if(x==0) return;
    T[++q]=T[x];
    x=q;
}
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+1;
    T[x].d=T[T[x].l].d+T[T[x].r].d+T[x].x;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    copy(T[x].l);
    copy(T[x].r);
    swap(T[x].l,T[x].r);
    if(T[x].l) T[T[x].l].k^=1;
    if(T[x].r) T[T[x].r].k^=1;
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
        copy(x1);
        split(T[x1].r,k-T[T[x].l].s-1,T[x1].r,x2);
        pushup(x1);
    }
    else
    {
        x2=x;
        copy(x2);
        split(T[x2].l,k,x1,T[x2].l);
        pushup(x2);
    }
}
int merge(int x1,int x2)
{
    if(x1==0) return x2;
    if(x2==0) return x1;
    pushdown(x1);
    pushdown(x2);
    if(T[x1].h<T[x2].h)
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
void add(int rt1,int &rt2,int x,int k)
{
    int x1,x2;
    split(rt1,x,x1,x2);
    T[q].x=T[++q].d=k;
    T[q].s=1;
    T[q].h=rand();
    T[q].k=0;
    rt2=merge(merge(x1,q),x2);
}
void remove(int rt1,int &rt2,int k)
{
    int x1,x2,x3;
    split(rt1,k,x1,x3);
    split(x1,k-1,x1,x2);
    x2=merge(T[x2].l,T[x2].r);
    rt2=merge(merge(x1,x2),x3);
}
int main()
{
    scanf("%d",&m);
    srand(m);
    ll las=0;
    for(int i=1;i<=m;++i)
    {
        int p,z;
        scanf("%d%d",&p,&z);
        if(z==1)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            x^=las,k^=las;
            add(rt[p],rt[i],x,k);
        }
        else if(z==2)
        {
            rt[i]=++q;
            T[rt[i]]=T[rt[p]];
            int x;
            scanf("%d",&x);
            x^=las;
            remove(rt[p],rt[i],x);
        }
        else if(z==3)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            x^=las,y^=las;
            int x1,x2,x3;
            split(rt[p],y,x1,x3);
            split(x1,x-1,x1,x2);
            T[x2].k^=1;
            rt[i]=merge(merge(x1,x2),x3);
        }
        else if(z==4)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            x^=las,y^=las;
            int x1,x2,x3;
            split(rt[p],y,x1,x3);
            split(x1,x-1,x1,x2);
            printf("%lld\n",las=T[x2].d);
            rt[i]=merge(merge(x1,x2),x3);
        }
    }
    return 0;
}