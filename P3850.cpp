#include<cstdio>
#include<iostream>
using namespace std;
int n,m,rt=0,q=0,t;
char c[1000001][11];
struct splay
{
    int k,a[2],f,s,c;
}T[10000001];
void pushup(int x)
{
    T[x].s=T[T[x].a[0]].s+T[T[x].a[1]].s+1;
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
void add(int &x,int f,int c,int k)
{
    if(x==0)
    {
        x=++q;
        T[x].k=k;
        T[x].s=1;
        T[x].f=f;
        T[x].c=c;
        splay(x,0);
        return;
    }
    if(k<=T[x].k) add(T[x].a[0],x,c,k);
    else add(T[x].a[1],x,c,k);
}
int find_f(int x,int f,int k)
{
    if(x==0)
    {
        splay(f,0);
        return 0;
    }
    if(k<=T[x].k) return find_f(T[x].a[0],x,k);
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
    if(k>=T[x].k) return find_b(T[x].a[1],x,k);
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
int main()
{
    add(rt,0,0,0);
    add(rt,0,0,1e9);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        cin>>c[++t];
        add(rt,0,t,i);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int k;
        cin>>c[++t];
        scanf("%d",&k);
        int o=sum(rt,k+1),p=sum(rt,k+2);
        splay(o,0);
        splay(p,rt);
        T[p].a[0]=++q;
        T[q].k=k;
        T[q].s=1;
        T[q].f=p;
        T[q].c=t;
        pushup(p);
        pushup(rt);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int k;
        scanf("%d",&k);
        cout<<c[T[sum(rt,k+2)].c];
        printf("\n");
    }
    return 0;
}
