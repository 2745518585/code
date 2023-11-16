#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int M=61;
int n;
ll a[M];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        ll x;
        scanf("%lld",&x);
        for(int j=60;j>=0;--j)
        {
            if((x&(1ll<<j))==0) continue;
            if(a[j]==0)
            {
                a[j]=x;
                break;
            }
            x^=a[j];
        }
    }
    ll s=0;
    for(int i=60;i>=0;--i)
    {
        if((s^a[i])>s) s^=a[i];
    }
    printf("%lld",s);
    return 0;
}