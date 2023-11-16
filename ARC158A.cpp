#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll a,b,c;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld%lld",&a,&b,&c);
        ll k=(a+b+c)/3;
        if((a+b+c)%3!=0||k%2!=a%2||k%2!=b%2||k%2!=c%2) printf("-1\n");
        else printf("%lld\n",max(abs(k-a),max(abs(k-b),abs(k-c)))/2);
    }
    return 0;
}