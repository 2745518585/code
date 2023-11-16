#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
int m,n;
int main()
{
    scanf("%d%d",&m,&n);
    ++n;
    ++m;
    ll s=(ll)(m*n)*(m*n-1)*(m*n-2)/6-(ll)n*m*(m-1)*(m-2)/6-(ll)m*n*(n-1)*(n-2)/6;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            s-=2ll*(__gcd(i,j)-1)*(m-i)*(n-j);
        }
    }
    printf("%lld",s);
    return 0;
}