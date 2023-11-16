#include<cstdio>
#include<algorithm>
#include<ctime>
using namespace std;
typedef long long ll;
int m,r=0,q=0;
struct treap
{
    int x,l,r,s,w,h;
}T[1000001];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+1;
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
void add(int &x,int k,int w)
{
    if(x==0)
    {
        x=++q;
        T[x].l=T[x].r=0;
        T[x].s=1;
        T[x].x=k;
        T[x].w=w;
        T[x].h=rand()*rand()%1000000+1;
        return;
    }
    if(k==T[x].x) return;
    else if(k<T[x].x) add(T[x].l,k,w);
    else if(k>T[x].x) add(T[x].r,k,w);  
    if(T[x].l!=0&&T[x].h>T[T[x].l].h) rotate_r(x);
    if(T[x].r!=0&&T[x].h>T[T[x].r].h) rotate_l(x);
    pushup(x);
}
void remove1(int &x)
{
    if(T[x].l!=0) remove1(T[x].l);
    else x=T[x].r;
}
void remove2(int &x)
{
    if(T[x].r!=0) remove2(T[x].r);
    else x=T[x].l;
}
ll abc1(int x)
{
    if(x==0) return 0;
    return abc1(T[x].l)+abc1(T[x].r)+T[x].x;
}
ll abc2(int x)
{
    if(x==0) return 0;
    return abc2(T[x].l)+abc2(T[x].r)+T[x].w;
}
int main()
{
    srand(time(NULL));
    while(1)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int k,q;
            scanf("%d%d",&q,&k);
            add(r,k,q);
        }
        else if(z==2) remove1(r);
        else if(z==3) remove2(r);
        else if(z==-1) break;
    }
    printf("%lld %lld",abc2(r),abc1(r));
    return 0;
}
