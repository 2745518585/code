#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll l,r,pow10[11];
int main()
{
    pow10[0]=1;
    for(int i=1;i<=10;++i) pow10[i]=pow10[i-1]*10;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld",&l,&r);
        int x1=0,x2=0;
        while(pow10[x1+1]<=l) ++x1;
        while(pow10[x2+1]<=r) ++x2;
        if(x1==x2)
        {
            printf("%lld\n",r-l+1);
            continue;
        }
        ll x=r/10;
        if(r/pow10[x2]>1) x=max(x,pow10[x2]-1);
        else x=max(x,r%pow10[x2]);
        ll s=r-pow10[x2]+1;
        s+=(pow10[x2]-1)-max(x+1,l)+1;
        printf("%lld\n",s);
    }
    return 0;
}