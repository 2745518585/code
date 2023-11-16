#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,rt=0,q=0;
struct splay
{
    int k,a[2],f,s,p;
}T[10000001];
void pushup(int x)
{
    T[x].s=T[T[x].a[0]].s+T[T[x].a[1]].s+1;
}
void pushdown(int x)
{
    if(T[x].p==0) return;
    T[T[x].a[0]].p^=1;
    T[T[x].a[1]].p^=1;
    swap(T[x].a[0],T[x].a[1]);
    T[x].p=0;
}
void rotate(int x)
{
    int y=T[x].f,z=T[y].f,k=T[y].a[1]==x;
    T[z].a[T[z].a[1]==y]=x;
    T[x].f=z;
    T[y].a[k]=T[x].a[k^1];
    T[T[x].a[k^1]].f=y;
    T[x].a[k^1]=y;
    T[y].f=x;
    pushup(x);
    pushup(y);
}
void splay(int x,int k)
{
    while(T[x].f!=k) rotate(x);
    if(k==0) rt=x;
}
void add(int k)
{
    int x=rt,f=0;
    while(x!=0)
    {
        f=x;
        if(k<T[x].k) x=T[x].a[0];
        else x=T[x].a[1];
    }
    x=++q;
    if(f!=0)
    {
        if(k<T[f].k) T[f].a[0]=x;
        else T[f].a[1]=x;
    }
    T[x].k=k;
    T[x].s=1;
    T[x].f=f;
    splay(x,0);
}
int sum(int k)
{
    int x=rt;
    while(x!=0)
    {
        pushdown(x);
        if(k<=T[T[x].a[0]].s) x=T[x].a[0];
        else if(k<=T[T[x].a[0]].s+1)
        {
            splay(x,0);
            return x;
        }
        else
        {
            k-=T[T[x].a[0]].s+1;
            x=T[x].a[1];
        }
    }
}
void print(int x)
{
    if(x==0) return;
    pushdown(x);
    print(T[x].a[0]);
    if(T[x].k>=1&&T[x].k<=n) printf("%d ",T[x].k);
    print(T[x].a[1]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n+1;++i) add(i);
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        l=sum(l);
        r=sum(r+2);
        splay(l,0);
        splay(r,l);
        T[T[r].a[0]].p^=1;
    }
    print(rt);
    return 0;
}