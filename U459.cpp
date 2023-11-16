#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10001,M=100001;
int n,m,p=1,s1,s2,t[N],t0[N];
ll v,f[N];
bool h[N];
struct road
{
    int m,q;
    ll r,w;
}a[M];
void road(int x,int y,ll r,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[p].w=w;
}
bool SPFA()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=n;++i)
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
int main()
{
    scanf("%d%d",&n,&m);
    s1=1,s2=n;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll r,w;
        scanf("%d%d%lld%lld",&x,&y,&r,&w);
        road(x,y,r,w);
        road(y,x,0,-w);
    }
    ll r=0;
    while(SPFA())
    {
        for(int i=1;i<=n;++i) 
        {
            t0[i]=t[i];
            h[i]=false;
        }
        r+=dfs(s1,1e18);
    }
    printf("%lld %lld",r,v);
    return 0;
}