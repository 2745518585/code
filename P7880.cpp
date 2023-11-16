#include<bits/stdc++.h>
using namespace std;
using it=set<int>::iterator;
typedef long long ll;
const int N=1000001;
int n,m,q,p=1,t[N],d[N],f[N];
ll e[N];
set<int> Set;
struct str
{
    int x,t;
    str(){}
    str(int x,int t):x(x),t(t){}
};
vector<str> b[N],c[N];
struct road
{
    int m,q,w;
}a[N<<1];
struct tree
{
    int f,s,z;
    ll h;
}T[N];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
namespace Tree
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]+=k,x+=(x&-x);
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s+=T[x],x-=(x&-x);
        return s;
    }
}
void dfs0(int x)
{
    T[x].s=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        T[a[i].m].f=x;
        T[a[i].m].h=T[x].h+a[i].w;
        dfs0(a[i].m);
        T[x].s+=T[a[i].m].s;
        if(T[a[i].m].s>T[T[x].z].s) T[x].z=a[i].m;
    }
}
void dfs3(int x,int w)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        dfs3(a[i].m,w);
    }
    it p=Set.lower_bound(x);
    if(p!=Set.end()) b[*p].push_back(str(x,w));
    if(p!=Set.begin()) b[x].push_back(str(*prev(p),w));
}
void dfs2(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        dfs2(a[i].m);
    }
    Set.insert(x);
}
void dfs(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs(a[i].m);
        Set.clear();
    }
    if(T[x].z!=0) dfs(T[x].z);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs3(a[i].m,x);
        dfs2(a[i].m);
    }
    it p=Set.lower_bound(x);
    if(p!=Set.end()) b[*p].push_back(str(x,x));
    if(p!=Set.begin()) b[x].push_back(str(*prev(p),x));
    b[x].push_back(str(x,x));
    Set.insert(x);
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
    dfs0(1);
    dfs(1);
    for(int i=1;i<=n;++i) e[i]=T[i].h;
    sort(e+1,e+n+1);
    q=unique(e+1,e+n+1)-e-1;
    for(int i=1;i<=n;++i)
    {
        T[i].h=lower_bound(e+1,e+q+1,T[i].h)-e;
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        c[y].push_back(str(x,i));
    }
    for(int i=1;i<=n;++i)
    {
        for(auto j:b[i])
        {
            if(f[T[j.t].h]!=0) Tree::add(f[T[j.t].h],-1);
            f[T[j.t].h]=max(f[T[j.t].h],j.x);
            if(f[T[j.t].h]!=0) Tree::add(f[T[j.t].h],1);
        }
        for(auto j:c[i])
        {
            d[j.t]=Tree::sum(n)-Tree::sum(j.x-1);
        }
    }
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",d[i]);
    }
    return 0;
}