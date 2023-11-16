#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001;
int n,m,q=0;
struct splay
{
    int x,a[2],f,s,t,k;
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].a[0]].s^T[T[x].a[1]].s^T[x].t;
}
bool check(int x)
{
    return T[T[x].f].a[0]!=x&&T[T[x].f].a[1]!=x;
}
void turn(int x)
{
    swap(T[x].a[0],T[x].a[1]);
    T[x].k^=1;
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    if(T[x].a[0]) turn(T[x].a[0]);
    if(T[x].a[1]) turn(T[x].a[1]);
    T[x].k=0;
}
void rotate(int x)
{
    int y=T[x].f,z=T[y].f,k=T[y].a[1]==x;
    if(!check(y)) T[z].a[T[z].a[1]==y]=x;
    T[x].f=z;
    T[y].a[k]=T[x].a[k^1];
    T[T[x].a[k^1]].f=y;
    T[x].a[k^1]=y;
    T[y].f=x;
    pushup(y);
    pushup(x);
}
void splay(int x)
{
    int p[N],t=0,d=x;
    p[++t]=x;
    while(!check(d)) p[++t]=d=T[d].f;
    for(int i=t;i>=1;--i) pushdown(p[i]);
    while(!check(x))
    {
        int y=T[x].f,z=T[T[x].f].f;
        if(!check(y))
        {
            if(((T[y].a[0]==x)^(T[z].a[0]==y))==1) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    pushup(x);
}
void access(int x)
{
    int y=0;
    while(x!=0)
    {
        splay(x);
        T[x].a[1]=y;
        pushup(x);
        y=x;
        x=T[x].f;
    }
}
void makeroot(int x)
{
    access(x);
    splay(x);
    turn(x);
}
int findroot(int x)
{
    access(x);
    splay(x);
    while(T[x].a[0]!=0)
    {
        pushdown(x);
        x=T[x].a[0];
    }
    splay(x);
    return x;
}
void get(int x,int y)
{
    makeroot(y);
    access(x);
    splay(x);
}
void add(int x,int y)
{
    if(findroot(x)==findroot(y)) return;
    makeroot(x);
    T[x].f=y;
}
void cut(int x,int y)
{
    makeroot(x);
    if(findroot(y)==x&&T[y].f==x&&T[y].a[0]==0)
    {
        T[x].a[1]=T[y].f=0;
        pushup(x);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&T[i].t);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y,z;
        scanf("%d%d%d",&z,&x,&y);
        if(z==0)
        {
            get(x,y);
            printf("%d\n",T[x].s);
        }
        else if(z==1) add(x,y);
        else if(z==2) cut(x,y);
        else if(z==3)
        {
            splay(x);
            T[x].t=y;
        }
    }
    return 0;
}