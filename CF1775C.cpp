#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll x,k;
        scanf("%lld%lld",&x,&k);
        if((x&k)!=k)
        {
            printf("-1\n");
            continue;
        }
        ll w1=x,w2=6e18;
        for(ll i=0;i<=60;++i)
        {
            if((k&(1ll<<i))==0)
            {
                if((x&(1ll<<i))!=0)
                {
                    ll z=x;
                    z&=(~((1ll<<(i+1))-1));
                    z+=(1ll<<(i+1));
                    w1=max(w1,z);
                }
            }
            else
            {
                ll z=x;
                z&=(~((1ll<<(i+1))-1));
                z+=(1ll<<(i+1))-1;
                w2=min(w2,z);
            }
        }
        if(w1>w2) printf("-1\n");
        else printf("%lld\n",w1);
    }
    return 0;
}