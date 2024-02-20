#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=401;
int n,m;
ll f[N][N][N][2];
struct str
{
    int x,l;
}a[N];
bool cmp(str a,str b)
{
    return a.x<b.x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].l);
    }
    a[++n].x=0,a[n].l=0;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=0;k<=n;++k) f[i][j][k][0]=f[i][j][k][1]=-1e18;
        }
    }
    int p=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i].l==0)
        {
            p=i;
            break;
        }
    }
    for(int i=0;i<=n;++i) f[p][p][i][0]=f[p][p][i][1]=0;
    for(int i=n;i>=1;--i)
    {
        for(int j=i;j<=n;++j)
        {
            for(int k=0;k<=n;++k)
            {
                for(int l=0;l<=1;++l)
                {
                    int x=l?a[j].x:a[i].x;
                    if(i>1)
                    {
                        if(k>0) f[i-1][j][k-1][0]=max(f[i-1][j][k-1][0],f[i][j][k][l]-(ll)abs(a[i-1].x-x)*k+a[i-1].l);
                        f[i-1][j][k][0]=max(f[i-1][j][k][0],f[i][j][k][l]-(ll)abs(a[i-1].x-x)*k);
                    }
                    if(j<n)
                    {
                        if(k>0) f[i][j+1][k-1][1]=max(f[i][j+1][k-1][1],f[i][j][k][l]-(ll)abs(a[j+1].x-x)*k+a[j+1].l);
                        f[i][j+1][k][1]=max(f[i][j+1][k][1],f[i][j][k][l]-(ll)abs(a[j+1].x-x)*k);
                    }
                }
            }
        }
    }
    printf("%lld\n",max(f[1][n][0][0],f[1][n][0][1]));
    return 0;
}