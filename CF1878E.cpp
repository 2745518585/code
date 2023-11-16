#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=500001,M=31;
int n,m,a[N],b[N][M];
namespace ST
{
    int b[N][M],lg[N],pw[N];
    void init()
    {
        for(int i=1;i<=n;++i)
        {
            b[i][0]=a[i];
            lg[i]=log2(i);
        }
        pw[0]=1;
        for(int i=1;i<=30;++i) pw[i]=pw[i-1]*2;
        for(int i=1;i<=30;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j+pw[i]-1<=n) b[j][i]=b[j][i-1]&b[j+pw[i-1]][i-1];
            }
        }
    }
    int sum(int x,int y)
    {
        return b[x][lg[y-x]]&b[y-pw[lg[y-x]]+1][lg[y-x]];
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        ST::init();
        scanf("%d",&m);
        for(int i=1;i<=m;++i)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            if(a[x]<k)
            {
                printf("-1 ");
                continue;
            }
            int l=x,r=n;
            while(l<r)
            {
                int z=l+r+1>>1;
                if(ST::sum(x,z)>=k) l=z;
                else r=z-1;
            }
            printf("%d ",l);
        }
        printf("\n");
    }
    return 0;
}