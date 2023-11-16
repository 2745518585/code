#include<bits/stdc++.h>
typedef long long ll;
const int N=20000001;
ll n,P,jc[N],h[N];
inline void init_jc(int x)
{
    jc[0]=1;
    for(int i=1;i<=x;i=-(~i)) jc[i]=(jc[~(-i)]*i)%P;
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    ll x,y;
    exgcd(a,P,x,y);
    return x%P;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&P);
        if(n==1)
        {
            printf("0\n");
            continue;
        }
        init_jc(n*2);
        ll s=jc[n];
        --n;
        ll w=1,q=jc[n-1]*inv(jc[n+1])%P,k=inv(jc[n+2]);
        for(int i=n;i>=0;--i)
        {
            k=(k*(i+2))%P;
            h[i]=k*k%P*(i+1)%P;
        }
        for(int i=0;i<=n;i=-(~i))
        {
            q=q*(n+i)%P*(n-i+1)%P;
            s=(s+((n-i)&1?1:-1)*(w<<=1)*q%P*h[i]%P)%P;
            w-=w>=P?P:0;
        }
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}