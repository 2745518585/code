#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001,M=101;
int n,m,f[N];
ll b[N];
bool g[M][M],h[N];
bool check(int x,int x1,int x2)
{
    return ((x&(1<<(min(x1,x2)-1)))!=0)&&((x&(1<<(max(x1,x2)-1)))==0);
}
ll solve()
{
    for(int i=0;i<=(1<<n)-1;++i) b[i]=0;
    b[0]=1;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        if(h[f[i]]==false) continue;
        for(int j=1;j<=n;++j)
        {
            if(i&(1<<(j-1))) continue;
            b[i|(1<<(j-1))]+=b[i];
        }
    }
    return b[(1<<n)-1];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;++i) h[((1<<i)-1)<<(n-i)]=true;
    for(int i=0;i<=(1<<n)-1;++i) f[i]=i;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) g[i][j]=true;
    }
    ll w=1;
    for(int i=1;i<=m;++i)
    {
        int z1,z2;
        scanf("%d%d",&z1,&z2);
        int x=(z1+w)%n+1,y=(z2+w*2)%n+1;
        if(x>y) swap(x,y);
        if(g[x][y]==true)
        {
            for(int j=1;j<=n;++j) g[x][j]=g[j][x]=g[y][j]=g[j][y]=0;
            for(int j=0;j<=(1<<n)-1;++j)
            {
                if(check(f[j],x,y)) f[j]^=(1<<(x-1))^(1<<(y-1));
                for(int k=1;k<=n;++k)
                {
                    if(check(f[j],x,k)) g[x][k]=g[k][x]=true;
                    if(check(f[j],y,k)) g[y][k]=g[k][y]=true;
                }
            }
            w=solve();
        }
        printf("%lld\n",w);
    }
    return 0;
}