#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,fa[N],ga[N],d[N];
bool h[N],g[N];
vector<pair<int,int>> b[N];
struct str
{
    int x,y,t;
}a[N];
void add(int x)
{
    printf("+ %d\n",x);
    fflush(stdout);
}
void remove(int x)
{
    printf("- %d\n",x);
    fflush(stdout);
}
int query(int x)
{
    printf("? %d\n",x);
    fflush(stdout);
    int z;
    scanf("%d",&z);
    return z;
}
bool check(int x,int y)
{
    for(int i=1;i<=20;++i)
    {
        if(!query(x)||!query(y)) return false;
    }
    return true;
}
void dfs(int x)
{
    d[x]=d[fa[x]]+1;
    for(auto i:b[x])
    {
        if(i.first==fa[x]) continue;
        fa[i.first]=x;
        ga[i.first]=i.second;
        dfs(i.first);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) b[i].clear(),fa[i]=ga[i]=d[i]=0;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&a[i].x,&a[i].y);
            g[i]=h[i]=false;
        }
        for(int i=1;i<=m;++i)
        {
            remove(i);
            if(!check(a[i].x,a[i].y))
            {
                add(i);
                g[i]=h[i]=true;
                b[a[i].x].push_back(make_pair(a[i].y,i));
                b[a[i].y].push_back(make_pair(a[i].x,i));
            }
        }
        fa[1]=0;
        dfs(1);
        for(int i=1;i<=m;++i)
        {
            if(g[i]) continue;
            int z=ga[d[a[i].x]>=d[a[i].y]?a[i].x:a[i].y];
            remove(z);
            add(i);
            if(check(a[i].x,a[i].y)) h[i]=true;
            remove(i);
            add(z);
        }
        printf("! ");
        for(int i=1;i<=m;++i) printf("%d ",h[i]);
        printf("\n");
        fflush(stdout);
        int x;
        scanf("%d",&x);
        if(x==0) return 0;
    }
    return 0;
}