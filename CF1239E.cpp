#include<cstdio>
#include<algorithm>
#include<bitset>
using namespace std;
const int N=26,M=50001;
int n,a[N<<1];
bool h[N<<1];
bitset<N*M> f[N<<1][N<<1];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n*2;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n*2+1);
    f[2][0][0]=1;
    for(int i=3;i<=n*2;++i)
    {
        for(int j=n*2;j>=1;--j)
        {
            f[i][j]|=f[i-1][j]|(f[i-1][j-1]<<a[i]);
        }
        f[i][0]=f[i-1][0];
    }
    int s=0;
    for(int i=3;i<=n*2;++i) s+=a[i];
    int x=n-1,w=s/2;
    while(!f[n*2][n-1][w]) ++w;
    // printf("%d %d\n",x,w);
    for(int i=n*2;i>=3;--i)
    {
        if(f[i-1][x][w]==0) w-=a[i],--x;
        else h[i]=true;
    }
    h[1]=true;
    for(int i=1;i<=n*2;++i)
    {
        if(h[i]) printf("%d ",a[i]);
    }
    printf("\n");
    for(int i=n*2;i>=1;--i)
    {
        if(!h[i]) printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}