#include<iostream>
#include<cstdio>
#include<algorithm>
#include<ctime>
using namespace std;
int n,m,r[100001],q=0,a[100001],f[100001];
struct treap
{
    int k,l,r,s,h,t;
}T[10000001];
int fa(int x)
{
    if(f[x]==x) return x;
    return f[x]=fa(f[x]);
}
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
void add(int &x,int t,int k)
{
    if(x==0)
    {
        x=++q;
        T[x].l=T[x].r=0;
        T[x].s=1;
        T[x].t=t;
        T[x].k=k;
        T[x].h=rand()*rand()%1000000+1;
        return;
    }
    else if(k<T[x].k) add(T[x].l,t,k);
    else if(k>T[x].k) add(T[x].r,t,k);
    if(T[x].l!=0&&T[x].h>T[T[x].l].h) rotate_r(x);
    if(T[x].r!=0&&T[x].h>T[T[x].r].h) rotate_l(x);
    pushup(x);
}
int sum(int x,int k)
{
    if(x==0) return -1;
    if(k<T[T[x].l].s+1) return sum(T[x].l,k);
    if(k<=T[T[x].l].s+1) return x;
    return sum(T[x].r,k-T[T[x].l].s-1);
}
void dfs(int x,int &rt)
{
    if(x==0) return;
    add(rt,T[x].t,a[T[x].t]);
    dfs(T[x].l,rt);
    dfs(T[x].r,rt);
}
int main()
{   
    srand(time(NULL));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=n;++i) f[i]=i;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(fa(x)!=fa(y)) f[fa(x)]=fa(y);
    }
    for(int i=1;i<=n;++i)
    {
        add(r[fa(i)],i,a[i]);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        char z;
        cin>>z;
        int x,y;
        scanf("%d%d",&x,&y);
        if(z=='Q')
        {
            int p=sum(r[fa(x)],y);
            if(p==-1) printf("-1\n");
            else printf("%d\n",T[p].t);
        }
        else if(z=='B')
        {
            if(fa(x)==fa(y)) continue;
            dfs(r[fa(x)],r[fa(y)]);
            f[fa(x)]=fa(y);
        }
    }
    return 0;
}