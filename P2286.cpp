#include<cstdio>
#include<algorithm>
using namespace std;
int m,r=0,q=0;
struct treap
{
    int x,l,r,s,h,t;
}T1[1000001],T2[1000001];
void pushup(treap T[],int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+T[x].t;
}
void rotate_l(treap T[],int &x)
{
    int p=T[x].r;
    T[x].r=T[p].l;
    T[p].l=x;
    T[p].s=T[x].s;
    x=p;
    pushup(T,x);
    pushup(T,T[x].l);
}
void rotate_r(treap T[],int &x)
{
    int p=T[x].l;
    T[x].l=T[p].r;
    T[p].r=x;
    T[p].s=T[x].s;
    x=p;
    pushup(T,x);
    pushup(T,T[x].r);
}
void add(treap T[],int &x,int k)
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
    else if(k<T[x].x) add(T,T[x].l,k);
    else if(k>T[x].x) add(T,T[x].r,k);
    if(T[x].l!=0&&T[x].h>T[T[x].l].h) rotate_r(T,x);
    if(T[x].r!=0&&T[x].h>T[T[x].r].h) rotate_l(T,x);
    pushup(T,x);
}
void remove(treap T[],int &x,int k)
{
    if(x==0) return;
    if(k==T[x].x)
    {
        if(T[x].t>1)
        {
        	--T[x].t;
            pushup(T,x);
            return;
        }
        if(T[x].l==0&&T[x].r==0)
        {
            x=0;
            return;
        }
        if(T[x].l!=0&&(T[x].r==0||T[T[x].l].h<T[T[x].r].h))
        {
            rotate_r(T,x);
            remove(T,T[x].r,k);
        }
        else
        {   
            rotate_l(T,x);
            remove(T,T[x].l,k);
        }
        pushup(T,x);
        return;
    }
    if(k<T[x].x) remove(T,T[x].l,k);
    else remove(T,T[x].r,k);
    pushup(T,x);
}
int find_f(treap T[],int x,int k)
{
    if(x==0) return 1e9;
    if(k<=T[x].x) return find_f(T,T[x].l,k);
    int p=find_f(T,T[x].r,k);
    if(p==1e9) return T[x].x;
    return p;
}
int find_b(treap T[],int x,int k)
{
    if(x==0) return 1e9;
    if(k>=T[x].x) return find_b(T,T[x].r,k);
    int p=find_b(T,T[x].l,k);
    if(p==1e9) return T[x].x;
    return p;
}
int main()
{
    srand(0);
    scanf("%d",&m);
    int s=0;
    for(int i=1;i<=m;++i)
    {
        int z,k;
        scanf("%d%d",&z,&k);
        if(z==0)
        {
            if(T2[r].s!=0)
            {
                int x=find_f(T2,r,k),y=find_b(T2,r,k);
                if(abs(k-x)<=abs(k-y))
                {
                    s+=abs(k-x);
                    remove(T2,r,x);
                }
                else
                {
                    s+=abs(k-y);
                    remove(T2,r,y);
                }
            }
            else
            {
                add(T1,r,k);
            }
        }
        else if(z==1)
        {
            if(T1[r].s!=0)
            {
                int x=find_f(T1,r,k),y=find_b(T1,r,k);
                if(abs(k-x)<=abs(k-y))
                {
                    s+=abs(k-x);
                    remove(T1,r,x);
                }
                else
                {
                    s+=abs(k-y);
                    remove(T1,r,y);
                }
            }
            else
            {
                add(T2,r,k);
            }
        }
        s%=1000000;
    }
    printf("%d",s);
    return 0;
}