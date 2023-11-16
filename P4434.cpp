#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001,P=1000000007;
int n,m,q,p=1,t[N],b[N],fa[N],ga[N];
bool h[N];
struct tree
{
    int f,s,d,t,z,b,bm;
}T[N];
struct tree2
{
    int l,r,s,k;
}T2[N<<2];
struct road
{
    int m,q;
}a[N<<1];
int find(int x)
{
    if(fa[x]==x) return x;
    int z=find(fa[x]);
    ga[x]^=ga[fa[x]];
    return fa[x]=z;
}
void pushup(int x)
{
    T2[x].s=max(T2[x<<1].s,T2[x<<1|1].s);
}
void pushdown(int x)
{
    if(T2[x].k==0) return;
    if((find(T2[x<<1].s)==find(T2[x].k)&&ga[T2[x<<1].s]!=ga[T2[x].k])||(find(T2[x<<1|1].s)==find(T2[x].k)&&ga[T2[x<<1|1].s]!=ga[T2[x].k]))
    {
        printf("0");
        exit(0);
    }
    if(find(T2[x<<1].s)!=find(T2[x].k))
    {
        int z=find(T2[x<<1].s);
        fa[z]=find(T2[x].k);
        ga[z]=ga[T2[x<<1].s]^ga[T2[x].k];
    }
    if(find(T2[x<<1|1].s)!=find(T2[x].k))
    {
        int z=find(T2[x<<1|1].s);
        fa[z]=find(T2[x].k);
        ga[z]=ga[T2[x<<1|1].s]^ga[T2[x].k];
    }
    T2[x<<1].s=T2[x<<1|1].s=T2[x].k;
    T2[x<<1].k=T2[x<<1|1].k=T2[x].k;
    T2[x].k=0;
}
void build(int x,int l,int r)
{
    T2[x].l=l;
    T2[x].r=r;
    T2[x].s=T2[x].k=0;
    if(l==r)
    {
        T2[x].s=b[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,int k)
{
    if(T2[x].l>=l&&T2[x].r<=r)
    {
        if(find(T2[x].s)==find(k)&&ga[T2[x].s]!=ga[k])
        {
            printf("0");
            exit(0);
        }
        if(find(T2[x].s)!=find(k))
        {
            int z=find(T2[x].s);
            fa[z]=find(k);
            ga[z]=ga[T2[x].s]^ga[k];
        }
        T2[x].s=k;
        T2[x].k=k;
        return;
    }
    pushdown(x);
    int z=T2[x].l+T2[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
int num(int x,int q)
{
    if(T2[x].l==T2[x].r)
    {
        return T2[x].s;
    }
    pushdown(x);
    int z=T2[x].l+T2[x].r>>1;
    if(q<=z) return num(x<<1,q);
    else return num(x<<1|1,q);
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        T[a[i].m].f=x;
        dfs1(a[i].m);
        T[x].s+=T[a[i].m].s;
        if(T[a[i].m].s>T[T[x].z].s) T[x].z=a[i].m;
    }
}
void dfs2(int x,int k)
{
    T[x].b=++q;
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs2(a[i].m,a[i].m);
    }
    T[x].bm=q;
}
void change(int x,int y)
{
    if(x==y) return;
    int k1=num(1,T[x].b),k2=num(1,T[y].b);
    bool u1=false,u2=false;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            add(1,T[T[x].t].b,T[x].b,k1);
            u1=true;
            x=T[T[x].t].f;
        }
        else
        {
            add(1,T[T[y].t].b,T[y].b,k2);
            u2=true;
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) add(1,T[x].b+1,T[y].b,k2),u2=true;
    else if(T[x].d>T[y].d) add(1,T[y].b+1,T[x].b,k1),u1=true;
    if(u1==true&&u2==true)
    {
        if(find(k1)==find(k2)&&ga[k1]==ga[k2])
        {
            printf("0");
            exit(0);
        }
        if(find(k1)!=find(k2))
        {
            int z=find(k1);
            ga[z]=ga[k1]^ga[k2]^1;
            fa[z]=find(k2);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=n;++i) b[T[i].b]=i;
    for(int i=1;i<=n;++i) fa[i]=i,ga[i]=0;
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        change(x,y);
    }
    int s=0;
    for(int i=1;i<=n;++i) num(1,i);
    for(int i=2;i<=n;++i)
    {
        int z=num(1,i);
        if(h[find(z)]==false&&find(z)==z)
        {
            ++s;
            h[find(z)]=true;
        }
    }
    ll w=1;
    for(int i=1;i<=s;++i) w=(w*2)%P;
    printf("%lld",w);
    return 0;
}