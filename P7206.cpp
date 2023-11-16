#include<cstdio>
#include<algorithm>
#include<unordered_set>
using namespace std;
typedef long long ll;
const int N=100001,M=27,P=1e9+7;
int n,m,q,o,t[N],p=1,r,q1,q2,h2[N],c[N];
ll powb[N],h[N];
bool g[N],u;
char b[N];
unordered_set<ll> Set;
struct tree
{
    int s,ms,d;
    ll h1,h2;
}T[N];
struct road
{
    int m,q;
}a[N<<1];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
ll num(ll a,ll b)
{
    return a*P+b;
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs1(int x,int fa)
{
    T[x].s=1;
    T[x].ms=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        dfs1(a[i].m,x);
        T[x].s+=T[a[i].m].s;
        T[x].ms=max(T[x].ms,T[a[i].m].s);
    }
    T[x].ms=max(T[x].ms,q-T[x].s);
    if(T[x].ms<T[r].ms) r=x;
}
void dfs2(int x,int fa)
{
    h[++q2]=((T[x].h1*inv(powb[T[x].d])-T[x].h2*inv(powb[m-1]))%P+P)%P;
    h2[q2]=T[x].d;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        T[a[i].m].d=T[x].d+1;
        T[a[i].m].h1=(T[x].h1+(b[a[i].m]-'a'+1)*powb[T[x].d+1])%P;
        T[a[i].m].h2=(T[x].h2*27+(b[a[i].m]-'a'+1))%P;
        dfs2(a[i].m,x);
    }
}
void solve(int x)
{
    Set.clear();
    q1=q2=0;
    T[x].h1=b[x]-'a'+1;
    T[x].h2=0;
    T[x].d=0;
    Set.insert(num(((T[x].h1*inv(powb[T[x].d])-T[x].h2*inv(powb[m-1]))%P+P)%P,0));
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        T[a[i].m].d=T[x].d+1;
        T[a[i].m].h1=(T[x].h1+(b[a[i].m]-'a'+1)*powb[T[x].d+1])%P;
        T[a[i].m].h2=(T[x].h2*27+(b[a[i].m]-'a'+1))%P;
        dfs2(a[i].m,x);
        for(int j=q1+1;j<=q2;++j)
        {
            if(Set.count(num(h[j],m-h2[j]-1))!=0) u=true;
        }
        if(u) return;
        for(int j=q1+1;j<=q2;++j) Set.insert(num(h[j],h2[j]));
        q1=q2;
    }
}
void dfs0(int x)
{
    r=0;
    q=T[x].s;
    dfs1(x,0);
    c[++o]=r;
    g[r]=true;
    for(int i=t[r];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        dfs0(a[i].m);
    }
}
void dfs(int x)
{
    r=c[++o];
    solve(r);
    if(u) return;
    g[r]=true;
    for(int i=t[r];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        dfs(a[i].m);
        if(u) return;
    }
}
int main()
{
    scanf("%d%s",&n,b+1);
    powb[0]=1;
    for(int i=1;i<=n;++i) powb[i]=powb[i-1]*27%P;
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    T[0].ms=1e9;
    dfs0(1);
    int l=1,r=(n+1)/2;
    while(l<r)
    {
        int z=l+r+1>>1;
        m=z*2-1;
        for(int i=1;i<=n;++i) g[i]=false;
        u=false;
        o=0;
        dfs(1);
        if(u==true) l=z;
        else r=z-1;
    }
    int s=l*2-1;
    l=0,r=n/2;
    while(l<r)
    {
        int z=l+r+1>>1;
        m=z*2;
        for(int i=1;i<=n;++i) g[i]=false;
        u=false;
        o=0;
        dfs(1);
        if(u==true) l=z;
        else r=z-1;
    }
    printf("%d",max(s,l*2));
    return 0;
}