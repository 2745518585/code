#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100001;
const ll P=998244353;
int n,m,a[N];
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
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&a[i]);
        n+=a[i];
    }
    sort(a+1,a+m+1);
    int p=1;
    ll s1=0,d1=P-2,s2=1,d2=1,s=0;
    while(p<=m&&a[p]==1) s=(s-2)%P,++p;
    for(int i=1;i<=n-1;++i)
    {
        ll p2=(n-i)*d2%P*s2%P;
        ll p1=((ll)(3*n-2*i)*d1%P*s2-1*(2*n-i)%P*s1%P*d2)%P;
        while(p<=m&&a[p]==i+1) s=(s+p1*inv(p2))%P,++p;
        s1=d1,s2=d2,d1=p1,d2=p2;
    }
    printf("%lld\n",((s-d1%P*inv(d2))%P+P)%P);
    return 0;
}