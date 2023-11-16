#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
const int N=500001,M=21;
int n,m,q,c[N][2],e[N],f1[N],f2[N],fa[N][M],g[N],h[N];
vector<int> d[N];
struct node
{
    int x,y,t;
    node(){}
    node(int x,int y,int t):x(x),y(y),t(t){}
}b[N][2];
vector<node> a;
struct tree
{
    int f,d,h;
}T[N];
map<pair<int,int>,int> Map;
int solve(vector<node> a,int x,int y,int t)
{
    if(a.size()==0) return 0;
    if(a.size()==1) return a[0].t;
    if(t==0)
    {
        if(!Map.count(make_pair(x,y)))
        {
            Map[make_pair(x,y)]=++m;
            T[m].h=x+y;
        }
        int z=Map[make_pair(x,y)];
        for(auto i:a)
        {
            if(z!=i.t) T[i.t].f=z;
        }
        return z;
    }
    vector<node> p;
    for(auto i:a)
    {
        if(i.x>=x+(1<<(t-1))) p.push_back(i);
    }
    int z1=solve(p,x+(1<<(t-1)),y,t-1);
    vector<node>().swap(p);
    for(auto i:a)
    {
        if(i.y>=y+(1<<(t-1))) p.push_back(i);
    }
    int z2=solve(p,x,y+(1<<(t-1)),t-1);
    vector<node>().swap(p);
    for(auto i:a)
    {
        if(i.x<x+(1<<(t-1))&&i.y<y+(1<<(t-1))) p.push_back(i);
    }
    if(z1) p.push_back(node(x+(1<<(t-1))-1,y,z1));
    if(z2) p.push_back(node(x,y+(1<<(t-1))-1,z2));
    int z=solve(p,x,y,t-1);
    vector<node>().swap(p);
    return z;
}
void dfs(int x)
{
    T[x].d=T[T[x].f].d+1;
    for(auto i:d[x])
    {
        if(i==T[x].f) continue;
        T[i].d=T[x].d+1;
        dfs(i);
    }
}
int LCA(int x,int y)
{
    if(T[x].d<T[y].d) swap(x,y);
    int t=0;
    while(t>=0)
    {
        if(T[fa[x][t]].d>=T[y].d) x=fa[x][t],++t;
        else --t;
    }
    if(x==y) return x;
    t=0;
    while(t>=0)
    {
        if(fa[x][t]!=fa[y][t]) x=fa[x][t],y=fa[y][t],++t;
        else --t;
    }
    return T[x].f;
}
int LCA2(int x,int y)
{
    if(T[x].d<T[y].d) swap(x,y);
    while(T[x].d>T[y].d) x=T[x].f;
    while(x!=y) x=T[x].f,y=T[y].f;
    return x;
}
void dfs2(int x)
{
    for(auto i:d[x])
    {
        if(i==T[x].f) continue;
        dfs2(i);
        g[x]+=g[i];
        h[x]+=h[i];
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d%d",&b[i][0].x,&b[i][0].y,&b[i][1].x,&b[i][1].y);
        ++m;
        a.push_back(node(b[i][0].x,b[i][0].y,m));
        Map[make_pair(b[i][0].x,b[i][0].y)]=m;
        T[m].h=b[i][0].x+b[i][0].y;
        ++m;
        a.push_back(node(b[i][1].x,b[i][1].y,m));
        Map[make_pair(b[i][1].x,b[i][1].y)]=m;
        T[m].h=b[i][1].x+b[i][1].y;
    }
    ++m;
    a.push_back(node(0,0,m));
    Map[make_pair(0,0)]=m;
    int rt=solve(a,0,0,30);
    for(int i=1;i<=m;++i)
    {
        if(T[i].f!=0) d[T[i].f].push_back(i);
    }
    dfs(rt);
    for(int i=1;i<=m;++i) e[i]=T[i].h;
    sort(e+1,e+m+1);
    q=unique(e+1,e+m+1)-e-1;
    for(int i=1;i<=m;++i)
    {
        T[i].h=lower_bound(e+1,e+q+1,T[i].h)-e;
    }
    for(int i=1;i<=m;++i) fa[i][0]=T[i].f;
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=m;++j)
        {
            fa[j][i]=fa[fa[j][i-1]][i-1];
        }
    }
    for(int i=1;i<=n;++i)
    {
        int x=Map[make_pair(b[i][0].x,b[i][0].y)],y=Map[make_pair(b[i][1].x,b[i][1].y)];
        int z=LCA(x,y);
        if(z!=x&&z!=y)
        {
            ++g[x],++g[y],g[z]-=2;
            ++h[x],++h[y],--h[z],--h[T[z].f];
        }
        else
        {
            if(T[x].d>T[y].d) swap(x,y);
            ++g[y],--g[x];
            ++h[y],--h[T[x].f];
        }
    }
    dfs2(rt);
    for(int i=1;i<=m;++i)
    {
        if(g[i])
        {
            ++f1[T[T[i].f].h+1];
            --f1[T[i].h];
            ++f2[T[T[i].f].h+1];
            --f2[T[i].h+1];
        }
    }
    for(int i=1;i<=q;++i) f1[i]+=f1[i-1],f2[i]+=f2[i-1];
    for(int i=1;i<=m;++i)
    {
        if(h[i]) ++f1[T[i].h];
    }
    int s=0;
    for(int i=q;i>=1;--i)
    {
        if(f1[i]%2!=s%2) ++s;
        if(e[i]-e[i-1]>1&&f2[i]%2!=s%2) ++s;
    }
    printf("%d",s);
    return 0;
}