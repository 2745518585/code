#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=24;
int n,m,b[N<<2],g[1<<N][2];
ll f[1<<N];
struct point
{
    int x,y;
}a[N+1];
int sum(int x)
{
    for(int i=1;i<=n;++i)
    {
        if((x&(1<<(i-1)))==0) return i;
    }
}
ll dis(int x,int y)
{
    return (ll)(a[x].x-a[y].x)*(a[x].x-a[y].x)+(ll)(a[x].y-a[y].y)*(a[x].y-a[y].y);
}
int main()
{
    scanf("%d%d%d",&a[0].x,&a[0].y,&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    for(int i=0;i<=(1<<n)-1;++i) f[i]=1e18;
    f[0]=0;
    for(int i=0;i<=(1<<n)-2;++i)
    {
        if(f[i]==1e18) continue;
        int q=sum(i);
        if(f[i]+dis(0,q)*2<f[i|(1<<(q-1))])
        {
            f[i|(1<<(q-1))]=f[i]+dis(0,q)*2;
            g[i|(1<<(q-1))][0]=q;
            g[i|(1<<(q-1))][1]=0;
        }
        for(int j=1;j<=n;++j)
        {
            if((i&(1<<(j-1)))!=0||j==q) continue;
            if(f[i]+dis(0,q)+dis(q,j)+dis(j,0)<f[i|(1<<(q-1))|(1<<(j-1))])
            {
                f[i|(1<<(q-1))|(1<<(j-1))]=f[i]+dis(0,q)+dis(q,j)+dis(j,0);
                g[i|(1<<(q-1))|(1<<(j-1))][0]=j;
                g[i|(1<<(q-1))|(1<<(j-1))][1]=q;
            }
        }
    }
    printf("%lld\n",f[(1<<n)-1]);
    int x=(1<<n)-1;
    b[++m]=0;
    while(x!=0)
    {
        b[++m]=g[x][0];
        if(g[x][1]!=0)
        {
            b[++m]=g[x][1];
            x^=(1<<(g[x][0]-1))|(1<<(g[x][1]-1));
        }
        else x^=(1<<(g[x][0]-1));
        b[++m]=0;
    }
    for(int i=m;i>=1;--i)
    {
        printf("%d ",b[i]);
    }
    return 0;
}