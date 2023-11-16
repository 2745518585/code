#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
ll a,b,m,n;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld%lld%lld",&a,&b,&n,&m);
        if(a*m<=b*(m+1)) printf("%lld\n",(n/(m+1)*m)*a+(n%(m+1))*min(a,b));
        else printf("%lld\n",n*min(a,b));
    }
    return 0;
}