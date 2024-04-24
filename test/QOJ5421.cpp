#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,k,tot,rt[N];
vector<pair<int,int>> a[N];
vector<int> c[N];
struct tree
{
    int l,r,s,h;
    ll x,k1,k2;
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+1;
}
void maketag(int x,ll k1,ll k2)
{
    T[x].x+=k1*(T[T[x].l].s+1)+k2;
    T[x].k1+=k1;
    T[x].k2+=k2;
}
void pushdown(int x)
{
    maketag(T[x].l,T[x].k1,T[x].k2);
    maketag(T[x].r,T[x].k1,T[x].k2+(T[T[x].l].s+1)*T[x].k1);
    T[x].k1=T[x].k2=0;
}
void split(int x,ll k,int &x1,int &x2)
{
    if(x==0)
    {
        x1=x2=0;
        return;
    }
    pushdown(x);
    if(T[x].x<=k)
    {
        x1=x;
        split(T[x].r,k,T[x].r,x2);
    }
    else
    {
        x2=x;
        split(T[x].l,k,x1,T[x].l);
    }
    pushup(x);
}
int merge(int x1,int x2)
{
    if(x1==0||x2==0) return x1|x2;
    pushdown(x1);
    pushdown(x2);
    if(T[x1].h<T[x2].h)
    {
        T[x1].r=merge(T[x1].r,x2);
        pushup(x1);
        return x1;
    }
    else
    {
        T[x2].l=merge(x1,T[x2].l);
        pushup(x2);
        return x2;
    }
}
void add(int &rt,ll k)
{
    int x1,x2;
    split(rt,k,x1,x2);
    T[++tot].x=k;
    T[tot].l=T[tot].r=0;
    T[tot].s=1;
    T[tot].h=rand();
    rt=merge(merge(x1,tot),x2);
}
void get(int x,auto p)
{
    if(x==0) return;
    pushdown(x);
    get(T[x].l,p);
    p(T[x].x);
    get(T[x].r,p);
}
void dfs(int x,int fa)
{
    add(rt[x],0);
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        dfs(i.first,x);
        maketag(rt[i.first],2*i.second,-(k+1)*i.second);
        if(T[rt[i.first]].s>T[rt[x]].s) swap(rt[x],rt[i.first]);
        get(rt[i.first],[&](ll k){add(rt[x],k);});
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    dfs(1,0);
    ll s=0;
    int t=k;
    get(rt[1],[&](ll k){if(t>0) s-=k,--t;});
    printf("%lld",s);
    return 0;
}