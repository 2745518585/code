#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,g[N];
ll f[N],T[N];
vector<int> a[N];
bool cmp(int x,int y)
{
    return g[x]<g[y];
}
void add(int x,ll k)
{
    while(x<=n) T[x]=(T[x]+k)%P,x+=x&-x;
}
ll sum(int x)
{
    ll s=0;
    while(x>=1) s=(s+T[x])%P,x-=x&-x;
    return s;
}
void dfs1(int x,int fa)
{
    g[x]=x;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs1(i,x);
        g[x]=max(g[x],g[i]);
    }
}
void dfs2(int x,int fa,int v)
{
    if(x==1) f[x]=1;
    else if(v<=x) f[x]=sum(x-1)-sum(v-1);
    else f[x]=0;
    sort(a[x].begin(),a[x].end(),cmp);
    add(x,f[x]);
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs2(i,x,max(v,x));
        add(g[i],f[g[i]]);
    }
    for(auto i:a[x])
    {
        if(i!=fa) add(g[i],-f[g[i]]);
    }
    add(x,-f[x]);
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) a[i].clear();
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        dfs1(1,0);
        for(int i=1;i<=n;++i) T[i]=0;
        dfs2(1,0,0);
        printf("%lld\n",(f[n]%P+P)%P);
    }
    return 0;
}