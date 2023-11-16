#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5000001;
int n,m,p=1,t[N],b[N];
ll s;
struct road
{
    int m,q;
}a[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
int tot,rt[N];
struct tree
{
    int l,r,s,w;
}T[N<<4];
void pushup(int x,int t)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
    T[x].w=T[T[x].l].w^T[T[x].r].w^(T[T[x].r].s&1?(1<<t):0);
}
void insert(int &x,int q,int t)
{
    if(x==0) x=++tot;
    if(t==30)
    {
        ++T[x].s;
        return;
    }
    if((q&(1<<t))==0) insert(T[x].l,q,t+1);
    else insert(T[x].r,q,t+1);
    pushup(x,t);
}
void add(int &x,int t)
{
    if(x==0) x=++tot;
    if(t==30) return;
    swap(T[x].l,T[x].r);
    add(T[x].l,t+1);
    pushup(x,t);
}
int merge(int x1,int x2,int t)
{
    if(x1==0||x2==0) return x1+x2;
    if(t==30)
    {
        T[x1].s=T[x1].s+T[x2].s;
        return x1;
    }
    T[x1].l=merge(T[x1].l,T[x2].l,t+1);
    T[x1].r=merge(T[x1].r,T[x2].r,t+1);
    pushup(x1,t);
    return x1;
}
void dfs(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        dfs(a[i].m);
        rt[x]=merge(rt[x],rt[a[i].m],0);
    }
    add(rt[x],0);
    insert(rt[x],b[x],0);
    s+=T[rt[x]].w;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        road(x,i);
    }
    dfs(1);
    printf("%lld",s);
    return 0;
}