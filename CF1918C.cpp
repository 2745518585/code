#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll a,b,r;
        scanf("%lld%lld%lld",&a,&b,&r);
        bool u=false;
        ll s=0;
        for(int i=60;i>=0;--i)
        {
            if((a&(1ll<<i))!=(b&(1ll<<i)))
            {
                if(u)
                {
                    if((((a&(1ll<<i))!=0)^(a>b))) s-=(1ll<<i);
                    else if(r>=(1ll<<i)) s-=(1ll<<i),r-=(1ll<<i);
                    else s+=(1ll<<i);
                }
                else
                {
                    s+=(1ll<<i);
                    u=true;
                }
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}