#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,k,p=1,s1,s2,t[N],t0[N],f[N];
struct road
{
    int m,q;
    ll r;
}a[N];
struct str
{
    int x,y;
    ll w;
}b[N];
void road(int x,int y,ll r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
}
bool bfs()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=s2;++i) f[i]=0;
    f[s1]=1;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[a[i].m]==0&&a[i].r!=0)
            {
                f[a[i].m]=f[k]+1;
                Q.push(a[i].m);
            }
        }
    }
    return f[s2]!=0;
}
ll dfs(int x,ll r)
{
    if(x==s2) return r;
    ll s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(f[a[i].m]==f[x]+1&&a[i].r!=0)
        {
            ll z=dfs(a[i].m,min(r,a[i].r));
            if(z!=0)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
            }
            if(r==0) return s;
        }
    }
    return s;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    s1=n+1,s2=n+2;
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%lld",&b[i].x,&b[i].y,&b[i].w);
    }
    road(s1,b[k].x,1e18);
    road(b[k].x,s1,0);
    road(b[k].y,s2,1e18);
    road(s2,b[k].y,0);
    for(int i=1;i<=m;++i)
    {
        if(i!=k&&b[i].w<=b[k].w)
        {
            road(b[i].x,b[i].y,b[k].w-b[i].w+1);
            road(b[i].y,b[i].x,b[k].w-b[i].w+1);
        }
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%lld",r);
    return 0;
}