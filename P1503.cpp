#include<iostream>
#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
int n,m,r=0,q=0;
bool h[1000001];
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
        if(T[x].l==0&&T[x].r==0)
        {
            x=0;
            return;
        }
        if(T[x].l!=0&&(T[x].r==0||T[T[x].l].h<T[T[x].r].h))
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
    srand(0);
    scanf("%d%d",&n,&m);
    stack<int> S;
    add(r,0);
    add(r,n+1);
    for(int i=1;i<=m;++i)
    {
        char z;
        cin>>z;
        if(z=='D')
        {
            int k;
            scanf("%d",&k);
            h[k]=true;
            S.push(k);
            add(r,k);
        }
        else if(z=='R')
        {
            remove(r,S.top());
            h[S.top()]=false;
            S.pop();
        }
        else if(z=='Q')
        {
            int k;
            scanf("%d",&k);
            if(h[k]==true) printf("0\n");
            else printf("%d\n",find_b(r,k)-find_f(r,k)-1);
        }
    }
    return 0;
}