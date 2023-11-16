#include<cstdio>
#include<algorithm>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
const int N=1001,M=18;
const ll inf=1e18;
const short dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
ll m,n,k,q=2,b[N][2],d[N][N],f[N][N],g[1<<M][M+1];
char a[N][N];
bool check(ll x,ll y)
{
    return x>=1&&x<=m&&y>=1&&y<=n&&a[x][y]!='#'&&f[x][y]==inf;
}
ll sum(ll x)
{
    ll s=0;
    while(x) x-=x&-x,++s;
    return s;
}
void bfs(ll x,ll y)
{
    for(ll i=1;i<=m;++i)
    {
        for(ll j=1;j<=n;++j) f[i][j]=inf;
    }
    f[x][y]=0;
    queue<pair<ll,ll>> Q;
    Q.push(make_pair(x,y));
    while(!Q.empty())
    {
        ll kx=Q.front().first,ky=Q.front().second;
        Q.pop();
        for(ll i=0;i<=3;++i)
        {
            if(!check(kx+dx[i],ky+dy[i])) continue;
            f[kx+dx[i]][ky+dy[i]]=f[kx][ky]+1;
            Q.push(make_pair(kx+dx[i],ky+dy[i]));
        }
    }
}
int main()
{
    scanf("%lld%lld%lld",&m,&n,&k);
    for(ll i=1;i<=m;++i)
    {
        scanf("%s",a[i]+1);
        for(ll j=1;j<=n;++j)
        {
            if(a[i][j]=='S') b[1][0]=i,b[1][1]=j;
            if(a[i][j]=='G') b[2][0]=i,b[2][1]=j;
            if(a[i][j]=='o') ++q,b[q][0]=i,b[q][1]=j;
        }
    }
    for(ll i=1;i<=q;++i)
    {
        bfs(b[i][0],b[i][1]);
        for(ll j=1;j<=q;++j) d[i][j]=f[b[j][0]][b[j][1]];
    }
    for(ll i=0;i<=(1<<(q-2))-1;++i)
    {
        for(ll j=1;j<=q-2;++j) g[i][j]=inf;
    }
    for(ll i=1;i<=q-2;++i)
    {
        g[(1<<(i-1))][i]=d[1][i+2];
    }
    for(ll i=0;i<=(1<<(q-2))-1;++i)
    {
        for(ll j=1;j<=q-2;++j)
        {
            if((i&(1<<(j-1)))==0||g[i][j]==inf) continue;
            for(ll k=1;k<=q-2;++k)
            {
                if((i&(1<<(k-1)))!=0) continue;
                g[i|(1<<(k-1))][k]=min(g[i|(1<<(k-1))][k],g[i][j]+d[j+2][k+2]);
            }
        }
    }
    ll s=-1;
    if(d[1][2]<=k) s=0;
    for(ll i=0;i<=(1<<(q-2))-1;++i)
    {
        for(ll j=1;j<=q-2;++j)
        {
            if((i&(1<<(j-1)))==0) continue;
            if(g[i][j]+d[j+2][2]<=k) s=max(s,sum(i));
        }
    }
    printf("%lld",s);
    return 0;
}