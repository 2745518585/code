#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001,M=31;
int n,m,q,tot,b[N],c[N],d1[N],d2[N];
vector<pair<int,ll>> a[N];
struct tree
{
    int f,s,d,t,z,b;
    ll h;
}T[N];
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(auto i:a[x])
    {
        if(i.first==T[x].f) continue;
        T[i.first].f=x;
        T[i.first].h=T[x].h+i.second;
        dfs1(i.first);
        T[x].s+=T[i.first].s;
        if(T[i.first].s>T[T[x].z].s) T[x].z=i.first;
    }
}
void dfs2(int x,int t)
{
    T[x].t=t;
    T[x].b=++tot;
    if(T[x].z) dfs2(T[x].z,t);
    for(auto i:a[x])
    {
        if(i.first==T[x].f||i.first==T[x].z) continue;
        dfs2(i.first,i.first);
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
namespace ST
{
    int a[N][M],lg[N];
    int check(int x,int y)
    {
        return T[x].d<T[y].d?x:y;
    }
    void init()
    {
        for(int i=0;i<=20;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,n);++j) lg[j]=i;
        }
        for(int i=2;i<=n;++i) a[i][0]=LCA(b[i-1],b[i]);
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j+(1<<i)-1<=n) a[j][i]=check(a[j][i-1],a[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int sum(int x,int y)
    {
        x=T[x].b,y=T[y].b;
        if(x>y) swap(x,y);
        ++x;
        return check(a[x][lg[y-x+1]],a[y-(1<<lg[y-x+1])+1][lg[y-x+1]]);
    }
}
ll dis(int x,int y)
{
    if(x==y) return 0;
    return T[x].h+T[y].h-T[ST::sum(x,y)].h*2;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        if(x<=n) c[x]=i;
    }
    q=-1;
    while(c[q+1]) ++q;
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=n;++i) b[T[i].b]=i;
    ST::init();
    d1[0]=d2[0]=c[0];
    for(int i=1;i<=q;++i)
    {
        d1[i]=d1[i-1],d2[i]=d2[i-1];
        ll z1=dis(d2[i],c[i]),z2=dis(d1[i],c[i]),z=dis(d1[i],d2[i]);
        if(z1>=z&&z1>=z2) d1[i]=c[i];
        else if(z2>=z&&z2>z1) d2[i]=c[i];
    }
    for(int i=1;i<=m;++i)
    {
        int x;
        ll k;
        scanf("%d%lld",&x,&k);
        int l=0,r=q+1;
        while(l<r)
        {
            int z=l+r>>1;
            if(dis(x,d1[z])<=k&&dis(x,d2[z])<=k) l=z+1;
            else r=z;
        }
        printf("%d\n",l);
    }
    return 0;
}