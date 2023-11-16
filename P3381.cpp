#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,s1,s2,p=1,t[N],t0[N];
ll f[N],v;
bool h[N];
struct road
{
    int m,q;
    ll r,w;
}a[N<<1];
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
    for(int i=1;i<=n;++i) f[i]=1e18,h[i]=false;
    f[s1]=0;
    h[s1]=true;
    Q.push(s1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[k]+a[i].w<f[a[i].m]&&a[i].r>0)
            {
                f[a[i].m]=f[k]+a[i].w;
                h[a[i].m]=true;
                Q.push(a[i].m);
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
        if(f[x]+a[i].w==f[a[i].m]&&!h[a[i].m]&&a[i].r>0)
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
            if(r==0) return s;
        }
    }
    return s;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s1,&s2);
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
        for(int i=1;i<=n;++i) t0[i]=t[i],h[i]=false;
        r+=dfs(s1,1e18);
    }
    printf("%lld %lld",r,v);
    return 0;
}