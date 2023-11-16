#include<cstdio>
#include<algorithm>
using namespace std;
int n,r=0,q=0;
struct treap
{
    int x,l,r,s,h,t;
}T[1000001];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+T[x].t;
}
void rotate_l(int &x)
{
    int p=T[x].r;
    T[x].r=T[p].l;
    T[p].l=x;
    T[p].s=T[x].s;
    x=p;
    pushup(x);
    pushup(T[x].l);
}
void rotate_r(int &x)
{
    int p=T[x].l;
    T[x].l=T[p].r;
    T[p].r=x;
    T[p].s=T[x].s;
    x=p;
    pushup(x);
    pushup(T[x].r);
}
void add(int &x,int k)
{
    if(x==0)
    {
        x=++q;
        T[x].l=T[x].r=0;
        T[x].s=T[x].t=1;
        T[x].x=k;
        T[x].h=rand()*rand()%1000000+1;
        return;
    }
    if(k==T[x].x) ++T[x].t;
    else if(k<T[x].x) add(T[x].l,k);
    else if(k>T[x].x) add(T[x].r,k);
    if(T[x].l!=0&&T[x].h>T[T[x].l].h) rotate_r(x);
    if(T[x].r!=0&&T[x].h>T[T[x].r].h) rotate_l(x);
    pushup(x);
}
int find_f(int x,int k)
{
    if(x==0) return -1e9;
    if(k==T[x].x&&T[x].t>1) return T[x].x;
    if(k<=T[x].x) return find_f(T[x].l,k);
    int p=find_f(T[x].r,k);
    if(p==-1e9) return T[x].x;
    return p;
}
int find_b(int x,int k)
{
    if(x==0) return 1e9;
    if(k==T[x].x&&T[x].t>1) return T[x].x;
    if(k>=T[x].x) return find_b(T[x].r,k);
    int p=find_b(T[x].l,k);
    if(p==1e9) return T[x].x;
    return p;
}
int main()
{
    srand(0);
    scanf("%d",&n);
    int s=0;
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        add(r,x);
        if(i==1) s+=x;
        else s+=min(x-find_f(r,x),find_b(r,x)-x);
    }
    printf("%d",s);
    return 0;
}