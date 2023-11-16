#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=101;
ll n,f[N][N][2];
ll solve1()
{
    ll s=0;
    for(ll i=2;((1ll<<i)-1)<=n;++i)
    {
        ll x=n/((1ll<<i)-1);
        ll z=n-((1ll<<i)-1)*x;
        for(int j=i;j>=1;--j)
        {
            if(z>=((1ll<<j)-1)) z-=((1ll<<j)-1);
        }
        if(z==0) ++s;
    }
    // printf("%lld\n",s);
    return s;
}
ll check(ll x,int q1,int q2,int t)
{
    if((x+t)%2==1) return 0;
    f[0][0][0]=1;
    for(int i=1;i<=50;++i)
    {
        for(int j=0;j<=i*2;++j) f[i][j][0]=f[i][j][1]=0;
        for(int j=0;j<=i*2;++j)
        {
            for(int k:{0,1})
            {
                for(int o:{0,1})
                {
                    if(o&&i>=q1) continue;
                    for(int p:{0,1})
                    {
                        if(p&&i>=q2) continue;
                        if((k+o+p)%2==(((x+t)&(1ll<<i))!=0)) f[i][j+o+p][(k+o+p)/2]+=f[i-1][j][k];
                    }
                }
            }
        }
    }
    return f[50][t][0];
}
ll solve2()
{
    ll s=0;
    for(ll i=1;((1ll<<(i+1))-3)<=n;++i)
    {
        for(ll j=1;((1ll<<(i+1))+(1ll<<(j+1))-3)<=n-((1ll<<j)-1);++j)
        {
            ll x=(n-((1ll<<j)-1))/((1ll<<(i+1))+(1ll<<(j+1))-3);
            ll z=n-((1ll<<(i+1))+(1ll<<(j+1))-3)*x-((1ll<<j)-1);
            for(ll k=0;k<=i+j-2;++k)
            {
                s+=check(z,i,j,k);
            }
        }
    }
    // printf("%lld\n",s);
    return s;
}
int main()
{
    scanf("%lld",&n);
    ll s=1;
    s+=solve1();
    s+=solve2();
    printf("%lld\n",s);
    return 0;
}