#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10000001;
int n,m,rt=0,q=0,s;
struct splay
{
    int x,a[2],f,s,m,t;
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].a[0]].s+T[T[x].a[1]].s+1;
    T[x].m=max(T[x].t,max(T[T[x].a[0]].m,T[T[x].a[1]].m));
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
void add(int &x,int f,int k,int t)
{
    if(x==0)
    {
        x=++q;
        T[x].x=k;
        T[x].s=1;
        T[x].f=f;
        T[x].t=t;
        splay(x,0);
        return;
    }
    else if(k<T[x].x) add(T[x].a[0],x,k,t);
    else add(T[x].a[1],x,k,t);
}
void build()
{
    add(rt,0,1e9,0);
    add(rt,0,-1e9,0);
}
int find_f(int x,int f,int k)
{
    if(x==0)
    {
        splay(f,0);
        return 0;
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
    if(k>=T[x].x) return find_b(T[x].a[1],x,k);
    int p=find_b(T[x].a[0],x,k);
    if(p==0) return x;
    return p;
}
int sum(int x,int k)
{
    if(x==0) return 0;
    if(k<T[T[x].a[0]].s+1) return sum(T[x].a[0],k);
    if(k<=T[T[x].a[0]].s+1)
    {
        splay(x,0);
        return x;
    }
    return sum(T[x].a[1],k-T[T[x].a[0]].s-1);
}
int num(int k)
{
    splay(find_f(rt,rt,k),0);
    return T[T[rt].a[0]].s+1;
}
int main()
{
    build();
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        int z1=sum(rt,x+1),z2=sum(rt,x+2);
        splay(z1,0);
        splay(z2,z1);
        int t=max(T[T[z1].a[0]].m,T[z1].t)+1;
        T[z2].a[0]=++q;
        T[q].s=1;
        T[q].f=z2;
        T[q].t=t;
        splay(q,0);
        printf("%d\n",max(s,t));
        s=max(s,t);
    }
    return 0;
}