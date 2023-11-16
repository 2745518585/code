#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001;
int n,m,k1,k2;
ll f[N][N],g[N],h[N];
struct str
{
    int x,y;
    str() {}
    str(int x,int y):x(x),y(y) {}
}a[N];
bool cmp(str a,str b)
{
    return a.y<b.y;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&k1,&k2);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].x);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].y);
    }
    sort(a+1,a+n+1,cmp);
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<=m;++j) f[i][j]=-1e18;
    }
    f[0][0]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=i;j>=1;--j)
        {
            for(int k=m;k>=a[i].y;--k)
            {
                f[j][k]=max(f[j][k],f[j-1][k-a[i].y]+a[i].x);
            }
        }
        for(int j=1;j<=n-i;++j) g[j]=a[n-j+1].x;
        sort(g+1,g+(n-i)+1,[&](ll x,ll y) {return x>y;});
        for(int j=1;j<=n-i;++j) g[j]+=g[j-1];
        for(int j=0;j<=i;++j)
        {
            for(int k=0;k<=m;++k)
            {
                h[k]=max(h[k],f[j][k]+g[min(n-i,j/k1+j/k2)]);
            }
        }
    }
    for(int i=1;i<=m;++i) h[i]=max(h[i],h[i-1]);
    for(int i=1;i<=m;++i)
    {
        printf("%lld ",h[i]);
    }
    return 0;
}