#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2101,M=2000001;
const ll P=998244353;
int n,q,a[N<<1],a2[N<<1],b[M],c[N<<1];
ll f[N<<1][N],C[N][N];
bool h[N<<1];
bool check(int x)
{
    if(x==1) return false;
    for(int i=2;i*i<=x;++i)
    {
        if(x%i==0) return false;
    }
    return true;
}
int main()
{
    scanf("%d",&n);
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=n;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    for(int i=1;i<=n*2;++i)
    {
        int x;
        scanf("%d",&x);
        if(b[x]==0) b[x]=++q,c[q]=x;
        ++a[b[x]];
    }
    if(q<n)
    {
        printf("0");
        return 0;
    }
    for(int i=1;i<=q;++i)
    {
        a2[i]=a2[i-1]+a[i];
        h[i]=check(c[i]);
    }
    f[0][0]=1;
    for(int i=1;i<=q;++i)
    {
        for(int j=0;j<=n;++j)
        {
            if(h[i]&&j>=1&&n-(a2[i-1]-(j-1))>=0) f[i][j]=(f[i][j]+f[i-1][j-1]*C[n-(a2[i-1]-(j-1))][a[i]-1]%P)%P;
            if(n-(a2[i-1]-j)>=0) f[i][j]=(f[i][j]+f[i-1][j]*C[n-(a2[i-1]-j)][a[i]]%P)%P;
        }
    }
    printf("%lld",f[q][n]);
    return 0;
}