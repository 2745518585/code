#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001,M=2000001;
const ll P=998244353;
int n,m,b1[M],b2[M];
ll jc[M],a[N][N];
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
    return (x%P+P)%P;
}
ll C(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*inv(jc[b]*jc[a-b])%P;
}
int main()
{
    jc[0]=1;
    for(int i=1;i<=2000000;++i) jc[i]=jc[i-1]*i%P;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&b1[i],&b2[i]);
        }
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=m;++j)
            {
                a[i][j]=C(b2[j]-b1[i]+n-1,n-1);
            }
        }
        ll s=1;
        for(int i=1;i<=m;++i)
        {
            if(a[i][i]==0)
            {
                s=-s;
                for(int j=i;j<=m;++j)
                {
                    if(a[j][i]!=0)
                    {
                        swap(a[i],a[j]);
                        break;
                    }
                }
            }
            for(int j=i+1;j<=m;++j)
            {
                ll z=a[j][i]*inv(a[i][i])%P;
                for(int k=i;k<=m;++k)
                {
                    a[j][k]=(a[j][k]-a[i][k]*z%P+P)%P;
                }
            }
        }
        for(int i=1;i<=m;++i) s=(s*a[i][i])%P;
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}