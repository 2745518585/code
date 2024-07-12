#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,d[N];
ll b[N],f[N];
vector<int> a[N];
vector<pair<int,int>> e;
struct tree
{
    int f,s,d,t,z;
}T[N];
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(auto i:a[x])
    {
        if(i==T[x].f) continue;
        T[i].f=x;
        dfs1(i);
        T[x].s+=T[i].s;
        if(T[i].s>T[T[x].z].s) T[x].z=i;
    }
}
void dfs2(int x,int t)
{
    T[x].t=t;
    if(T[x].z) dfs2(T[x].z,t);
    for(auto i:a[x])
    {
        if(i==T[x].f||i==T[x].z) continue;
        dfs2(i,i);
    }
}
int LCA(int x,int y)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>T[T[y].t].d) x=T[T[x].t].f;
        else y=T[T[y].t].f;
    }
    if(T[x].d<T[y].d) return x;
    else return y;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
        e.push_back(make_pair(x,y));
    }
    for(int i=2;i<=n;++i)
    {
        scanf("%lld",&b[i]);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=2;i<=n;++i) d[i]=LCA(i-1,i);
    for(ll r=1;r<=60;++r)
    {
        for(int j=2;j<=n;++j)
        {
            f[j]=(b[j]-f[j-1]+f[d[j]]*2)&((1ll<<r)-1);
        }
    }
    for(int i=2;i<=n;++i)
    {
        if(f[i]-f[T[i].f]<=0||f[i-1]+f[i]-2*f[d[i]]!=b[i])
        {
            printf("-1");
            return 0;
        }
    }
    for(auto i:e)
    {
        printf("%lld\n",abs(f[i.first]-f[i.second]));
    }
    return 0;
}