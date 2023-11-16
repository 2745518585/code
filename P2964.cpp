#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2002;
int n,a[N],f[N][N];
int main()
{
    scanf("%d",&n);
    int s=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        s+=a[i];
    }
    for(int i=n;i>=1;--i)
    {
        int w=-1e9,q=0;
        for(int j=1;i+j-1<=n;++j)
        {
            q+=a[i+j-1];
            w=max(w,q-f[i+j][min(j*2,n)]);
            f[i][j]=w;
        }
        for(int j=2;j<=n;++j) f[i][j]=max(f[i][j],f[i][j-1]);
    }
    printf("%lld",(s+f[1][2])/2);
    return 0;
}