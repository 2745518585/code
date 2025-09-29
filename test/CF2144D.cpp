#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,a[N],b[N];
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&q);
        for(int i=1;i<=5e5;++i) b[i]=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            ++b[a[i]];
        }
        for(int i=1;i<=5e5;++i) b[i]+=b[i-1];
        ll s=-1e18;
        for(int i=2;i<=2e5;++i)
        {
            ll w=0;
            for(int j=1;j<=2e5/i+1;++j)
            {
                w+=(ll)j*(b[j*i]-b[(j-1)*i])-(ll)q*max((b[j*i]-b[(j-1)*i])-(b[j]-b[j-1]),0);
            }
            // printf("%d: %lld\n",i,w);
            s=max(s,w);
        }
        printf("%lld\n",s);
    }
    return 0;
}