#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,a[N];
ll jc[N],ivjc[N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
ll A(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*ivjc[a-b]%P)%P;
}
ll C(ll a,ll b)
{
    if(b>a) return 0;
    return (jc[a]*ivjc[a-b]%P*ivjc[b]%P)%P;
}
int main()
{
    jc[0]=1;
    for(int i=1;i<=200000;++i) jc[i]=jc[i-1]*i%P;
    ivjc[200000]=inv(jc[200000]);
    for(int i=200000;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        if((a[n]!=-1&&a[n]!=n)||[&](){
            for(int i=1;i<=n-1;++i) if(a[i]>i||(a[i+1]!=-1&&a[i]>a[i+1])) return true;
            return false;
        }())
        {
            printf("0\n");
            continue;
        }
        a[n]=n;
        ll s=1;
        for(int i=1,j=0;i<=n;++i)
        {
            if(a[i]==-1) continue;
            ll w=0;
            for(int k=0;k<=a[i]-a[j];++k)
            {
                w=(w+C(i-j,k)*A(j-a[j],k)%P*C(i-j,a[i]-a[j]-k)%P*A(i-a[j]-k,a[i]-a[j]-k)%P)%P;
            }
            s=s*w%P;
            j=i;
        }
        printf("%lld\n",s);
    }
    return 0;
}