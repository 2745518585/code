#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,p=1,t[N],b[N],d[N],f[N];
struct road
{
    int m,q;
}a[N<<1];
struct tree
{
    int f,s,z;
}T[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
struct str
{
    int x,t;
    str(){}
    str(int x,int t):x(x),t(t){}
};
vector<str> c[N];
namespace Tree
{
    int T[N];
    void add(int x,int k)
    {
        ++x;
        while(x<=n+1) T[x]+=k,x+=x&-x;
    }
    int sum(int x)
    {
        ++x;
        int s=0;
        while(x>=1) s+=T[x],x-=x&-x;
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
        dfs0(a[i].m);
        T[x].s+=T[a[i].m].s;
        if(T[a[i].m].s>T[T[x].z].s) T[x].z=a[i].m;
    }
}
void dfs1(int x)
{
    Tree::add(f[b[x]],-1);
    ++f[b[x]];
    Tree::add(f[b[x]],1);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        dfs1(a[i].m);
    }
}
void dfs2(int x)
{
    Tree::add(f[b[x]],-1);
    --f[b[x]];
    Tree::add(f[b[x]],1);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        dfs2(a[i].m);
    }
}
void dfs(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs(a[i].m);
        dfs2(a[i].m);
    }
    if(T[x].z!=0) dfs(T[x].z);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f||a[i].m==T[x].z) continue;
        dfs1(a[i].m);
    }
    Tree::add(f[b[x]],-1);
    ++f[b[x]];
    Tree::add(f[b[x]],1);
    for(auto i:c[x]) d[i.t]=Tree::sum(n)-Tree::sum(i.x-1);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=m;++i)
    {
        int x,k;
        scanf("%d%d",&x,&k);
        c[x].push_back(str(k,i));
    }
    dfs0(1);
    dfs(1);
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",d[i]);
    }
    return 0;
}