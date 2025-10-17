#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,a[N];
ll jc[N],ivjc[N],pw2[N];
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
ll C(ll a,ll b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[a-b]%P*ivjc[b]%P;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        jc[0]=1;
        for(int i=1;i<=n+1;++i) jc[i]=jc[i-1]*i%P;
        ivjc[n+1]=inv(jc[n+1]);
        for(int i=n+1;i>=1;--i) ivjc[i-1]=ivjc[i]*i%P;
        pw2[0]=1;
        for(int i=1;i<=n+1;++i) pw2[i]=pw2[i-1]*2%P;
        for(int i=0;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        bool u=false;
        int t=0;
        for(int i=0;i<=n;++i)
        {
            if(a[i]!=-1)
            {
                if(a[i]==0) continue;
                else if(a[i]>n) u=true;
                else if(a[a[i]]==-1) a[a[i]]=i;
                else if(a[a[i]]!=i) u=true;
            }
        }
        if(u)
        {
            printf("0\n");
            continue;
        }
        int w=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i]==-1) ++w;
        }
        ll s=0;
        for(int i=0;i<=w/2;++i)
        {
            s=(s+jc[w]*ivjc[w-i*2]%P*inv(pw2[i])%P*ivjc[i]%P*pw2[w-i*2]%P)%P;
            if(a[n]==-1) s=(s-jc[w-1]*ivjc[w-i*2-1]%P*inv(pw2[i])%P*ivjc[i]%P*pw2[w-i*2-1]%P)%P;
        }
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}