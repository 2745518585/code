#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001;
const ll P=1e9+7;
int n,m;
ll a[N][N];
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
    int z;
    scanf("%d%d%d",&n,&m,&z);
    if(z==0)
    {
        for(int i=1;i<=m;++i)
        {
            int x,y,w;
            scanf("%d%d%d",&x,&y,&w);
            a[x][y]=(a[x][y]-w)%P;
            a[y][x]=(a[y][x]-w)%P;
            a[x][x]=(a[x][x]+w)%P;
            a[y][y]=(a[y][y]+w)%P;
        }
    }
    else if(z==1)
    {
        for(int i=1;i<=m;++i)
        {
            int x,y,w;
            scanf("%d%d%d",&x,&y,&w);
            a[x][y]=(a[x][y]-w)%P;
            a[y][y]=(a[y][y]+w)%P;
        }
    }
    ll s=1;
    for(int i=2;i<=n;++i)
    {
        if(a[i][i]==0)
        {
            s=-s;
            for(int j=i;j<=n;++j)
            {
                if(a[j][i]!=0)
                {
                    swap(a[i],a[j]);
                    break;
                }
            }
        }
        for(int j=i+1;j<=n;++j)
        {
            ll z=a[j][i]*inv(a[i][i])%P;
            for(int k=i;k<=n;++k)
            {
                a[j][k]=(a[j][k]-a[i][k]*z%P+P)%P;
            }
        }
    }
    for(int i=2;i<=n;++i) s=(s*a[i][i])%P;
    printf("%lld",(s%P+P)%P);
    return 0;
}