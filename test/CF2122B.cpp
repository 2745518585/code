#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            int a,b,c,d;
            scanf("%d%d%d%d",&a,&b,&c,&d);
            if(b<=d) s+=max(a-c,0);
            else s+=a+(b-d);
        }
        printf("%lld\n",s);
    }
    return 0;
}