#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,r=0,q=0;
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
        T[x].h=rand();
        return;
    }
    if(k==T[x].x) ++T[x].t;
    else if(k<T[x].x) add(T[x].l,k);
    else if(k>T[x].x) add(T[x].r,k);
    if(T[x].l!=0&&T[x].h>T[T[x].l].h) rotate_r(x);
    if(T[x].r!=0&&T[x].h>T[T[x].r].h) rotate_l(x);
    pushup(x);
}
int sum(int x,int k)
{
    if(x==0) return 1e9;
    if(k<T[T[x].l].s+1) return sum(T[x].l,k);
    if(k<=T[T[x].l].s+T[x].t) return T[x].x;
    return sum(T[x].r,k-T[T[x].l].s-T[x].t);
}
int main()
{
    srand(0);
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        add(r,x);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        char z[10];
        cin>>z;
        if(z[0]=='a')
        {
            int k;
            scanf("%d",&k);
            add(r,k);
        }
        else if(z[0]=='m')
        {
            printf("%d\n",sum(r,(T[r].s+1)/2));
        }
    }
    return 0;
}