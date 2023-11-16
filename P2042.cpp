#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001,inf=100000000;
int n,m,rt=0,q=0;
bool h[N];
struct splay
{
    int x,a[2],f,s,t,k,lk,rk,mk,k0,k1,k2;
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].a[0]].s+T[T[x].a[1]].s+1;
    T[x].k=T[T[x].a[0]].k+T[T[x].a[1]].k+T[x].t;
    T[x].lk=max(T[T[x].a[0]].lk,T[T[x].a[0]].k+T[x].t+T[T[x].a[1]].lk);
    T[x].rk=max(T[T[x].a[1]].rk,T[T[x].a[1]].k+T[x].t+T[T[x].a[0]].rk);
    T[x].mk=max(max(T[T[x].a[0]].mk,T[T[x].a[1]].mk),T[T[x].a[0]].rk+T[x].t+T[T[x].a[1]].lk);
}
void pushdown(int x)
{
    if(T[x].k0!=0)
    {
        if(T[x].a[0]&&T[T[x].a[0]].k0<T[x].k0)
        {
            T[T[x].a[0]].t=T[x].k1;
            T[T[x].a[0]].k=T[T[x].a[0]].s*T[x].k1;
            T[T[x].a[0]].k1=T[x].k1;
            T[T[x].a[0]].k0=T[x].k0;
            if(T[x].k1<0) T[T[x].a[0]].lk=T[T[x].a[0]].rk=0,T[T[x].a[0]].mk=T[x].k1;
            else T[T[x].a[0]].lk=T[T[x].a[0]].rk=T[T[x].a[0]].mk=T[T[x].a[0]].k;
        }
        if(T[x].a[1]&&T[T[x].a[1]].k0<T[x].k0)
        {
            T[T[x].a[1]].t=T[x].k1;
            T[T[x].a[1]].k=T[T[x].a[1]].s*T[x].k1;
            T[T[x].a[1]].k1=T[x].k1;
            T[T[x].a[1]].k0=T[x].k0;
            if(T[x].k1<0) T[T[x].a[1]].lk=T[T[x].a[1]].rk=0,T[T[x].a[1]].mk=T[x].k1;
            else T[T[x].a[1]].lk=T[T[x].a[1]].rk=T[T[x].a[1]].mk=T[T[x].a[1]].k;
        }
        T[x].k0=T[x].k1=0;
    }
    if(T[x].k2!=0)
    {
        if(T[x].a[0])
        {
            swap(T[T[x].a[0]].a[0],T[T[x].a[0]].a[1]);
            swap(T[T[x].a[0]].lk,T[T[x].a[0]].rk);
            T[T[x].a[0]].k2^=1;
        }
        if(T[x].a[1])
        {
            swap(T[T[x].a[1]].a[0],T[T[x].a[1]].a[1]);
            swap(T[T[x].a[1]].lk,T[T[x].a[1]].rk);
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
void check(int x)
{
    if(x==0) return;
    h[x]=true;
    check(T[x].a[0]);
    check(T[x].a[1]);
}
void add(int &x,int f,int k,int t)
{
    if(x==0)
    {
        if(q>=1500000)
        {
            for(int i=1;i<=q;++i) h[i]=false;
            check(rt);
            q=0;
        }
        while(h[q+1]==true) ++q;
        x=++q;
        h[q]=true;
        T[x].x=k;
        T[x].s=1;
        T[x].t=T[x].k=T[x].mk=t;
        T[x].lk=T[x].rk=max(t,0);
        T[x].k0=T[x].k1=T[x].k2=0;
        T[x].a[0]=T[x].a[1]=0;
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
    T[1].t=T[1].k=T[1].mk=-inf;
    T[1].lk=T[1].rk=0;
    T[1].k0=T[1].k1=T[1].k2=0;
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
        int x;
        scanf("%d",&x);
        add(rt,0,i,x);
    }
    for(int i=1;i<=m;++i)
    {
        char z[20];
        scanf("%s",z);
        T[0].mk=-inf;
        if(z[0]=='I')
        {
            int d,k;
            scanf("%d%d",&d,&k);
            int h=sum(rt,d+1),g=sum(rt,d+2);
            splay(h,0);
            splay(g,h);
            for(int i=1;i<=k;++i)
            {
                int x;
                scanf("%d",&x);
                add(T[g].a[0],g,i,x);
            }
        }
        else if(z[0]=='D')
        {
            int x,k;
            scanf("%d%d",&x,&k);
            if(T[rt].s<x+k+1) k=T[rt].s-x-1;
            int h=sum(rt,x),g=sum(rt,x+k+1);
            splay(h,0);
            splay(g,h);
            T[T[g].a[0]].f=0;
            T[g].a[0]=0;
            pushup(g);
            pushup(h);
        }
        else if(z[0]=='M'&&z[2]=='K')
        {
            int x,k,c;
            scanf("%d%d%d",&x,&k,&c);
            if(T[rt].s<x+k+1) k=T[rt].s-x-1;
            int h=sum(rt,x),g=sum(rt,x+k+1);
            splay(h,0);
            splay(g,h);
            T[T[g].a[0]].t=c;
            T[T[g].a[0]].k=T[T[g].a[0]].s*c;
            T[T[g].a[0]].k1=c;
            T[T[g].a[0]].k0=i;
            if(c<0) T[T[g].a[0]].lk=T[T[g].a[0]].rk=0,T[T[g].a[0]].mk=c;
            else T[T[g].a[0]].lk=T[T[g].a[0]].rk=T[T[g].a[0]].mk=T[T[g].a[0]].k;
            pushup(g);
            pushup(h);
        }
        else if(z[0]=='R')
        {
            int x,k;
            scanf("%d%d",&x,&k);
            if(T[rt].s<x+k+1) k=T[rt].s-x-1;
            int h=sum(rt,x),g=sum(rt,x+k+1);
            splay(h,0);
            splay(g,h);
            swap(T[T[g].a[0]].a[0],T[T[g].a[0]].a[1]);
            swap(T[T[g].a[0]].lk,T[T[g].a[0]].rk);
            T[T[g].a[0]].k2^=1;
            pushdown(T[g].a[0]);
            pushdown(T[g].a[0]);
            pushup(g);
            pushup(h);
        }
        else if(z[0]=='G')
        {
               int x,k;
            scanf("%d%d",&x,&k);
            if(T[rt].s<x+k+1) k=T[rt].s-x-1;
            int h=sum(rt,x),g=sum(rt,x+k+1);
            splay(h,0);
            splay(g,h);
            printf("%d\n",T[T[g].a[0]].k);
        }
        else if(z[0]=='M'&&z[2]=='X')
        {
            int h=sum(rt,1),g=sum(rt,T[rt].s);
            splay(h,0);
            splay(g,h);
            printf("%d\n",T[T[g].a[0]].mk);
        }
//        for(int i=2;i<=T[rt].s-1;++i)
//        {
//            printf("%d ",T[sum(rt,i)].t);
//        }
//        printf("\n");
    }
    return 0;
}