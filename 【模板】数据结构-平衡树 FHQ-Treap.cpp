#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10000001;
int m,tot,rt;
struct tree
{
    int k,l,r,s,h;
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+1;
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
void add(int k)
{
    int x1,x2;
    split(rt,k,x1,x2);
    T[++tot].k=k;
    T[tot].l=T[tot].r=0;
    T[tot].s=1;
    T[tot].h=rand();
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
int num(int k)
{
    int x1,x2;
    split(rt,k-1,x1,x2);
    int z=T[x1].s+1;
    rt=merge(x1,x2);
    return z;
}
int sum(int x,int k)
{
    if(x==0) return 0;
    if(k<=T[T[x].l].s) return sum(T[x].l,k);
    else if(k<=T[T[x].l].s+1) return x;
    else return sum(T[x].r,k-T[T[x].l].s-1);
}
int find_f(int k)
{
    int x1,x2;
    split(rt,k-1,x1,x2);
    int z=sum(x1,T[x1].s);
    rt=merge(x1,x2);
    return z;
}
int find_b(int k)
{
    int x1,x2;
    split(rt,k,x1,x2);
    int z=sum(x2,1);
    rt=merge(x1,x2);
    return z;
}
int main()
{
    scanf("%d",&m);
    srand(m);
    for(int i=1;i<=m;++i)
    {
        int z,k;
        scanf("%d%d",&z,&k);
        if(z==1) add(k);
        if(z==2) remove(k);
        if(z==3) printf("%d\n",num(k));
        if(z==4) printf("%d\n",T[sum(rt,k)].k);
        if(z==5) printf("%d\n",T[find_f(k)].k);
        if(z==6) printf("%d\n",T[find_b(k)].k);
    }
    return 0;
}