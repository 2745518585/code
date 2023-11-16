#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,k;
ll query(int x)
{
    printf("? %d\n",x);
    fflush(stdout);
    ll y;
    scanf("%lld",&y);
    return y;
}
int main()
{
    scanf("%d%d",&n,&k);
    int q=sqrt(n);
    if(n<=100) q=1;
    for(int i=1;i<=q;++i) query(1);
    int l=1,r=n;
    for(int i=1;i<=n;i+=q)
    {
        if(query(i)<k)
        {
            l=i;
            break;
        }
    }
    while(l<r)
    {
        int z=l+r+1>>1;
        int p=query(z);
        if(p<k) l=z;
        else r=z-1;
    }
    printf("! %d\n",l%n+1);
    fflush(stdout);
    return 0;
}