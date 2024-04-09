#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
int m;
ll n,k,pw[N],f[N];
ll sum1(int t,ll x)
{
    if(x<=(n-pw[m])/pw[m-t])
    {
        ll s=0,z=x;
        for(int i=t;i>=0;--i)
        {
            s+=f[m-i]*(z%k)+1;
            z/=k;
        }
        return s;
    }
    else
    {
        ll s=n-(f[m-t-1]-1),z=x;
        for(int i=t;i>=0;--i)
        {
            s-=f[m-i-1]*(k-z%k-1-(i==0));
            z/=k;
        }
        return s;
    }
}
ll sum2(int t,ll x)
{
    return pw[t]+x;
}
ll solve1(int t)
{
    ll l=0,r=((t==m?n:pw[t+1])-pw[t]);
    while(l<r)
    {
        ll z=l+r>>1;
        if(sum1(t,z)>=sum2(t,z)) r=z;
        else l=z+1;
    }
    return l;
}
ll solve2(int t)
{
    ll l=0,r=((t==m?n:pw[t+1])-pw[t]);
    while(l<r)
    {
        ll z=l+r+1>>1;
        if(sum1(t,z)<=sum2(t,z)) l=z;
        else r=z-1;
    }
    return l;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&k);
        m=-1;
        ll x=n;
        while(x) ++m,x/=k;
        pw[0]=1;
        for(int i=1;i<=m;++i) pw[i]=pw[i-1]*k;
        f[0]=1;
        for(int i=1;i<=m;++i) f[i]=f[i-1]+pw[i];
        ll s=0;
        for(int i=0;i<=m;++i)
        {
            ll z=solve1(i);
            if(sum1(i,z)==sum2(i,z)) s+=solve2(i)-z+1;
        }
        printf("%lld\n",s);
    }
    return 0;
}