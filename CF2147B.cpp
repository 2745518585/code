#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=n;i>=1;--i) printf("%d ",i);
        printf("%d ",n);
        for(int i=1;i<=n-1;++i) printf("%d ",i);
        printf("\n");
    }
    return 0;
}