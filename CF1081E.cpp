#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
typedef long long ll;
int n;
ll a[N],b[N];
int main()
{
    scanf("%d",&n);
    n/=2;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        bool u=false;
        for(ll j=sqrt(a[i]);j>=1;--j)
        {
            if(a[i]%j!=0) continue;
            if(((j%2)^((a[i]/j)%2))) continue;
            if((a[i]/j-j)/2>s)
            {
                b[i]=((a[i]/j-j)/2)*((a[i]/j-j)/2)-s*s;
                s=(a[i]/j+j)/2;
                u=true;
                break;
            }
        }
        if(u==false)
        {
            printf("No");
            return 0;
        }
    }
    printf("Yes\n");
    for(int i=1;i<=n;++i)
    {
        printf("%lld %lld ",b[i],a[i]);
    }
    return 0;
}