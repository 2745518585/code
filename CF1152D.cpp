#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=1e9+7;
int n,f[N][N][2];
int main()
{
    scanf("%d",&n);
    for(int i=n;i>=0;--i)
    {
        for(int j=i;j>=0;--j)
        {
            f[i][j][0]=f[i][j][1]=0;
            if(i+1<=n)
            {
                f[i][j][0]=max(f[i][j][0]+f[i+1][j][0],f[i][j][1]+max(f[i+1][j][0],f[i+1][j][1]))%P;
                f[i][j][1]=(f[i][j][1]+f[i+1][j][0])%P;
            }
            if(j+1<=i)
            {
                f[i][j][0]=max(f[i][j][0]+f[i][j+1][0],f[i][j][1]+max(f[i][j+1][0],f[i][j+1][1]))%P;
                f[i][j][1]=(f[i][j][1]+f[i][j+1][0])%P;
            }
            ++f[i][j][1];
        }
    }
    printf("%lld",f[0][0][0]%P);
    return 0;
}