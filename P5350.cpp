#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
// #define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=2000001;
const ll P=1e9+7;
int n,m,q,rt;
bool h[N];
struct tree
{
    int x,l,r,s,w,h,k1;
    ll d,k2,k3;
}T[N];
void pushdown(int x);
void clear(int x)
{
    if(x==0) return;
    pushdown(x);
    clear(T[x].l);
    h[x]=true;
    clear(T[x].r);
}
void copy(int &x)
{
    if(x==0) return;
    if(q>=1.5e6)
    {
        for(int i=1;i<=q;++i) h[i]=false;
        clear(rt);
        q=0;
    }
    ++q;
    while(h[q]==true) ++q;
    T[q]=T[x];
    x=q;
}
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+1;
    T[x].d=(T[T[x].l].d+T[T[x].r].d+T[x].w)%P;
}
void pushdown(int x)
{
    if(x==0) return;
    if(T[x].l) copy(T[x].l);
    if(T[x].r) copy(T[x].r);
    if(T[x].k1!=0)
    {
        if(T[x].l)
        {
            T[T[x].l].k1^=1;
            swap(T[T[x].l].l,T[T[x].l].r);
        }
        if(T[x].r)
        {
            T[T[x].r].k1^=1;
            swap(T[T[x].r].l,T[T[x].r].r);
        }
        T[x].k1=0;
    }
    if(T[x].k2!=-1)
    {
        if(T[x].l)
        {
            T[T[x].l].w=T[x].k2;
            T[T[x].l].d=T[x].k2*T[T[x].l].s%P;
            T[T[x].l].k2=T[x].k2;
            T[T[x].l].k3=0;
        }
        if(T[x].r)
        {
            T[T[x].r].w=T[x].k2;
            T[T[x].r].d=T[x].k2*T[T[x].r].s%P;
            T[T[x].r].k2=T[x].k2;
            T[T[x].r].k3=0;
        }
        T[x].k2=-1;
    }
    if(T[x].k3!=0)
    {
        if(T[x].l)
        {
            T[T[x].l].w=(T[T[x].l].w+T[x].k3)%P;
            T[T[x].l].d=(T[T[x].l].d+T[x].k3*T[T[x].l].s%P)%P;
            T[T[x].l].k3=(T[T[x].l].k3+T[x].k3)%P;
        }
        if(T[x].r)
        {
            T[T[x].r].w=(T[T[x].r].w+T[x].k3)%P;
            T[T[x].r].d=(T[T[x].r].d+T[x].k3*T[T[x].r].s%P)%P;
            T[T[x].r].k3=(T[T[x].r].k3+T[x].k3)%P;
        }
        T[x].k3=0;
    }
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
        split(T[x1].r,k-T[T[x].l].s-1,T[x1].r,x2);
        copy(x1);
        pushup(x1);
    }
    else
    {
        x2=x;
        split(T[x2].l,k,x1,T[x2].l);
        copy(x2);
        pushup(x2);
    }
}
int merge(int x1,int x2)
{
    pushdown(x1);
    pushdown(x2);
    if(x1==0) return x2;
    if(x2==0) return x1;
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
void add(int x,int k)
{
    int x1,x2;
    split(rt,x,x1,x2);
    ++q;
    T[q].k1=T[q].k3=0;
    T[q].k2=-1;
    T[q].w=T[q].d=k;
    T[q].s=1;
    T[q].h=rand();
    rt=merge(merge(x1,q),x2);
}
void print(int x)
{
    if(x==0) return;
    pushdown(x);
    print(T[x].l);
    printf("%lld ",(T[x].w%P+P)%P);
    print(T[x].r);
}
int main()
{
    n=read(),m=read();
    srand(n*m);
    for(int i=1;i<=n;++i)
    {
        add(i-1,read());
    }
    for(int i=1;i<=m;++i)
    {
        int z=read();
        if(z==1)
        {
            int x=read(),y=read();
            int x1,x2,x3;
            split(rt,y,x1,x3);
            split(x1,x-1,x1,x2);
            printf("%lld\n",(T[x2].d%P+P)%P);
            rt=merge(merge(x1,x2),x3);
        }
        else if(z==2)
        {
            int x=read(),y=read();
            ll k=read();
            int x1,x2,x3;
            split(rt,y,x1,x3);
            split(x1,x-1,x1,x2);
            copy(x2);
            T[x2].w=k;
            T[x2].d=k*T[x2].s%P;
            T[x2].k2=k;
            T[x2].k3=0;
            rt=merge(merge(x1,x2),x3);
        }
        else if(z==3)
        {
            int x=read(),y=read();
            ll k=read();
            int x1,x2,x3;
            split(rt,y,x1,x3);
            split(x1,x-1,x1,x2);
            copy(x2);
            T[x2].w=(T[x2].w+k)%P;
            T[x2].d=(T[x2].d+k*T[x2].s%P)%P;
            T[x2].k3=(T[x2].k3+k)%P;
            rt=merge(merge(x1,x2),x3);
        }
        else if(z==4)
        {
            int l1=read(),r1=read(),l2=read(),r2=read();
            int x1,x2,x3,x4,x5;
            split(rt,max(r1,r2),x1,x5);
            split(x1,max(l1,l2)-1,x1,x4);
            split(x1,min(r1,r2),x1,x3);
            split(x1,min(l1,l2)-1,x1,x2);
            if(l1<l2)
            {
                x4=x2;
                copy(x4);
            }
            else
            {
                x2=x4;
                copy(x2);
            }
            rt=merge(merge(merge(merge(x1,x2),x3),x4),x5);
        }
        else if(z==5)
        {
            int l1=read(),r1=read(),l2=read(),r2=read();
            int x1,x2,x3,x4,x5;
            split(rt,max(r1,r2),x1,x5);
            split(x1,max(l1,l2)-1,x1,x4);
            split(x1,min(r1,r2),x1,x3);
            split(x1,min(l1,l2)-1,x1,x2);
            rt=merge(merge(merge(merge(x1,x4),x3),x2),x5);
        }
        else if(z==6)
        {
            int x=read(),y=read();
            int x1,x2,x3;
            split(rt,y,x1,x3);
            split(x1,x-1,x1,x2);
            copy(x2);
            T[x2].k1^=1;
            swap(T[x2].l,T[x2].r);
            rt=merge(merge(x1,x2),x3);
        }
    }
    print(rt);
    return 0;
}