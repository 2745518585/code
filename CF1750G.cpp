#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
int n,a[N];
bool h[N];
ll P,jc[N],C[N][N],f[N];
int main()
{
    scanf("%d%lld",&n,&P);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    a[0]=n+1;
    for(int i=n;i>=1;--i)
    {
        for(int j=n;j>=1;--j) f[j]=f[j-1];
        f[0]=0;
        if(a[i-1]+1==a[i])
        {
            for(int j=0;j<=n;++j) f[j]=(f[j]+f[j+1])%P;
        }
        h[a[i]]=true;
        int w1=0,w2=0,v1=0,v2=0;
        for(int j=1;j<=a[i]-1;++j)
        {
            if(h[j-1]&&h[j]) ++w1;
            else if(!h[j-1]&&h[j]) ++v1;
        }
        for(int j=1;j<=n;++j)
        {
            if(h[j-1]&&h[j]) ++w2;
            else if(!h[j-1]&&h[j]) ++v2;
        }
        for(int j=0;j<=n;++j)
        {
            if(j-v2>=0)
            {
                f[j]=(f[j]+jc[j-1]*v1%P*C[w2][j-v2]%P)%P;
            }
            if(j-v2-1>=0)
            {
                f[j]=(f[j]+jc[j-1]*w1%P*C[w2-1][j-v2-1]%P)%P;
            }
            if(a[i-1]+1<a[i]&&h[a[i-1]+1]&&j<n&&j-v2+1>=0)
            {
                f[j]=(f[j]+jc[j]*C[w2][j-v2+1]%P)%P;
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        ll s=0;
        for(int j=0;j<=i;++j)
        {
            if((i-j)%2) s=(s-f[j]*C[n-j][i-j]%P)%P;
            else s=(s+f[j]*C[n-j][i-j]%P)%P;
        }
        printf("%lld ",(s%P+P)%P);
    }
    return 0;
}