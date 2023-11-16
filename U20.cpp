#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10001,M=1000001;
int n,m,p=1,s1,s2,t[N],t0[N],f[N];
ll b[N],c[N][N];
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
    for(int i=1;i<=n;++i)
    {
        ll x;
        scanf("%lld%lld",&b[i],&x);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%lld",&c[i][j]);
        }
    }
    s1=n+1,s2=n+2;
    for(int k=1;k<=n;++k)
    {
        p=1;
        for(int i=1;i<=s2;++i) t[i]=0;
        ll w=0;
        for(int i=1;i<=n;++i)
        {
            if(i==k) continue;
            ll r=0;
            for(int j=1;j<=n;++j)
            {
                if(j==i||j==k) continue;
                road(i,j,c[i][j]);
                road(j,i,0);
                r+=c[i][j];
            }
            w+=r+b[i]*2;
            road(s1,i,r+b[i]*2);
            road(i,s1,0);
        }
        ll d=b[k];
        for(int i=1;i<=n;++i)
        {
            if(i==k) continue;
            d+=c[k][i];
        }
        ll r=0;
        for(int i=1;i<=n;++i)
        {
            if(i==k) continue;
            road(i,s2,d*2);
            road(s2,i,0);
        }
        while(bfs())
        {
            for(int i=1;i<=s2;++i) t0[i]=t[i];
            r+=dfs(s1,1e18);
        }
        if(r==w)
        {
            printf("%d ",k);
        }
    }
    return 0;
}