#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001,M=101;
int n,m,p=1,s1,s2,t[N],t0[N],f[N];
ll b[M][M],c[M][M];
struct road
{
    int m,q;
    ll r;
}a[N];
void road(int x,int y,ll r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[++p].m=x;
    a[p].q=t[y];
    t[y]=p;
    a[p].r=0;
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
int sum(int x,int y)
{
    if(y==0) return s1;
    if(y==m) return s2;
    return (x-1)*(m-1)+y;
}
int main()
{
    scanf("%d%d",&n,&m);
    s1=n*(m-1)+1,s2=n*(m-1)+2;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            ll r;
            scanf("%lld%lld",&b[i][j],&r);
            road(sum(i,j-1),sum(i,j),r);
        }
        b[i][m+1]=1e18;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            scanf("%lld",&c[i][j]);
            c[j][i]=c[i][j];
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i==j) continue;
            for(int k=1;k<=m;++k)
            {
                for(int l=1;l<=m;++l)
                {
                    road(sum(i,k-1),sum(j,l),c[i][j]*max(min(b[i][k],b[j][l+1])-max(b[i][k-1],b[j][l]),0ll));
                }
            }
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