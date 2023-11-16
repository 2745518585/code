#include<cstdio>
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline ll read()
{
    char c=getchar();ll x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
ll p,k,a[10000001],m1[10000001],m2[10000001];
int n;
void abc(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else abc(b,a%b,y,x),y-=a/b*x;
}
int main()
{
    scanf("%d%lld%lld",&n,&p,&k);
    ll w=1;
    m1[0]=m2[n+1]=1;
    for(int i=1;i<=n;++i)
    {
        a[i]=read();
        w=(w*a[i])%p;
        m1[i]=(m1[i-1]*a[i])%p;
    }
    for(int i=n;i>=1;--i)
    {
        m2[i]=(m2[i+1]*a[i])%p;
    }
    ll x,y;
    abc(w,p,x,y);
    x=(x%p+p)%p;
    ll s=0,q=1;
    for(int i=1;i<=n;++i)
    {
        q=(q*k)%p;
        s=(s+q*m1[i-1]%p*m2[i+1]%p)%p;
    }
    printf("%lld",s*x%p);
    return 0;
}