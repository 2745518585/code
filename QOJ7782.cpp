#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=300001,M=500;
const ll B=147258369,P=1e9+7;
int n,m,q,a[N],b[N];
ll pw[N],ivpw[N],pws[N];
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
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
namespace ST
{
    int f[N][21],lg[N];
    void init()
    {
        for(int i=1;i<=m;++i) f[i][0]=b[i];
        for(int i=1;i<=20;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,m);++j) lg[j]=i;
        }
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=m;++j)
            {
                if(j+(1<<i)-1<=m) f[j][i]=gcd(f[j][i-1],f[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int sum(int x,int y)
    {
        if(x>y) swap(x,y);
        return gcd(f[x][lg[y-x]],f[y-(1<<lg[y-x])+1][lg[y-x]]);
    }
}
struct sgt0
{
    int p;
    ll b[M+1];
    void add(int x,ll k)
    {
        b[x/M]=(b[x/M]+k)%P;
    }
    ll sum(int x)
    {
        ll s=0;
        for(int i=0;i<=x/M-1;++i) s=(s+b[i])%P;
        for(int i=x/M*M;i<=x;++i) s=(s+a[i]*(i%p==0))%P;
        return s;
    }
}S0[M+1];
struct sgt1
{
    int p;
    ll b[N/M+1];
    void add(int x,ll k)
    {
        b[x/M]=(b[x/M]+k)%P;
    }
    ll sum(int x)
    {
        ll s=0;
        for(int i=0;i<=x/M-1;++i) s=(s+b[i])%P;
        for(int i=x/M*M;i<=x;++i) s=(s+a[i]*pw[i%p]%P)%P;
        return s;
    }
}S1[M+1];
struct sgt2
{
    ll a[N],b[N];
    void add(int x,ll k)
    {
        for(int i=x;i<=(x/M+1)*M-1;++i) b[i]=(b[i]+k)%P;
        for(int i=x/M+1;i<=n/M;++i) a[i]=(a[i]+k)%P;
    }
    ll sum(int x)
    {
        return (a[x/M]+b[x])%P;
    }
}S2;
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&b[i]);
    }
    pw[0]=1;
    for(int i=1;i<=n;++i) pw[i]=pw[i-1]*B%P;
    ivpw[n]=inv(pw[n]);
    for(int i=n;i>=1;--i) ivpw[i-1]=ivpw[i]*B%P;
    pws[0]=pw[0];
    for(int i=1;i<=n;++i) pws[i]=(pws[i-1]+pw[i])%P;
    ST::init();
    for(int i=1;i<=M;++i)
    {
        S0[i].p=S1[i].p=i;
        for(int j=1;j<=n;++j)
        {
            if(j%i==0) S0[i].add(j,a[j]);
            S1[i].add(j,a[j]*pw[j%i]%P);
        }
    }
    for(int i=1;i<=n;++i)
    {
        S2.add(i,a[i]*pw[i]%P);
    }
    for(int i=1;i<=q;++i)
    {
        char z;
        scanf("%s",&z);
        if(z=='U')
        {
            int x,k;
            scanf("%d%d",&x,&k);
            for(int j=1;j<=M;++j)
            {
                if(x%j==0) S0[j].add(x,(k-a[x]));
                S1[j].add(x,(k-a[x])*pw[x%j]%P);
            }
            S2.add(x,(k-a[x])*pw[x]%P);
            a[x]=k;
        }
        else if(z=='Q')
        {
            int l1,r1,l2,r2;
            scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
            int k=gcd(ST::sum(l2,r2),r1-l1+1);
            ll w=0,s=0;
            if(k<=M)
            {
                w=(S0[k].sum(r1)-S0[k].sum(l1-1))%P;
                s=(S1[k].sum(r1)-S1[k].sum(l1-1))%P;
            }
            else
            {
                for(int i=0;i<=n;i+=k)
                {
                    if(i>=l1&&i<=r1) w=(w+a[i])%P;
                    int l=max(i,l1),r=min(i+k-1,r1);
                    if(l<=r)
                    {
                        s=(s+(S2.sum(r)-S2.sum(l-1))*ivpw[l-l%k]%P)%P;
                    }
                }
            }
            w=(w*pws[k-1]%P+P)%P;
            s=(s%P+P)%P;
            if(w==s) printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}