#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
int n,f[N][N];
ll a[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        a[i]+=a[i-1];
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=n;++j) f[i][j]=1e9;
    }
    for(int i=1;i<=n;++i)
    {
        int k=i-1;
        for(int j=i-1;j>=0;--j)
        {
            while(k-1>=0&&a[j]-a[k-1]<=a[i]-a[j]) --k;
            f[i][j]=f[j][k]+(i-j-1);
        }
        for(int j=i-2;j>=0;--j) f[i][j]=min(f[i][j],f[i][j+1]);
    }
    printf("%d",f[n][0]);
    return 0;
}