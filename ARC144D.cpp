#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n;
ll k;
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
int main()
{
    scanf("%d%lld",&n,&k);
    ll s=0,w=1,q0=1,q1=1,q2=(k+1)%P;
    for(int i=0;i<=n;++i)
    {
        s=(s+w*q0%P*(q1*((k+1)%P)%P-q2*i%P)%P)%P;
        w=w*2%P;
        q0=q0*(n-i)%P*inv(i+1)%P;
        q1=q1*((k-i)%P)%P*inv(i+1)%P;
        q2=q2*((k-i)%P)%P*inv(i+2)%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}