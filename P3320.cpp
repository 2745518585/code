#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,tot,p=1,rt,t[N],b[N],c[N];
ll s;
struct tree
{
    int f,s,d,t,z,b;
    ll h;
}T[N];
struct road
{
    int m,q,w;
}a[N<<1];
struct Treap
{
    struct tree
    {
        int x,l,r,s,h,t; 
    }T[N];
    void pushup(int x)
    {
        T[x].s=T[T[x].l].s+T[T[x].r].s+T[x].t;
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
        else if(k<T[x].x) add(T[x].l,k);
        else if(k>T[x].x) add(T[x].r,k);
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
        if(k<T[x].x) remove(T[x].l,k);
        else remove(T[x].r,k);
        pushup(x);
    }
    int find_f(int x,int k)
    {
        if(x==0) return -1;
        if(k<=T[x].x) return find_f(T[x].l,k);
        int p=find_f(T[x].r,k);
        if(p==-1) return T[x].x;
        return p;
    }
    int find_b(int x,int k)
    {
        if(x==0) return -1;
        if(k>=T[x].x) return find_b(T[x].r,k);
        int p=find_b(T[x].l,k);
        if(p==-1) return T[x].x;
        return p;
    }
}Treap;
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        T[a[i].m].f=x;
        T[a[i].m].h=T[x].h+a[i].w;
        dfs1(a[i].m);
        T[x].s+=T[a[i].m].s;
        if(T[a[i].m].s>T[T[x].z].s) T[x].z=a[i].m;
    }
}
void dfs2(int x,int k)
{
    T[x].b=++tot;
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        else dfs2(a[i].m,a[i].m);
    }
}
int LCA(int x,int y)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d) x=T[T[x].t].f;
        else y=T[T[y].t].f;
    }
    if(T[x].d<T[y].d) return x;
    else return y;
}
ll sum(int x,int y)
{
    return T[x].h+T[y].h-2*T[LCA(x,y)].h;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=n;++i) b[T[i].b]=i;
    for(int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        if(c[x]==0)
        {
            c[x]=1;
            int z1=Treap.find_f(rt,T[x].b),z2=Treap.find_b(rt,T[x].b);
            if(z1==-1) z1=Treap.find_f(rt,1e9);
            if(z2==-1) z2=Treap.find_b(rt,-1e9);
            if(z1!=-1) s+=sum(x,b[z1]);
            if(z2!=-1) s+=sum(x,b[z2]);
            if(z1!=-1&&z2!=-1) s-=sum(b[z1],b[z2]);
            Treap.add(rt,T[x].b);
        }
        else
        {
            c[x]=0;
            Treap.remove(rt,T[x].b);
            int z1=Treap.find_f(rt,T[x].b),z2=Treap.find_b(rt,T[x].b);
            if(z1==-1) z1=Treap.find_f(rt,1e9);
            if(z2==-1) z2=Treap.find_b(rt,-1e9);
            if(z1!=-1) s-=sum(x,b[z1]);
            if(z2!=-1) s-=sum(x,b[z2]);
            if(z1!=-1&&z2!=-1) s+=sum(b[z1],b[z2]);
        }
        printf("%lld\n",s);
    }
    return 0;
}