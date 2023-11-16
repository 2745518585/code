#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll a[N],k,f[N][2];
ll sum(int x,int t)
{
    if(x==1||x==n) return a[x];
    if(a[x]>=k)
    {
        if(t==0) return min(a[x]-k,k);
        else return max(a[x]-k,k);
    }
    else
    {
        if(t==0) return 0;
        else return a[x];
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%lld",&n,&k);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
        }
        f[1][0]=f[1][1]=0;
        for(int i=2;i<=n-1;++i)
        {
            f[i][0]=f[i][1]=1e18;
            for(int j=0;j<=1;++j)
            {
                for(int k=0;k<=1;++k)
                {
                    f[i][k]=min(f[i][k],f[i-1][j]+sum(i-1,j^1)*sum(i,k));
                }
            }
        }
        printf("%lld\n",min(f[n-1][0]+sum(n-1,1)*a[n],f[n-1][1]+sum(n-1,0)*a[n]));
    }
    return 0;
}