#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001,M=10000001;
int n,m,p=1,s1,s2,t[N],t0[N],f[N];
ll b[N][2],q;
struct road
{
    int m,q;
    ll r;
}a[M];
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
            int z=dfs(a[i].m,min(r,a[i].r));
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
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&b[i][0]);
    for(int i=1;i<=n;++i) scanf("%lld",&b[i][1]);
    scanf("%d",&m);
    s1=(n+m)*2+1,s2=(n+m)*2+2;
    for(int i=1;i<=n;++i)
    {
        q+=b[i][0]+b[i][1];
        road(i,n+i,1e18);
        road(n+i,i,0);
        road(s1,i,b[i][0]);
        road(i,s1,0);
        road(n+i,s2,b[i][1]);
        road(s2,n+i,0);
    }
    for(int i=1;i<=m;++i)
    {
        int k;
        ll r1,r2;
        scanf("%d%lld%lld",&k,&r1,&r2);
        q+=r1+r2;
        road(s1,n*2+i,r1);
        road(n*2+i,s1,0);
        road(n*2+m+i,s2,r2);
        road(s2,n*2+m+i,0);
        for(int j=1;j<=k;++j)
        {
            int x;
            scanf("%d",&x);
            road(n*2+i,x,1e18);
            road(x,n*2+i,0);
            road(n+x,n*2+m+i,1e18);
            road(n*2+m+i,n+x,0);
        }
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%lld",q-r);
    return 0;
}