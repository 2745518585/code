#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001,M=21;
int n,m,q,b1[M],b2[M];
ll pow10[M],a[N],b[N],d[N],f[N];
void dfs(int x,ll k,ll t)
{
    if(x==(n+1)/2)
    {
        a[++q]=k;
        d[q]=t;
        return;
    }
    for(int i=0;i<=18;++i)
    {
        if((x==0&&i==0)||(x*2+1==n&&i%2==1)) continue;
        ll z=(x==0)?b2[i]:b1[i];
        if(x*2+1==n) z=1;
        if(z==0) continue;
        if(x*2+1==n) dfs(x+1,k+pow10[x]*i,t*z);
        else dfs(x+1,k+pow10[x]*i+pow10[n-x-1]*i,t*z);
    }
}
ll sum(ll x)
{
    ll s=0;
    while(x)
    {
        s=s*10+x%10;
        x/=10;
    }
    return s;
}
ll solve(ll x)
{
    if(x==0) return 0;
    int z=upper_bound(b+1,b+n+1,x)-b-1;
    return f[z];
}
int main()
{
    pow10[0]=1;
    for(int i=1;i<=12;++i) pow10[i]=pow10[i-1]*10;
    for(int i=0;i<=9;++i)
    {
        for(int j=0;j<=9;++j)
        {
            ++b1[i+j];
            if(i!=0) ++b2[i+j];
        }
    }
    for(n=1;n<=10;++n)
    {
        dfs(0,0,1);
    }
    n=q;
    for(int i=1;i<=n;++i)
    {
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    n=unique(b,b+n+1)-b-1;
    for(int i=1;i<=q;++i)
    {
        f[lower_bound(b+1,b+n+1,a[i])-b]+=d[i];
    }
    for(int i=1;i<=n;++i)
    {
        int z=lower_bound(b+1,b+n+1,b[i]+sum(b[i]))-b;
        if(z<=n&&b[z]==b[i]+sum(b[i])) f[z]+=f[i];
        f[i]+=f[i-1];
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        ll x,y;
        scanf("%lld%lld",&x,&y);
        printf("%lld\n",solve(y)-solve(x-1)+y-x+1);
    }
    return 0;
}