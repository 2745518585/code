#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
ll n,k;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&k);
        if(n==k)
        {
            printf("YES\n");
            printf("1\n");
            printf("%lld\n",1);
        }
        else if(n-k+1>n/2)
        {
            printf("YES\n");
            printf("2\n");
            printf("%lld %lld\n",n-k+1,1);
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}