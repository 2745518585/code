#include<cstdio>
#include<algorithm>
#include<ctime>
using namespace std;
const int N=20000001;
int m,q=0,rt[N];
struct tree
{
    int x,l,r,s,h,t; 
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+T[x].t;
}
void copy(int &x)
{
    if(x==0) return;
    T[++q]=T[x];
    x=q;
}
void rotate_l(int &x)
{
    copy(T[x].l);
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
    copy(T[x].r);
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
    else if(k<T[x].x) copy(T[x].l),add(T[x].l,k);
    else if(k>T[x].x) copy(T[x].r),add(T[x].r,k);
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
    if(k<T[x].x) copy(T[x].l),remove(T[x].l,k);
    else copy(T[x].r),remove(T[x].r,k);
    pushup(x);
}
bool check(int x,int k)
{
    if(x==0) return false;
    if(k<T[x].x) return check(T[x].l,k);
    if(k>T[x].x) return check(T[x].r,k);
    return true;
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
    if(k<T[T[x].l].s+1) return sum(T[x].l,k);
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
    srand(time(NULL));
    scanf("%d",&m);
    add(rt[0],2147483647);
    add(rt[0],-2147483647);
    for(int i=1;i<=m;++i)
    {
        int x,z,k;
        scanf("%d%d%d",&x,&z,&k);
        if(z==1)
        {
            rt[i]=++q;
            T[rt[i]]=T[rt[x]];
            add(rt[i],k);
        }
        else if(z==2)
        {
            if(check(rt[x],k)==false)
            {
                rt[i]=rt[x];
                continue;
            }
            rt[i]=++q;
            T[rt[i]]=T[rt[x]];
            remove(rt[i],k);
        }
        else if(z==3) printf("%d\n",num(rt[i]=rt[x],k)-1);
        else if(z==4) printf("%d\n",sum(rt[i]=rt[x],k+1));
        else if(z==5) printf("%d\n",find_f(rt[i]=rt[x],k));
        else if(z==6) printf("%d\n",find_b(rt[i]=rt[x],k));
    }
    return 0;
}