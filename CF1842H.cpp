#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=21;
const ll P=998244353;
int n,m,g[N][2];
ll f[1<<N];
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
    x=(x%P+P)%P;
    return x;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int z,x,y;
        scanf("%d%d%d",&z,&x,&y);
        g[x][z^1]|=(1<<(y-1)),g[y][z^1]|=(1<<(x-1));
    }
    f[0]=1;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i&(1<<(j-1))) continue;
            for(int k=0;k<=1;++k)
            {
                if((i|(1<<(j-1)))&g[j][k]) continue;
                f[i|(1<<(j-1))]=(f[i|(1<<(j-1))]+f[i])%P;
            }
        }
    }
    ll w=1;
    for(int i=1;i<=n;++i) w=w*i*2%P;
    printf("%lld",(f[(1<<n)-1]*inv(w)%P+P)%P);
    return 0;
}