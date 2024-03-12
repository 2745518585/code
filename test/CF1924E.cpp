#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
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
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int m,n;
        ll k;
        scanf("%d%d%lld",&m,&n,&k);
        --k;
        if((ll)m*n<=k)
        {
            printf("0\n");
            continue;
        }
        ll s=0;
        for(int i=1;i<=m-1;++i)
        {
            if(k/i<n) s=(s+inv(i+k/i))%P;
        }
        for(int i=1;i<=n-1;++i)
        {
            if(k/i<m) s=(s+inv(i+k/i))%P;
        }
        printf("%lld\n",((s+1)%P+P)%P);
    }
    return 0;
}