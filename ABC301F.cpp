#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=500001;
const ll P=998244353;
int n,h[N];
ll C[N][31],A[N][31],jc[N],powb[N],f[N],g[N],g2[N];
char a[N];
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    jc[0]=1;
    for(int i=1;i<=max(n,52);++i) jc[i]=jc[i-1]*i%P;
    C[0][0]=1;
    for(int i=1;i<=max(n,52);++i)
    {
        C[i][0]=1;
        for(int j=1;j<=26;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    for(int i=0;i<=max(n,52);++i)
    {
        for(int j=0;j<=26;++j)
        {
            A[i][j]=C[i][j]*jc[j]%P;
        }
    }
    powb[0]=1;
    for(int i=1;i<=max(n,52);++i) powb[i]=powb[i-1]*26%P;
    int w=0,p=26;
    for(int i=1;i<=n;++i)
    {
        if(a[i]!='?')
        {
            if(a[i]>='A'&&a[i]<='Z')
            {
                ++h[a[i]];
                if(h[a[i]]==2)
                {
                    for(int j=0;j<=p;++j)
                    {
                        f[i]=(f[i]+A[w][j]*C[p][j]%P*powb[w-j]%P)%P;
                    }
                    break;
                }
                --p;
                for(int j=0;j<=p;++j)
                {
                    f[i]=(f[i]+A[w][j+1]*C[p][j]%P*powb[w-j-1]%P)%P;
                }
            }
        }
        else
        {
            for(int j=0;j<=p;++j)
            {
                f[i]=(f[i]+A[w][j]*C[p][j]%P*(j+(26-p))%P*powb[w-j]%P)%P;
            }
            ++w;
        }
    }
    w=0,p=1;
    for(int i=n;i>=1;--i)
    {
        if(a[i]!='?')
        {
            if(a[i]>='A'&&a[i]<='Z')
            {
                g[i]=(g[i+1]+p*powb[w])%P;
                p=0;
            }
            else g[i]=0;
        }
        else
        {
            g[i]=(g[i+1]*26%P+p*powb[w]%P*26%P)%P;
            ++w;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(a[i]!='?')
        {
            if(a[i]>='a'&&a[i]<='z') g2[i]=g[i+1];
            else g2[i]=0;
        }
        else g2[i]=g[i+1]*26;
    }
    for(int i=n;i>=1;--i)
    {
        if(a[i]!='?') g2[i]=(g2[i]+g2[i+1])%P;
        else g2[i]=(g2[i]+g2[i+1]*52%P)%P;
    }
    ll s=0;
    for(int i=1;i<=n-1;++i)
    {
        s=(s+f[i]*g2[i+1]%P)%P;
    }
    ll z=1;
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='?') z=z*52%P;
    }
    printf("%lld",(z-s+P)%P);
    return 0;
}