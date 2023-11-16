#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
int m,n,k,a[N][N],a2[N][N];
ll b[N][N],b1[N][N],b2[N][N],c[N][N],c1[N][N],c2[N][N],c3[N][N],c4[N][N];
void solve()
{
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j) b[i][j]=c[i][j]=0;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            b[j][i]=b[j-1][i]+a2[j][i];
        }
    }
    for(int i=2;i<=m+n;++i)
    {
        for(int j=max(i-n,1);j<=min(i-1,m);++j)
        {
            b1[j][i-j]=b1[j-1][i-j+1]+a2[j][i-j];
        }
    }
    for(int i=-(m-1);i<=n-1;++i)
    {
        for(int j=min(n-i,m);j>=max(1-i,1);--j)
        {
            b2[j][i+j]=b2[j+1][i+j+1]+a2[j][i+j];
        }
    }
    for(int i=1;i<=k*2-1;++i)
    {
        for(int j=abs(k-i)+1;j<=k;++j)
        {
            c[k][k]+=a2[i][j];
        }
    }
    for(int i=k;i<=m-k+1;++i)
    {
        for(int j=k;j<=n-k+1;++j)
        {
            if(i==k&&j==k) continue;
            if(j==k) c[i][j]=c[i][j-1]-(b1[i][j-k]-b1[i-k][j])-(b2[i][j-k]-b2[i+k][j])+a2[i][j-k]+(b[i+k-1][j]-b[i-k][j]);
            else c[i][j]=c[i-1][j]-(b1[i-1][j-k+1]-b1[i-k][j+1])+(b2[i][j-k+1]-b2[i+k][j+1]);
        }
    }
}
int main()
{
    scanf("%d%d%d",&m,&n,&k);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    ll w=0;
    for(int i=1;i<=k*2-1;++i)
    {
        for(int j=abs(k-i)+1;j<=k*2-abs(k-i)-1;++j)
        {
            w+=a[i][j]*(abs(k-i)+abs(k-j));
        }
    }
    ll s=w;
    for(int i=k;i<=m-k+1;++i)
    {
        for(int j=k;j<=n-k+1;++j)
        {
            if(i==k&&j==k) continue;
            
        }
    }
}