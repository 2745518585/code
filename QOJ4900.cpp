#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001;
const ll P=998244353;
int n,m,k,L,R;
char a[N];
ll sum(ll l,ll r)
{
    return (l+r)*(r-l+1)/2;
}
ll sum1(ll x,int k)
{
    return x*(x+1)/2+(k-1)*x;
}
ll sum2(ll x,int k)
{
    return x*(x+1)/2+(k*2-2)*x;
}
int main()
{
    scanf("%d%d%d%d%s",&n,&L,&R,&k,a+1);
    m=n*k;
    for(int i=1;i<=n;++i) m+=a[i]=='1';
    ll s=0;
    if(L==0) s^=(ll)m*(m+1)/2%P;
    int q=0;
    ll p=1;
    for(int i=1;i<=n;++i)
    {
        q+=k+(a[i]=='1');
        int t=m-q,l=q/i+1;
        ll w=0;
        if(q<=i-1) w+=sum(1,q);
        else w+=sum(1,i-1)+(ll)(i-1)*(q-(i-1));
        if(t<=(i-1)*2) w+=sum1(t/2,i)+sum1(t-t/2,i);
        else
        {
            w+=sum1(i-1,i)*2;
            t-=(i-1)*2;
            w+=sum2(t/l,i)*(l-t%l);
            w+=sum2(t/l+1,i)*(t%l);
        }
        w=(ll)m*(m+1)/2-w;
        p=p*233%P;
        if(i>=L&&i<=R) s^=w%P*p%P;
    }
    printf("%lld",s);
    return 0;
}