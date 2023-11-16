#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=20000001,M=1e7;
int sp,p[N];
ll phi[N];
bool ip[N];
ll qpow(ll a,ll b,ll P)
{
    ll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y%P;
        y=y*y%P;
        b>>=1;
    }
    return x;
}
ll solve(ll P)
{
    if(P==1) return 0;
    return qpow(2,solve(phi[P])+phi[P],P);
}
int main()
{
    phi[1]=1;
    for(int i=2;i<=M;++i)
    {
        if(ip[i]==false) p[++sp]=i,phi[i]=i-1;
        for(int j=1;j<=sp&&i*p[j]<=M;++j)
        {
            ip[i*p[j]]=true;
            if(i%p[j]==0)
            {
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
            phi[i*p[j]]=phi[i]*phi[p[j]];
        }
    }
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll P;
        scanf("%lld",&P);
        printf("%lld\n",solve(P));
    }
    return 0;
}