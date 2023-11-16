#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int m,rt,tot;
struct treap
{
    int x,l,r,s,h,t;
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+T[x].t;
}
void rotate_l(int &x)
{
    int p=T[x].r;
    T[x].r=T[p].l;
    T[p].l=x;
    x=p;
    pushup(T[x].l);
    pushup(x);
}
void rotate_r(int &x)
{
    int p=T[x].l;
    T[x].l=T[p].r;
    T[p].r=x;
    x=p;
    pushup(T[x].r);
    pushup(x);
}
void add(int &x,int k)
{
    if(x==0)
    {
        x=++tot;
        T[x].l=T[x].r=0;
        T[x].s=T[x].t=1;
        T[x].x=k;
        T[x].h=rand();
        return;
    }
    if(k==T[x].x) ++T[x].t;
    else if(k<T[x].x) add(T[x].l,k);
    else if(k>T[x].x) add(T[x].r,k);
    if(T[x].l&&T[T[x].l].h<T[x].h) rotate_r(x);
    if(T[x].r&&T[T[x].r].h<T[x].h) rotate_l(x);
    pushup(x);
}
void remove(int &x,int k)
{
    if(x==0) return;
    if(k==T[x].x)
    {
        if(T[x].t>1)
        {
            --T[x].t;
            pushup(x);
            return;
        }
        if(!T[x].l&&!T[x].r)
        {
            x=0;
            return;
        }
        if(T[x].l&&(!T[x].r||T[T[x].l].h<T[T[x].r].h))
        {
            rotate_r(x);
            remove(T[x].r,k);
        }
        else
        {
            rotate_l(x);
            remove(T[x].l,k);
        }
        pushup(x);
        return;
    }
    if(k<T[x].x) remove(T[x].l,k);
    else remove(T[x].r,k);
    pushup(x);
}
int num(int x,int k)
{
    if(x==0) return 1;
    if(k==T[x].x) return T[T[x].l].s+1;
    if(k<T[x].x) return num(T[x].l,k);
    return T[T[x].l].s+T[x].t+num(T[x].r,k);
}
int sum(int x,int k)
{
    if(x==0) return 1e9;
    if(k<=T[T[x].l].s) return sum(T[x].l,k);
    if(k<=T[T[x].l].s+T[x].t) return T[x].x;
    return sum(T[x].r,k-T[T[x].l].s-T[x].t);
}
int find_f(int x,int k)
{
    if(x==0) return 0;
    if(k<=T[x].x) return find_f(T[x].l,k);
    int p=find_f(T[x].r,k);
    if(p==0) return T[x].x;
    return p;
}
int find_b(int x,int k)
{
    if(x==0) return 0;
    if(k>=T[x].x) return find_b(T[x].r,k);
    int p=find_b(T[x].l,k);
    if(p==0) return T[x].x;
    return p;
}
int main()
{
    scanf("%d",&m);
    srand(m);
    for(int i=1;i<=m;++i)
    {
        int z,k;
        scanf("%d%d",&z,&k);
        if(z==1) add(rt,k);
        else if(z==2) remove(rt,k);
        else if(z==3) printf("%d\n",num(rt,k));
        else if(z==4) printf("%d\n",sum(rt,k));
        else if(z==5) printf("%d\n",find_f(rt,k));
        else if(z==6) printf("%d\n",find_b(rt,k));
    }
    return 0;
}