#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
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
int n;
ll a[N],b[N],c[N],a2[N],b2[N];
void FWT_or(ll *a,int u)
{
    for(int k=1;k*2<=n;k<<=1)
    {
        for(int i=0;i<n;i+=k*2)
        {
            for(int j=0;j<k;++j) a[i+j+k]=(a[i+j+k]+a[i+j]*u%P)%P;
        }
    }
}
void FWT_and(ll *a,int u)
{
    for(int k=1;k*2<=n;k<<=1)
    {
        for(int i=0;i<n;i+=k*2)
        {
            for(int j=0;j<k;++j) a[i+j]=(a[i+j]+a[i+j+k]*u%P)%P;
        }
    }
}
void FWT_xor(ll *a,int u)
{
    for(int k=1;k*2<=n;k<<=1)
    {
        for(int i=0;i<n;i+=k*2)
        {
            for(int j=0;j<k;++j)
            {
                a[i+j]=a[i+j]+a[i+j+k];
                a[i+j+k]=a[i+j]-a[i+j+k]*2;
                a[i+j]=a[i+j]*u%P,a[i+j+k]=a[i+j+k]*u%P;
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    n=(1<<n);
    for(int i=0;i<n;++i)
    {
        scanf("%lld",&a2[i]);
    }
    for(int i=0;i<n;++i)
    {
        scanf("%lld",&b2[i]);
    }
    auto solve=[&](auto func,ll u)
    {
        for(int i=0;i<n;++i) a[i]=a2[i],b[i]=b2[i];
        func(a,1),func(b,1);
        for(int i=0;i<n;++i) c[i]=a[i]*b[i]%P;
        func(c,u);
        for(int i=0;i<n;++i) printf("%lld ",(c[i]%P+P)%P);printf("\n");
    };
    solve(FWT_or,-1);
    solve(FWT_and,-1);
    solve(FWT_xor,inv(2));
    return 0;
}