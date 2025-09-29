#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll x,y;
        scanf("%d%lld",&n,&x);
        y=(1ll<<(n+1))-x;
        m=0;
        int p=1;
        while(x!=(1ll<<n))
        {
            if(x<y) swap(x,y),p^=1;
            x-=y;
            y<<=1;
            a[++m]=p;
        }
        printf("%d\n",m);
        for(int i=m;i>=1;--i) printf("%d ",a[i]+1);
        printf("\n");
    }
    return 0;
}