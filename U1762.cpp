#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,rt=0,q=0;
struct splay
{
    int x,a[2],f,s,t;
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].a[0]].s+T[T[x].a[1]].s+T[x].t;
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
    pushup(y);
    pushup(x);
}
void splay(int x,int k)
{
    while(T[x].f!=k)
    {
        int y=T[x].f,z=T[T[x].f].f;
        if(z!=k)
        {
            if((T[y].a[0]==x)^(T[z].a[0]==y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if(k==0) rt=x;
}
void add(int &x,int f,int k)
{
    if(x==0)
    {
        x=++q;
        T[x].x=k;
        T[x].t=T[x].s=1;
        T[x].f=f;
        splay(x,0);
        return;
    }
    if(T[x].x==k)
    {
        ++T[x].t;
        ++T[x].s;
        splay(x,0);
        return;
    }
    else if(k<T[x].x) add(T[x].a[0],x,k);
    else add(T[x].a[1],x,k);
}
void build()
{
    add(rt,0,1e9);
    add(rt,0,-1e9);
}
int find_f(int x,int f,int k)
{
    if(x==0)
    {
        splay(f,0);
        return 0;
    }
    if(k==T[x].x&&T[x].t>1)
    {
        splay(x,0);
        return x;
    }
    if(k<=T[x].x) return find_f(T[x].a[0],x,k);
    int p=find_f(T[x].a[1],x,k);
    if(p==0) return x;
    return p;
}
int find_b(int x,int f,int k)
{
    if(x==0)
    {
        splay(f,0);
        return 0;
    }
    if(k==T[x].x&&T[x].t>1)
    {
        splay(x,0);
        return x;
    }
    if(k>=T[x].x) return find_b(T[x].a[1],x,k);
    int p=find_b(T[x].a[0],x,k);
    if(p==0) return x;
    return p;
}
void remove(int k)
{
    int x=find_f(rt,0,k),y=find_b(rt,0,k);
    splay(x,0);
    splay(y,x);
    --T[T[y].a[0]].t;
    --T[T[y].a[0]].s;
    if(T[T[y].a[0]].t==0)
    {
        T[T[y].a[0]].x=0;
        T[y].a[0]=0;
    }
    splay(y,0);
}
int sum(int x,int k)
{
    if(x==0) return 0;
    if(k<T[T[x].a[0]].s+1) return sum(T[x].a[0],k);
    if(k<=T[T[x].a[0]].s+T[x].t)
    {
        splay(x,0);
        return x;
    }
    return sum(T[x].a[1],k-T[T[x].a[0]].s-T[x].t);
}
int num(int k)
{
    splay(find_f(rt,rt,k),0);
    return T[T[rt].a[0]].s+T[rt].t;
}
int main()
{
    build();
    scanf("%d",&n);
    int s=0;
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        add(rt,0,x);
        if(i==1) s+=x;
        else s+=min(x-T[find_f(rt,0,x)].x,T[find_b(rt,0,x)].x-x);
    }
    printf("%d",s);
    return 0;
}