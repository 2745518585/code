#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll n,k,q;
        scanf("%lld%lld%lld",&n,&k,&q);
        if(q>=k*(k+1)/2&&q<=k*(n+(n-k+1))/2) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}