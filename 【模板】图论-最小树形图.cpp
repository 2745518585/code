#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,r,fa[N],rt[N],S[N],T;
bool h[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
namespace lt
{
    int tot;
    struct tree
    {
        int x,l,r,d,k;
        pair<int,int> p;
    }T[N];
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        if(T[x].l) T[T[x].l].x+=T[x].k,T[T[x].l].k+=T[x].k;
        if(T[x].r) T[T[x].r].x+=T[x].k,T[T[x].r].k+=T[x].k;
        T[x].k=0;
    }
    int merge(int x,int y)
    {
        if(x==0||y==0) return x+y;
        pushdown(x),pushdown(y);
        if(T[x].x>T[y].x) swap(x,y);
        T[x].r=merge(T[x].r,y);
        if(T[T[x].l].d<T[T[x].r].d) swap(T[x].l,T[x].r);
        T[x].d=T[T[x].r].d+1;
        return x;
    }
    void add(int &rt,int x,int p1,int p2)
    {
        ++tot;
        T[tot].x=x;
        T[tot].p=make_pair(p1,p2);
        rt=merge(rt,tot);
    }
    void pop(int &rt)
    {
        pushdown(rt);
        rt=merge(T[rt].l,T[rt].r);
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&r);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        lt::add(rt[y],w,x,y);
    }
    for(int i=1;i<=n;++i)
    {
        lt::add(rt[i%n+1],1e9,i,i%n+1);
    }
    for(int i=1;i<=n*2;++i) fa[i]=i;
    S[++T]=r;
    h[r]=true;
    ll s=0;
    while(rt[S[T]]!=0)
    {
        int x=find(lt::T[rt[S[T]]].p.first);
        if(x==S[T])
        {
            lt::pop(rt[S[T]]);
            continue;
        }
        if(h[x]==false)
        {
            S[++T]=x;
            h[x]=true;
            continue;
        }
        ++n;
        while(h[x])
        {
            int y=S[T];
            --T;
            h[y]=false,fa[y]=n;
            if(find(lt::T[rt[y]].p.second)!=find(r)) s+=lt::T[rt[y]].x;
            lt::T[rt[y]].k-=lt::T[rt[y]].x;
            lt::pop(rt[y]);
            rt[n]=lt::merge(rt[n],rt[y]);
        }
        S[++T]=n;
        h[n]=true;
    }
    if(s>=1e9) printf("-1");
    else printf("%lld",s);
    return 0;
}