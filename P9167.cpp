#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,k,q,t,rt;
ll f[N];
bool h[N];
struct tree
{
    int s,ms;
}T[N];
vector<int> a[N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    return (x%P+P)%P;
}
namespace rstree
{
    int tot;
    vector<int> a[N];
    stack<int> S;
    struct tree
    {
        int b,c;
    }T[N<<2];
    void dfs(int x)
    {
        T[x].b=T[x].c=++tot;
        S.push(x);
        for(auto i:a[x])
        {
            if(T[i].b==0)
            {
                dfs(i);
                T[x].c=min(T[x].c,T[i].c);
                if(T[i].c==T[x].b)
                {
                    ++q;
                    while(true)
                    {
                        ::a[q].push_back(S.top());
                        ::a[S.top()].push_back(q);
                        if(S.top()==i)
                        {
                            S.pop();
                            break;
                        }
                        S.pop();
                    }
                    ::a[q].push_back(x);
                    ::a[x].push_back(q);
                }
            }
            T[x].c=min(T[x].c,T[i].b);
        }
    }
}
void dfs0(int x,int fa)
{
    if(x<=n) T[x].s=1;
    else T[x].s=0;
    T[x].ms=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs0(i,x);
        T[x].s+=T[i].s;
        T[x].ms=max(T[x].ms,T[i].s);
    }
    T[x].ms=max(T[x].ms,n-T[x].s);
    if(x<=n&&T[x].ms<T[rt].ms) rt=x;
}
void dfs00(int x,int fa)
{
    if(x<=n) T[x].s=1;
    else T[x].s=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs00(i,x);
        T[x].s+=T[i].s;
    }
}
void dfs1(int x,int fa)
{
    if(x>n)
    {
        ll v=1;
        f[x]=0;
        for(auto i:a[x])
        {
            if(i==fa) continue;
            if(T[i].s<t) v=0;
            else dfs1(i,x),v=v*f[i]%P;
        }
        f[x]=(f[x]+v)%P;
        return;
    }
    int u=0;
    if(x<=n) u=1;
    ll v=1;
    f[x]=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        if(T[i].s<t) u+=T[i].s;
        else dfs1(i,x),v=v*f[i]%P;
    }
    if(u==t) f[x]=v;
}
void dfs2(int x,int fa)
{
    if(x>n)
    {
        ll v=1;
        f[x]=0;
        for(auto i:a[x])
        {
            if(i==fa) continue;
            if(T[i].s<t) v=0;
            else dfs2(i,x),v=v*f[i]%P;
        }
        f[x]=(f[x]+v)%P;
        return;
    }
    int u=0;
    if(x<=n) u=1;
    ll v=1;
    f[x]=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        if(T[i].s<t) u+=T[i].s;
        else if(T[i].s>=t+1) dfs2(i,x),v=v*f[i]%P;
        else dfs2(i,x);
    }
    if(u==0||u==1)
    {
        int p=0;
        for(auto i:a[x])
        {
            if(i==fa||T[i].s!=t) continue;
            if(f[i]==0) ++p;
        }
        if(p==0)
        {
            ll w=v;
            for(auto i:a[x])
            {
                if(i==fa||T[i].s!=t) continue;
                w=w*f[i]%P;
            }
            for(auto i:a[x])
            {
                if(i==fa||T[i].s!=t) continue;
                f[x]=(f[x]+w*inv(f[i])%P)%P;
            }
        }
        else if(p==1)
        {
            ll w=v;
            for(auto i:a[x])
            {
                if(i==fa||T[i].s!=t) continue;
                if(f[i]!=0) w=w*f[i]%P;
            }
            f[x]=(f[x]+w)%P;
        }
    }
    for(auto i:a[x])
    {
        if(i==fa) continue;
        if(T[i].s==t) v=v*f[i]%P;
    }
    if(u==t||u==t+1) f[x]=(f[x]+v)%P;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    q=n;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        rstree::a[x].push_back(y);
        rstree::a[y].push_back(x);
    }
    rstree::dfs(1);
    T[0].ms=1e9;
    dfs0(1,0);
    dfs00(rt,0);
    ll s=0;
    if(k==0)
    {
        for(t=1;t<=n-1;++t)
        {
            if(n%t!=0) continue;
            dfs1(rt,0);
            s=(s+f[rt])%P;
        }
    }
    else
    {
        for(int i=1;i<=n;++i) h[n/i]=h[n/i-1]=true;
        for(t=1;t<=n-1;++t)
        {
            if(!h[t]) continue;
            dfs2(rt,0);
            s=(s+f[rt])%P;
        }
        for(t=2;t<=n;++t)
        {
            if(n%t!=0) continue;
            dfs1(rt,0);
            s=(s-f[rt])%P;
        }
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}