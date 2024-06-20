#include<cstdio>
#include<algorithm>
#include<bitset>
using namespace std;
typedef long long ll;
const int N=1001,M=17;
const ll P=1e9+7;
int n,m,b[N][N],l[N],ct[1<<M],lg[1<<M];
ll pw2[N],pw3[N],f[M<<1][1<<M][2],g[1<<M],h[1<<M];
bitset<N> a[M<<1][4],d[1<<M][4],e[1<<M],R;
ll solve(int t)
{
    for(int i=1;i<=(n-n/2);++i)
    {
        for(int k:{0,1,2,3}) d[1<<(i-1)][k]=a[i-1][k];
    }
    int v=0;
    R=0;
    for(int i=1;i<=m;++i)
    {
        if(l[i]<=n-t)
        {
            ++v;
            R[i-1]=1;
            continue;
        }
    }
    for(int i=0;i<=(1<<(n-n/2))-1;++i)
    {
        for(int j:{0,1,2,3}) d[i][j]&=R;
    }
    for(int i=1;i<=(1<<(n-n/2))-1;++i)
    {
        if(i!=(i&-i))
        {
            for(int j:{0,1,2,3}) d[i][j]=d[i^(i&-i)][j]|d[i&-i][j];
        }
    }
    for(int i=0;i<=(1<<(n-n/2))-1;++i)
    {
        int x1=(((R&d[i][1])|(d[i][2]&d[i][3]))).count(),x2=(((R^d[i][1])&(d[i][2]^d[i][3]))).count();
        g[i]=pw2[x2]%P*pw3[v-x1-x2]%P;
    }
    for(int i=0;i<=(1<<(n-n/2))-1;++i)
    {
        int x1=(((d[i][0]&d[i][1])|(d[i][2]&d[i][3]))).count(),x2=(((d[i][0]^d[i][1])&(d[i][2]^d[i][3]))).count();
        h[i]=pw2[x2]%P*pw3[v-x1-x2]%P;
    }
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<=(1<<(n-n/2))-1;++j) f[i][j][0]=f[i][j][1]=0;
    }
    f[0][0][0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=(1<<(n-n/2))-1;++j)
        {
            f[i][j][0]=(f[i-1][j>>1][0])*(i<t?g[j]:h[j])%P;
            f[i][j][1]=(f[i-1][j>>1][1]+f[i-1][(j>>1)|(1<<((n-n/2)-1))][0]+f[i-1][(j>>1)|(1<<((n-n/2)-1))][1])*g[j]%P;
            if(j&1) f[i][j][0]=-f[i][j][0],f[i][j][1]=-f[i][j][1];
        }
    }
    ll s=0;
    for(int i=0;i<=(1<<(n-n/2))-1;++i)
    {
        if((i&-i)==(1<<(n-t)))
        {
            s=(s+f[n][i][0]+f[n][i][1])%P;
        }
    }
    return -s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=(1<<M)-1;++i) ct[i]=ct[i^(i&-i)]+1;
    for(int i=0;i<=M-1;++i)
    {
        for(int j=(1<<i);j<=(1<<(i+1))-1;++j) lg[j]=i;
    }
    pw2[0]=1;
    for(int i=1;i<=m;++i) pw2[i]=pw2[i-1]*2%P;
    pw3[0]=1;
    for(int i=1;i<=m;++i) pw3[i]=pw3[i-1]*3%P;
    for(int i=1;i<=m;++i)
    {
        static char z[N];
        scanf("%s",z+1);
        for(int j=0;j<=n-1;++j) b[i][j]=0;
        for(int j=1;z[j];++j)
        {
            if(z[j]=='R') ++l[i];
            else if(z[j]=='0') b[i][l[i]]=2;
            else if(z[j]=='1') b[i][l[i]]=3;
            else if(z[j]=='*') b[i][l[i]]^=1;
        }
        for(int j=0;j<=n-1;++j) a[j][b[i][j]][i-1]=1;
    }
    for(int i=1;i<=(1<<(n/2))-1;++i)
    {
        g[i]=1;
        for(int j=1;j<=m;++j)
        {
            if((lg[i]+1)+l[j]<=n) e[i][j-1]=1;
        }
    }
    for(int i=1;i<=m;++i) R[i-1]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=(n/2);++j)
        {
            if(j<=i)
            {
                for(int k:{0,1,2,3}) d[1<<(j-1)][k]=a[i-j][k];
            }
            else
            {
                for(int k:{0,1,2,3}) d[1<<(j-1)][k]=0;
                d[1<<(j-1)][0]=R;
            }
        }
        for(int j=1;j<=(1<<(n/2))-1;++j)
        {
            if(j!=(j&-j))
            {
                for(int k:{0,1,2,3}) d[j][k]=d[j^(j&-j)][k]|d[j&-j][k];
            }
        }
        for(int j=1;j<=(1<<(n/2))-1;++j)
        {
            int x1=(((d[j][0]&d[j][1])|(d[j][2]&d[j][3]))&e[j]).count(),x2=(((d[j][0]^d[j][1])&(d[j][2]^d[j][3]))&e[j]).count();
            g[j]=g[j]*pw2[x2]%P*pw3[e[j].count()-x1-x2]%P;
        }
    }
    ll s=0;
    for(int i=1;i<=(1<<(n/2))-1;++i)
    {
        if(ct[i]%2==1) s=(s+g[i])%P;
        else s=(s-g[i])%P;
    }
    for(int i=n/2+1;i<=n;++i)
    {
        s=(s+solve(i));
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}