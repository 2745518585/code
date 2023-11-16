#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int m,n,a[N],b[N],h[N];
ll jc[N],T[N];
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
void add(int x,ll k)
{
    while(x<=200000) T[x]+=k,x+=x&-x;
}
ll sum(int x)
{
    ll s=0;
    while(x>=1) s+=T[x],x-=x&-x;
    return s;
}
int main()
{
    jc[0]=1;
    for(int i=1;i<=200000;++i) jc[i]=(jc[i-1]*i)%P;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        ++a[x];
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    ll w=jc[m];
    for(int i=1;i<=200000;++i)
    {
        if(a[i]>0)
        {
            add(i,jc[a[i]]*inv(jc[a[i]-1])%P);
            w=w*inv(jc[a[i]])%P;
        }
    }
    ll s=0;
    for(int i=1;i<=min(m,n);++i)
    {
        w=w*inv(jc[m-i+1])%P*jc[m-i]%P;
        s=(s+w*sum(b[i]-1)%P)%P;
        if(a[b[i]]>0)
        {
            w=w*jc[a[b[i]]]%P;
            add(b[i],-(jc[a[b[i]]]*inv(jc[a[b[i]]-1])%P));
            --a[b[i]];
            if(a[b[i]]>0)
            {
                add(b[i],jc[a[b[i]]]*inv(jc[a[b[i]]-1])%P);
                w=w*inv(jc[a[b[i]]])%P;
            }
        }
        else
        {
            w=0;
            break;
        }
    }
    if(m<n&&w!=0) s=(s+1)%P;
    printf("%lld",s);
    return 0;
}