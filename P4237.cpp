#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10001,M=100001;
int n,m,k,q,p=1,s1,s2,t[N],p2=1,t2[N],t0[N];
ll v,f[N],b1[N],b2[N],q1,q2;
bool h[N];
struct road
{
    int m,q;
    ll r,w;
}a[M];
struct road2
{
    int m,q;
}a2[M];
void road(int x,int y,ll r,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[p].w=w;
}
void road2(int x,int y)
{
    a2[++p2].m=y;
    a2[p2].q=t2[x];
    t2[x]=p2;
}
bool SPFA()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=s2;++i)
    {
        f[i]=1e18;
        h[i]=false;
    }
    f[s1]=0;
    h[s1]=true;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(a[i].r>0&&f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    return f[s2]!=1e18;
}
ll dfs(int x,ll r)
{
    if(x==s2) return r;
    ll s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(h[a[i].m]==false&&a[i].r>0&&f[a[i].m]==f[x]+a[i].w)
        {
            h[a[i].m]=true;
            ll z=dfs(a[i].m,min(r,a[i].r));
            h[a[i].m]=false;
            if(z!=0)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
                v+=z*a[i].w;
            }
            else f[a[i].m]=0;
            if(r==0) return s; 
        }
    }
    return s;
}
void dfs0(int x)
{
    q1+=b1[x];
    q2+=b2[x];
    h[x]=true;
    for(int i=t2[x];i!=0;i=a2[i].q)
    {
        if(h[a2[i].m]) continue;
        dfs0(a2[i].m);
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&k,&q);
    s1=n*2+1,s2=n*2+2;
    for(int i=1;i<=n;++i)
    {
        ll w;
        scanf("%lld",&w);
        road(i,n+i,1e18,w);
        road(n+i,i,0,-w);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        road(n+x,y,1e18,w);
        road(y,n+x,0,-w);
        road(n+y,x,1e18,w);
        road(x,n+y,0,-w);
        road2(x,y);
        road2(y,x);
    }
    for(int i=1;i<=k;++i)
    {
        int x;
        ll w;
        scanf("%lld%d",&w,&x);
        road(s1,x,1,w);
        road(x,s1,0,-w);
        ++b1[x];
    }
    for(int i=1;i<=q;++i)
    {
        int x;
        ll w;
        scanf("%lld%d",&w,&x);
        road(n+x,s2,1,-w);
        road(s2,n+x,0,w);
        ++b2[x];
    }
    ll z=0;
    for(int i=1;i<=n;++i)
    {
        if(h[i]==false)
        {
            q1=q2=0;
            dfs0(i);
            z+=min(q1,q2);
        }
    }
    if(z<q)
    {
        printf("No\n%lld",z);
        return 0;
    }
    ll r=0;
    while(SPFA())
    {
        for(int i=1;i<=s2;++i) 
        {
            t0[i]=t[i];
            h[i]=false;
        }
        r+=dfs(s1,1e18);
    }
    printf("Yes\n%lld",-v);
    return 0;
}