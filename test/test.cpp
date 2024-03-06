#include<cstdio>
#include<algorithm>
#include<bitset>
using namespace std;
typedef long long ll;
const int N=15;
const ll P=1e9+7;
int n,m,k,b[N+1],e[1<<N],f[1<<N][N+1],g[1<<N][N+1],h[1<<N],C[N*2+2][N*2+2],jc[N*2+2];
bitset<1<<N> d[1<<N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    return x=(x%P+P)%P;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        b[x]|=(1<<(y-1));
    }
    for(int i=1;i<=n;++i) e[(1<<(i-1))]=i;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(b[j]&(1<<(i-1))) b[j]|=b[i];
        }
    }
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=(i-1)&i;j;j=(j-1)&i)
        {
            d[j][i^j]=d[j^(j&-j)][i^j]||(b[e[j&-j]]&(i^j));
        }
    }
    h[0]=1;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if((i&(1<<(j-1)))&&!d[i^(1<<(j-1))][1<<(j-1)]) h[i]=(h[i]+h[i^(1<<(j-1))])%P;
        }
    }
    g[0][0]=1;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=i;j;j=(j-1)&i)
        {
            if((j&(i&-i))&&!d[i^j][j]&&!d[j][i^j])
            {
                for(int k=1;k<=n;++k) g[i][k]=(g[i][k]+(ll)g[i^j][k-1]*h[j]%P)%P;
            }
        }
    }
    f[0][0]=1;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=i;j;j=(j-1)&i)
        {
            if(d[j][i^j]) continue;
            for(int l=0;l<=n;++l)
            {
                if(g[j][l]==0) continue;
                for(int k=l;k<=n;++k) f[i][k]=(f[i][k]+(ll)f[i^j][k-l]*g[j][l]%P*(l&1?1:-1)%P)%P;
            }
        }
    }
    C[0][0]=1;
    for(int i=1;i<=n*2+1;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    jc[0]=1;
    for(int i=1;i<=n*2+1;++i) jc[i]=(ll)jc[i-1]*i%P;
    ll s=0;
    for(int i=1;i<=k+1;++i)
    {
        s=(s+(ll)f[(1<<n)-1][i]*jc[i]%P*C[k+1][i]%P*inv((ll)C[n+k][n]*jc[n]%P)%P)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}