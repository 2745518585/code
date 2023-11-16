#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001,inf=100000000;
int n,m,rt=0,q=0;
struct splay
{
    int x,a[2],f,s,k,t,k1,k2;
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].a[0]].s+T[T[x].a[1]].s+1;
    T[x].k=max(T[x].t,max(T[T[x].a[0]].k,T[T[x].a[1]].k));
}
void pushdown(int x)
{
    if(T[x].k1!=0)
    {
        if(T[x].a[0])
        {
            T[T[x].a[0]].t+=T[x].k1;
            T[T[x].a[0]].k+=T[x].k1;
            T[T[x].a[0]].k1+=T[x].k1;
        }
        if(T[x].a[1])
        {
            T[T[x].a[1]].t+=T[x].k1;
            T[T[x].a[1]].k+=T[x].k1;
            T[T[x].a[1]].k1+=T[x].k1;
        }
        T[x].k1=0;
    }
    if(T[x].k2!=0)
    {
        if(T[x].a[0])
        {
            swap(T[T[x].a[0]].a[0],T[T[x].a[0]].a[1]);
            T[T[x].a[0]].k2^=1;
        }
        if(T[x].a[1])
        {
            swap(T[T[x].a[1]].a[0],T[T[x].a[1]].a[1]);
            T[T[x].a[1]].k2^=1;
        }
        T[x].k2=0;
    }
}
void rotate(int x)
{
    int y=T[x].f,z=T[y].f,k=(T[y].a[1]==x);
    T[z].a[T[z].a[1]==y]=x;
    T[x].f=z;
    T[y].a[k]=T[x].a[k^1];
    T[T[x].a[k^1]].f=y;
    T[x].a[k^1]=y;
    T[y].f=x;
    pushup(y);
    pushup(x);
}
void splay(int x,int k)
{
    while(T[x].f!=k)
    {
        int y=T[x].f,z=T[y].f;
        if(z!=k)
        {
            if((T[y].a[0]==x)^(T[z].a[0]==y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if(k==0) rt=x;
}
void add(int &x,int f,int k,int t)
{
    if(x==0)
    {
        x=++q;
        T[x].x=k;
        T[x].s=1;
        T[x].t=t;
        T[x].k1=T[x].k2=0;
        T[x].f=f;
        splay(x,0);
        return;
    }
    if(k<T[x].x) add(T[x].a[0],x,k,t);
    else add(T[x].a[1],x,k,t);
}
void build()
{
    rt=q=1;
    T[1].f=0;
    T[1].s=1;
    T[1].t=T[1].k=-inf;
    T[1].k1=T[1].k2=0;
    T[1].x=inf;
    add(rt,0,-inf,-inf);
}
int sum(int x,int k)
{
    if(x==0) return 0;
    pushdown(x);
    if(k<T[T[x].a[0]].s+1) return sum(T[x].a[0],k);
    if(k<=T[T[x].a[0]].s+1)
    {
        splay(x,0);
        return x;
    }
    return sum(T[x].a[1],k-T[T[x].a[0]].s-1);
}
int main()
{
    build();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        add(rt,0,i,0);
    }
    T[0].k=-1e9;
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            int h=sum(rt,x),g=sum(rt,y+2);
            splay(h,0);
            splay(g,h);
            T[T[g].a[0]].t+=k;
            T[T[g].a[0]].k+=k;
            T[T[g].a[0]].k1+=k;
            pushup(g);
            pushup(h);
        }
        else if(z==2)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            int h=sum(rt,x),g=sum(rt,y+2);
            splay(h,0);
            splay(g,h);
            swap(T[T[g].a[0]].a[0],T[T[g].a[0]].a[1]);
            T[T[g].a[0]].k2^=1;
            pushdown(T[g].a[0]);
            pushdown(T[g].a[0]);
            pushup(g);
            pushup(h);
        }
        else if(z==3)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            int h=sum(rt,x),g=sum(rt,y+2);
            splay(h,0);
            splay(g,h);
            printf("%d\n",T[T[g].a[0]].k);
        }
    }
    return 0;
}