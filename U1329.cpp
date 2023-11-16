#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001,M=1000001;
int n,m,t1,t2,p=1,s1,s2,t[N],t0[N],f[N];
ll q;
struct road
{
    int m,q;
    ll r;
}a[M];
struct road2
{
    int x,y;
    ll w;
}a2[M];
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
            else f[a[i].m]=0;
            if(r==0) return s;
        }
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    s1=n*2+1,s2=n*2+2;
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%lld",&a2[i].x,&a2[i].y,&a2[i].w);
    }
    scanf("%d%d%lld",&t1,&t2,&q);
    for(int i=1;i<=m;++i)
    {
        if(a2[i].w<q)
        {
            road(a2[i].x,a2[i].y,1);
            road(a2[i].y,a2[i].x,1);
        }
        else if(a2[i].w>q)
        {
            road(n+a2[i].x,n+a2[i].y,1);
            road(n+a2[i].y,n+a2[i].x,1);
        }
    }
    road(s1,t1,1e18);
    road(t1,s1,0);
    road(s1,n+t1,1e18);
    road(n+t1,s1,0);
    road(t2,s2,1e18);
    road(s2,t2,0);
    road(n+t2,s2,1e18);
    road(s2,n+t2,0);
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%lld",r);
    return 0;
}