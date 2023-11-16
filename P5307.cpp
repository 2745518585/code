#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=501,M=5001,K=2000001;
const ll P=1e9+7;
int m,n,k,q,a[N][N],b[M],c[K];
ll f[2][N][M];
int main()
{
    scanf("%d%d%d",&m,&n,&k);
    for(int i=1;i<=k;++i)
    {
        int t=int(ceil(double(k)/i));
        if(c[t]==0) b[++q]=t;
        c[t]=1;
    }
    sort(b+1,b+q+1);
    for(int i=1;i<=q;++i) c[b[i]]=i;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    f[1][1][c[int(ceil(double(k)/a[1][1]))]]=1;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i==1&&j==1) continue;
            for(int l=1;l<=q;++l) f[i&1][j][l]=0;
            for(int l=1;l<=q;++l)
            {
                f[i&1][j][c[int(ceil(double(b[l])/a[i][j]))]]=(f[i&1][j][c[int(ceil(double(b[l])/a[i][j]))]]+f[(i&1)^1][j][l]+f[i&1][j-1][l])%P;
            }
        }
    }
    printf("%lld",f[m&1][n][1]%P);
    return 0;
}