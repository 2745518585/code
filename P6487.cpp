#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
ll n,q,a[N];
int main()
{
    a[1]=1,a[2]=1,q=2;
    while(a[q]<=1e18)
    {
        ++q;
        a[q]=a[q-1]+a[q-2];
    }
    scanf("%lld",&n);
    for(int i=q;i>=1;--i)
    {
        if(n>=a[i])
        {
            n-=a[i];
            if(n==0)
            {
                printf("%lld",a[i]);
                return 0;
            }
        }
    }
    return 0;
}